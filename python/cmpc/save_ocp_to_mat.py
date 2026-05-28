from pickle import NEXT_BUFFER
from re import U

import numpy as np
from scipy.fft import next_fast_len
from scipy.io import savemat

from scipy.linalg import block_diag

from typing import List, Optional
"""
Save Linear-Quadratic OCP data to MATLAB .mat file compatible with C++ reader.

The OCP has the form:
    minimize  Σᵢ₌₀ⁿ⁻¹ [½ uᵢᵀ Rᵢ uᵢ + uᵢᵀ Sᵢ xᵢ + ½ xᵢᵀ Qᵢ xᵢ + rᵢᵀuᵢ + qᵢᵀxᵢ] + ½ xₙᵀ Qₙ xₙ + qₙᵀ xₙ
    s.t.      x₀ = b₀
              xᵢ₊₁ = Aᵢ xᵢ + Bᵢ uᵢ + bᵢ₊₁
              lᵢ ≤ Cᵢ xᵢ + Dᵢ uᵢ ≤ uᵢ
              lₙ ≤ Cₙ xₙ ≤ uₙ
"""




class OCPData:
    """Container for OCP problem data."""
    
    def __init__(self, N: int, nx: int, nu: int, ny: int, ny_N: int):
        """
        Initialize OCP dimensions.
        
        Args:
            N: Time horizon (number of stages)
            nx: State dimension
            nu: Control/input dimension
            ny: Output constraint dimension at stages 0 to N-1
            ny_N: Output constraint dimension at final stage N
        """
        self.N = N
        self.nx = nx
        self.nu = nu
        self.ny = ny
        self.ny_N = ny_N
        
        # Initialize matrices
        # H contains [Q Sᵀ; S R] for each stage i=0..N-1, plus Q_N at stage N
        self.H = np.zeros((nx + nu, nx + nu, N + 1))
        
        # AB contains [A B] for each stage i=0..N-1
        self.AB = np.zeros((nx, nx + nu, N))
        
        # CD contains [C D] for each stage i=0..N-1
        self.CD = np.zeros((ny, nx + nu, N))
        
        # CN contains [C] for final stage N
        self.CN = np.zeros((ny_N, nx))
        
        # qr contains stacked [q; r] vectors for all stages
        self.qr = np.zeros((N * (nx + nu) + nx, 1))
        
        # b contains all b vectors (including b₀)
        self.b = np.zeros(((N + 1) * nx, 1))
        
        # Constraint bounds
        self.b_min = np.zeros((N * ny + ny_N, 1))
        self.b_max = np.zeros((N * ny + ny_N, 1))
    
    def set_stage_cost(self, i: int, Q: np.ndarray, R: np.ndarray, 
                       S: Optional[np.ndarray] = None,
                       q: Optional[np.ndarray] = None,
                       r: Optional[np.ndarray] = None):
        """
        Set cost matrices and vectors for stage i.
        
        Args:
            i: Stage index (0 to N-1)
            Q: State cost matrix (nx, nx)
            R: Control cost matrix (nu, nu)
            S: Cross term (nu, nx), optional
            q: State cost vector (nx,), optional
            r: Control cost vector (nu,), optional
        """
        assert 0 <= i < self.N, f"Stage {i} out of range [0, {self.N-1}]"
        assert Q.shape == (self.nx, self.nx), f"Q shape mismatch: {Q.shape}"
        assert R.shape == (self.nu, self.nu), f"R shape mismatch: {R.shape}"
        
        # Build H = [Q Sᵀ; S R]
        self.H[:self.nx, :self.nx, i] = Q
        self.H[self.nx:, self.nx:, i] = R
        if S is not None:
            assert S.shape == (self.nu, self.nx), f"S shape mismatch: {S.shape}"
            self.H[self.nx:, :self.nx, i] = S
            self.H[:self.nx, self.nx:, i] = S.T
        
        # Set cost vectors
        if q is not None:
            assert q.shape == (self.nx,), f"q shape mismatch: {q.shape}"
            start_idx = i * (self.nx + self.nu)
            self.qr[start_idx:start_idx + self.nx, 0] = q
        
        if r is not None:
            assert r.shape == (self.nu,), f"r shape mismatch: {r.shape}"
            start_idx = i * (self.nx + self.nu) + self.nx
            self.qr[start_idx:start_idx + self.nu, 0] = r
    
    def set_terminal_cost(self, Q_N: np.ndarray, q_N: Optional[np.ndarray] = None):
        """
        Set terminal cost at stage N.
        
        Args:
            Q_N: Terminal state cost matrix (nx, nx)
            q_N: Terminal state cost vector (nx,), optional
        """
        assert Q_N.shape == (self.nx, self.nx), f"Q_N shape mismatch: {Q_N.shape}"
        
        # Store in H (padded with zeros for the control part)
        self.H[:self.nx, :self.nx, self.N] = Q_N
        
        if q_N is not None:
            assert q_N.shape == (self.nx,), f"q_N shape mismatch: {q_N.shape}"
            start_idx = self.N * (self.nx + self.nu)
            self.qr[start_idx:start_idx + self.nx, 0] = q_N
    
    def set_dynamics(self, i: int, A: np.ndarray, B: np.ndarray, b: np.ndarray):
        """
        Set dynamics matrices for stage i: x_{i+1} = A_i x_i + B_i u_i + b_{i+1}
        
        Args:
            i: Stage index (0 to N-1)
            A: State transition matrix (nx, nx)
            B: Control matrix (nx, nu)
            b: Affine term (nx,) - this is b_{i+1}
        """
        assert 0 <= i < self.N, f"Stage {i} out of range [0, {self.N-1}]"
        assert A.shape == (self.nx, self.nx), f"A shape mismatch: {A.shape}"
        assert B.shape == (self.nx, self.nu), f"B shape mismatch: {B.shape}"
        assert b.shape == (self.nx,), f"b shape mismatch: {b.shape}"
        
        # Build AB = [A B]
        self.AB[:, :self.nx, i] = A
        self.AB[:, self.nx:, i] = B
        
        # Store b_{i+1}
        start_idx = (i + 1) * self.nx
        self.b[start_idx:start_idx + self.nx, 0] = b
    
    def set_initial_state(self, b0: np.ndarray):
        """
        Set initial state constraint: x_0 = b_0
        
        Args:
            b0: Initial state (nx,)
        """
        assert b0.shape == (self.nx,), f"b0 shape mismatch: {b0.shape}"
        self.b[:self.nx, 0] = b0
    
    def set_stage_constraints(self, i: int, C: np.ndarray, D: np.ndarray,
                             l: np.ndarray, u: np.ndarray):
        """
        Set inequality constraints for stage i: l_i ≤ C_i x_i + D_i u_i ≤ u_i
        
        Args:
            i: Stage index (0 to N-1)
            C: State constraint matrix (ny, nx)
            D: Control constraint matrix (ny, nu)
            l: Lower bound (ny,)
            u: Upper bound (ny,)
        """
        assert 0 <= i < self.N, f"Stage {i} out of range [0, {self.N-1}]"
        assert C.shape == (self.ny, self.nx), f"C shape mismatch: {C.shape}"
        assert D.shape == (self.ny, self.nu), f"D shape mismatch: {D.shape}"
        assert l.shape == (self.ny,), f"l shape mismatch: {l.shape}"
        assert u.shape == (self.ny,), f"u shape mismatch: {u.shape}"
        
        # Build CD = [C D]
        self.CD[:, :self.nx, i] = C
        self.CD[:, self.nx:, i] = D
        
        # Store bounds
        start_idx = i * self.ny
        self.b_min[start_idx:start_idx + self.ny, 0] = l
        self.b_max[start_idx:start_idx + self.ny, 0] = u
    
    def set_terminal_constraints(self, C_N: np.ndarray, l_N: np.ndarray, u_N: np.ndarray):
        """
        Set terminal inequality constraints: l_N ≤ C_N x_N ≤ u_N
        
        Args:
            C_N: Terminal constraint matrix (ny_N, nx)
            l_N: Lower bound (ny_N,)
            u_N: Upper bound (ny_N,)
        """
        assert C_N.shape == (self.ny_N, self.nx), f"C_N shape mismatch: {C_N.shape}"
        assert l_N.shape == (self.ny_N,), f"l_N shape mismatch: {l_N.shape}"
        assert u_N.shape == (self.ny_N,), f"u_N shape mismatch: {u_N.shape}"
        
        self.CN[:, :] = C_N
        
        # Store terminal bounds
        start_idx = self.N * self.ny
        self.b_min[start_idx:start_idx + self.ny_N, 0] = l_N
        self.b_max[start_idx:start_idx + self.ny_N, 0] = u_N
    
    def save_to_mat(self, filename: str, varname: str = 'ocp'):
        """
        Save OCP data to MATLAB .mat file.
        
        Args:
            filename: Output filename (should end with .mat)
            varname: Variable name in the .mat file (default: 'ocp')
        """
        # Create struct with all required fields
        ocp_struct = {
            'AB': self.AB,
            'CD': self.CD,
            'CN': self.CN,
            'H': self.H,
            'qr': self.qr,
            'b': self.b,
            'b_min': self.b_min,
            'b_max': self.b_max,
        }
        
        # Save to .mat file with struct format
        savemat(filename, {varname: ocp_struct}, oned_as='column')
        print(f"OCP data saved to {filename}")
        print(f"Dimensions: N={self.N}, nx={self.nx}, nu={self.nu}, ny={self.ny}, ny_N={self.ny_N}")


def create_example_ocp():
    """Create a simple example OCP for testing."""
    N = 10   # Time horizon
    nx = 2   # State dimension
    nu = 1   # Control dimension
    ny = 2   # Output constraint dimension
    ny_N = 2 # Terminal constraint dimension
    
    ocp = OCPData(N, nx, nu, ny, ny_N)
    
    # Set cost matrices (LQR-like)
    Q = np.eye(nx)
    R = np.eye(nu) * 0.1
    S = np.zeros((nu, nx))
    q = np.zeros(nx)
    r = np.zeros(nu)
    
    for i in range(N):
        ocp.set_stage_cost(i, Q, R, S, q, r)
    
    # Terminal cost
    Q_N = 10 * np.eye(nx)
    q_N = np.zeros(nx)
    ocp.set_terminal_cost(Q_N, q_N)
    
    # Dynamics: simple double integrator
    dt = 0.1
    A = np.array([[1, dt], [0, 1]])
    B = np.array([[0.5 * dt**2], [dt]])
    b = np.zeros(nx)
    
    for i in range(N):
        ocp.set_dynamics(i, A, B, b)
    
    # Initial state
    b0 = np.array([1.0, 0.0])
    ocp.set_initial_state(b0)
    
    # State and control constraints: -10 ≤ x ≤ 10, -5 ≤ u ≤ 5
    C = np.eye(ny, nx)  # First two states
    D = np.zeros((ny, nu))
    l = -10 * np.ones(ny)
    u = 10 * np.ones(ny)
    
    for i in range(N):
        ocp.set_stage_constraints(i, C, D, l, u)
    
    # Terminal constraints
    C_N = np.eye(ny_N, nx)
    l_N = -10 * np.ones(ny_N)
    u_N = 10 * np.ones(ny_N)
    ocp.set_terminal_constraints(C_N, l_N, u_N)
    
    return ocp

def create_cont_double_integrator(N=100):
    """Create a simple example OCP for testing."""
    nx = 4   # State dimension
    nu = 2   # Control dimension
    ny = nu   # Output constraint dimension
    ny_N = nu # Terminal constraint dimension
    
    ocp = OCPData(N, nx, nu, ny, ny_N)
    
    # Set cost matrices (LQR-like)
    Q = np.eye(nx)
    R = np.eye(nu) * 0.1
    S = np.zeros((nu, nx))
    q = np.zeros(nx)
    r = np.zeros(nu)
    
    for i in range(N):
        ocp.set_stage_cost(i, Q, R, S, q, r)
    
    # Terminal cost
    Q_N = 10 * np.eye(nx)
    q_N = np.zeros(nx)
    ocp.set_terminal_cost(Q_N, q_N)
    
    # Dynamics: simple double integrator
    dt = 0.1
    A_hat = np.array([[1, dt], [0, 1]])
    A_bar = A_hat
    B_hat = np.array([[0.5 * dt**2], [dt]])
    B_bar = B_hat
    b = np.zeros(nx)
    
    
    for i in range(N):
        if i == 0:
            A = np.vstack([np.hstack([A_hat, np.zeros((2, 2))]), np.hstack([np.zeros((2, 2)), A_bar])])
            B = np.vstack([np.hstack([B_hat, np.zeros((2, 1))]), np.hstack([ B_bar, np.zeros((2, 1))])])
        else:
            A = np.vstack([np.hstack([A_hat, np.zeros((2, 2))]), np.hstack([np.zeros((2, 2)), A_bar])])
            B = np.vstack([np.hstack([B_hat, np.zeros((2, 1))]), np.hstack([ np.zeros((2, 1)), B_bar])])       
        ocp.set_dynamics(i, A, B, b)
    
    # Initial state
    b0 = np.array([1.0, 0.0, 1.0, 0.0])
    ocp.set_initial_state(b0)
    
    C =  np.zeros((ny, nx))  # First two states
    D = np.zeros((ny, nu))
    D = np.eye(nu)
    l = -0.1 * np.ones(ny)
    l[1] = -0.05 
    u = 0.1 * np.ones(ny)
    u[1] = 0.05
    print(u)
    print(D)
    for i in range(N):
        ocp.set_stage_constraints(i, C, D, l, u)
    
    # Terminal constraints
    C_N = np.zeros((ny_N, nx))
    l_N = -0.05 * np.ones(ny_N)
    l_N[2:] = -0.01 * np.ones(ny_N - 1)

    u_N = 0.05 * np.ones(ny_N)
    u_N[2:] = 0.01 * np.ones(ny_N - 1)
    ocp.set_terminal_constraints(C_N, l_N, u_N)
    
    return ocp
def create_cont_double_integrator_combined(N=100):
    """Create a simple example OCP for testing."""
    fanout = 2
    nx = 2   # State dimension
    nu = 1   # Control dimension
    ny = 0   # Output constraint dimension
    ny_N = 0 # Terminal constraint dimension
    
    ocp_full = OCPData(N, fanout * nx, fanout * nu, fanout * ny, fanout * ny_N)
    ocps = []
    Qs = []
    Rs = []
    Ss = []
    qs = []
    rs = []
    QNs = []
    qNs = []
    As = []
    Bs = []
    bs = []
    b0s= []
    for fan in range(fanout):
        ocp=OCPData(N, nx, nu, ny, ny_N)
        # Set cost matrices (LQR-like)
        Q = np.eye(nx) * (fan+1)**2
        R = np.eye(nu) * 0.1 / ((fan+1)**2)
        S = np.zeros((nu, nx))
        q = np.zeros(nx)
        r = np.zeros(nu)
        Qs.append(Q)
        Rs.append(R)
        Ss.append(S)
        qs.append(q)
        rs.append(r)
        for i in range(N):
         
            ocp.set_stage_cost(i, Q, R, S, q, r)
       
        # Terminal cost
        Q_N = 10 * np.eye(nx) * (fan+1)**2
        q_N = np.zeros(nx)
        QNs.append(Q_N)
        qNs.append(q_N)
        ocp.set_terminal_cost(Q_N, q_N)
        
        # Dynamics: simple double integrator
        if nx == 2:
            dt = 0.1
            A = np.array([[1, dt], [0, 1]])
            B = np.array([[0.5 * dt**2], [dt]])
            b = np.zeros(nx)
        else:
            A = np.eye(nx)
            B = np.eye(nu, nx)
            b = np.zeros(nx)
        As.append(A)
        Bs.append(B)
        bs.append(b)
        for i in range(N):
            ocp.set_dynamics(i, A, B, b)
            
        # Initial state
        b0 = np.zeros(nx)
        b0[0] = 1.0
        ocp.set_initial_state(b0)
        b0s.append(b0)
        print(f"Fanout {fan}: H=\n{ocp.H[:,:,0]}")
        ocp.save_to_mat(f"python/cmpc/ocp_data{N}_{fan}.mat", "ocp")
    Q_full = np.array(block_diag(*Qs))
    R_full = np.array(block_diag(*Rs))
    S_full = np.array(block_diag(*Ss))
    q_full = np.hstack(qs)
    r_full = np.hstack(rs)
    QN_full = np.array(block_diag(*QNs))
    qN_full = np.hstack(qNs)
    A_full = np.array(block_diag(*As))
    B_full = np.array(block_diag(*Bs))
    B0_full = np.zeros((fanout * nx, fanout * nu))
    B0_full[:, :nu] = np.vstack(Bs)
    b0_full = np.hstack(b0s)
    b_full = np.hstack(bs)
    for i in range(N):
        if i == 0:
            ocp_full.set_initial_state(b0_full)
            ocp_full.set_dynamics(i, A_full, B0_full, b_full)
        else:
            ocp_full.set_dynamics(i, A_full, B_full, b_full)
        ocp_full.set_stage_cost(i, Q_full, R_full, S_full, q_full, r_full)
    ocp_full.set_terminal_cost(QN_full, qN_full)
    ocp_full.save_to_mat(f"python/cmpc/ocp_data{N}_combined.mat", "ocp")
    print(A_full)
    print(B_full)
    print(B0_full)
    return ocp_full
if __name__ == "__main__":
    # Create and save example OCP
    N=32
    ocp = create_cont_double_integrator_combined(N)
    # ocp.save_to_mat(f"python/cmpc/ocp_data{N}.mat", "ocp")
    
    print("\nExample usage:")
    print("=" * 60)
    print("# Create OCP with your dimensions")
    print("ocp = OCPData(N=20, nx=4, nu=2, ny=3, ny_N=2)")
    print()
    print("# Set cost for each stage")
    print("for i in range(N):")
    print("    ocp.set_stage_cost(i, Q, R, S, q, r)")
    print()
    print("# Set terminal cost")
    print("ocp.set_terminal_cost(Q_N, q_N)")
    print()
    print("# Set dynamics for each stage")
    print("for i in range(N):")
    print("    ocp.set_dynamics(i, A, B, b)")
    print()
    print("# Set initial state")
    print("ocp.set_initial_state(b0)")
    print()
    print("# Set constraints for each stage")
    print("for i in range(N):")
    print("    ocp.set_stage_constraints(i, C, D, l, u)")
    print()
    print("# Set terminal constraints")
    print("ocp.set_terminal_constraints(C_N, l_N, u_N)")
    print()
    print("# Save to .mat file")
    print("ocp.save_to_mat('my_ocp.mat', 'ocp')")
    
    def create_cont_double_integrator_combined(N=100):
    """Create a simple example OCP for testing."""
    fanout = 2
    nx = 2   # State dimension
    nu = 1   # Control dimension
    ny = 0   # Output constraint dimension
    ny_N = 0 # Terminal constraint dimension
    
    ocp_full = OCPData(N, fanout * nx, fanout * nu, fanout * ny, fanout * ny_N)
    ocps = []
    Qs = []
    Rs = []
    Ss = []
    qs = []
    rs = []
    QNs = []
    qNs = []
    As = []
    Bs = []
    bs = []
    b0s= []
    for fan in range(fanout):
        ocp=OCPData(N, nx, nu, ny, ny_N)
        # Set cost matrices (LQR-like)
        Q = np.eye(nx) * (fan+1)**2
        R = np.eye(nu) * 0.1 / ((fan+1)**2)
        S = np.zeros((nu, nx))
        q = np.zeros(nx)
        r = np.zeros(nu)
        Qs.append(Q)
        Rs.append(R)
        Ss.append(S)
        qs.append(q)
        rs.append(r)
        for i in range(N):
         
            ocp.set_stage_cost(i, Q, R, S, q, r)
       
        # Terminal cost
        Q_N = 10 * np.eye(nx) * (fan+1)**2
        q_N = np.zeros(nx)
        QNs.append(Q_N)
        qNs.append(q_N)
        ocp.set_terminal_cost(Q_N, q_N)
        
        # Dynamics: simple double integrator
        if nx == 2:
            dt = 0.1
            A = np.array([[1, dt], [0, 1]])
            B = np.array([[0.5 * dt**2], [dt]])
            b = np.zeros(nx)
        else:
            A = np.eye(nx)
            B = np.eye(nu, nx)
            b = np.zeros(nx)
        As.append(A)
        Bs.append(B)
        bs.append(b)
        for i in range(N):
            ocp.set_dynamics(i, A, B, b)
            
        # Initial state
        b0 = np.zeros(nx)
        b0[0] = 1.0
        ocp.set_initial_state(b0)
        b0s.append(b0)
        print(f"Fanout {fan}: H=\n{ocp.H[:,:,0]}")
        ocp.save_to_mat(f"python/cmpc/ocp_data{N}_{fan}.mat", "ocp")
    Q_full = np.array(block_diag(*Qs))
    R_full = np.array(block_diag(*Rs))
    S_full = np.array(block_diag(*Ss))
    q_full = np.hstack(qs)
    r_full = np.hstack(rs)
    QN_full = np.array(block_diag(*QNs))
    qN_full = np.hstack(qNs)
    A_full = np.array(block_diag(*As))
    B_full = np.array(block_diag(*Bs))
    B0_full = np.zeros((fanout * nx, fanout * nu))
    B0_full[:, :nu] = np.vstack(Bs)
    b0_full = np.hstack(b0s)
    b_full = np.hstack(bs)
    for i in range(N):
        if i == 0:
            ocp_full.set_initial_state(b0_full)
            ocp_full.set_dynamics(i, A_full, B0_full, b_full)
        else:
            ocp_full.set_dynamics(i, A_full, B_full, b_full)
        ocp_full.set_stage_cost(i, Q_full, R_full, S_full, q_full, r_full)
    ocp_full.set_terminal_cost(QN_full, qN_full)
    ocp_full.save_to_mat(f"python/cmpc/ocp_data{N}_combined.mat", "ocp")
    print(A_full)
    print(B_full)
    print(B0_full)
    return ocp_full
if __name__ == "__main__":
    # Create and save example OCP
    N=32
    
    ocp = create_cont_double_integrator_combined(N)
    # ocp.save_to_mat(f"python/cmpc/ocp_data{N}.mat", "ocp")
    
    print("\nExample usage:")
    print("=" * 60)
    print("# Create OCP with your dimensions")
    print("ocp = OCPData(N=20, nx=4, nu=2, ny=3, ny_N=2)")
    print()
    print("# Set cost for each stage")
    print("for i in range(N):")
    print("    ocp.set_stage_cost(i, Q, R, S, q, r)")
    print()
    print("# Set terminal cost")
    print("ocp.set_terminal_cost(Q_N, q_N)")
    print()
    print("# Set dynamics for each stage")
    print("for i in range(N):")
    print("    ocp.set_dynamics(i, A, B, b)")
    print()
    print("# Set initial state")
    print("ocp.set_initial_state(b0)")
    print()
    print("# Set constraints for each stage")
    print("for i in range(N):")
    print("    ocp.set_stage_constraints(i, C, D, l, u)")
    print()
    print("# Set terminal constraints")
    print("ocp.set_terminal_constraints(C_N, l_N, u_N)")
    print()
    print("# Save to .mat file")
    print("ocp.save_to_mat('my_ocp.mat', 'ocp')")
