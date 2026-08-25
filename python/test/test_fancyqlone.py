import numpy as np
import numpy.linalg as la
import pytest

from cyqlone import (
    CyQPALMBackendSettings,
    FanCyQPALM,
    FanOCP,
    OCP,
    Settings,
    SolverStatus,
    WarmStartingStrategy,
)


def create_branch(model_scale: float, horizon: int = 8) -> OCP:
    nx, nu, ny, ny_terminal = 2, 1, 1, 1
    AB = np.empty((horizon, nx, nx + nu), order="F")
    CD = np.zeros((horizon, ny, nx + nu), order="F")
    QRS = np.zeros((horizon, nx + nu, nx + nu), order="F")
    A = np.array([[1.0, 0.1], [0.0, 0.98]])
    B = model_scale * np.array([[0.005], [0.1]])
    for stage in range(horizon):
        AB[stage, :, :nx] = A
        AB[stage, :, nx:] = B
        CD[stage, 0, nx] = 1.0
        QRS[stage, :nx, :nx] = np.diag([3.0, 0.4])
        QRS[stage, nx:, nx:] = 0.2

    rhs_eq = np.zeros((horizon + 1) * nx)
    rhs_eq[:nx] = [-0.4, 0.1]
    rhs_lb = np.full(horizon * ny + ny_terminal, -2.0)
    rhs_ub = np.full(horizon * ny + ny_terminal, 2.0)
    qr = np.zeros(horizon * (nx + nu) + nx)
    for stage in range(horizon):
        qr[stage * (nx + nu)] = -3.0
    qr[horizon * (nx + nu)] = -6.0

    return OCP(
        AB=AB,
        CD=CD,
        CN=np.asfortranarray([[1.0, 0.0]]),
        QRS=QRS,
        QN=np.asfortranarray(np.diag([6.0, 0.8])),
        rhs_eq=rhs_eq,
        rhs_lb=rhs_lb,
        rhs_ub=rhs_ub,
        qr=qr,
    )


def create_solver() -> tuple[FanOCP, FanCyQPALM]:
    fan = FanOCP([create_branch(0.9), create_branch(1.1)])
    backend_settings = CyQPALMBackendSettings()
    backend_settings.max_update_count = 0
    backend_settings.strategy = WarmStartingStrategy.Shift
    settings = Settings()
    settings.max_outer_iter = 40
    settings.max_total_inner_iter = 500
    settings.tolerance = 1e-9
    settings.dual_tolerance = 1e-9
    settings.eq_constr_tolerance = 1e-9
    return fan, FanCyQPALM(fan, 1, backend_settings, settings)


def assert_branch_feasible(branch: OCP, states: np.ndarray, inputs: np.ndarray) -> None:
    for stage in range(branch.N_horiz):
        expected = (
            branch.A(stage) @ states[stage]
            + branch.B(stage) @ inputs[stage]
            + branch.b(stage + 1)
        )
        assert la.norm(states[stage + 1] - expected, np.inf) < 1e-7
        output = branch.C(stage) @ states[stage] + branch.D(stage) @ inputs[stage]
        assert np.all(output >= branch.rhs_lb[stage * branch.ny : (stage + 1) * branch.ny] - 1e-8)
        assert np.all(output <= branch.rhs_ub[stage * branch.ny : (stage + 1) * branch.ny] + 1e-8)
    terminal_output = branch.C(branch.N_horiz) @ states[-1]
    assert np.all(terminal_output >= branch.rhs_lb[-branch.ny_N :] - 1e-8)
    assert np.all(terminal_output <= branch.rhs_ub[-branch.ny_N :] + 1e-8)


def test_fancyqlone_solution_reconstruction():
    fan, solver = create_solver()
    assert solver.status is None
    assert not solver.has_result
    with pytest.raises(RuntimeError, match="solve first"):
        _ = solver.result

    assert solver.solve() == SolverStatus.Converged
    result = solver.result
    assert result.shared_input.shape == (fan.branches[0].nu,)
    assert len(result.branches) == len(fan)
    assert solver.stats is not None
    assert solver.backend_stats is not None

    for branch, branch_result in zip(fan.branches, result.branches):
        assert branch_result.states.shape == (branch.N_horiz + 1, branch.nx)
        assert branch_result.inputs.shape == (branch.N_horiz, branch.nu)
        assert branch_result.dynamics_multipliers.shape == (branch.N_horiz + 1, branch.nx)
        assert np.allclose(branch_result.states[0], branch.x0)
        assert np.allclose(branch_result.inputs[0], result.shared_input)
        assert_branch_feasible(branch, branch_result.states, branch_result.inputs)

    assert la.norm(solver.equality_constraints, np.inf) < 1e-7
    assert result.kkt_error.equality_residual < 1e-7
    assert result.kkt_error.inequality_residual < 1e-7
    assert result.kkt_error.stationarity < 1e-7
    assert result.kkt_error.complementarity < 1e-7


def test_fancyqlone_updates_existing_problem_and_solver():
    fan, solver = create_solver()
    assert solver.solve() == SolverStatus.Converged
    previous_solution = solver.result.raw_solution.copy()
    problem_identity = id(fan)
    solver_identity = id(solver)
    branch_identities = tuple(map(id, fan.branches))

    for branch_index, branch in enumerate(fan.branches):
        branch.x0[:] = [0.2, -0.15]
        for stage in range(branch.N_horiz):
            branch.A(stage)[:, :] = [[1.0, 0.12], [0.0, 0.95 - 0.01 * branch_index]]
            branch.B(stage)[:, :] *= 0.8 + 0.1 * branch_index
            branch.C(stage)[:, :] = [[0.05 * (branch_index + 1), -0.02]]
            branch.D(stage)[:, :] = 1.0
            branch.Q(stage)[:, :] = np.diag([4.0 + stage, 0.6])
            branch.R(stage)[:, :] = 0.35
            branch.S(stage)[:, :] = [[0.01, -0.005]]
            branch.q(stage)[:] = [-2.0, 0.0]
            branch.r(stage)[:] = 0.01 * (branch_index + 1)
            branch.b(stage + 1)[:] = [0.0, 0.002 * (2 * branch_index - 1)]
        branch.Q(branch.N_horiz)[:, :] = np.diag([9.0, 1.0])
        branch.q(branch.N_horiz)[:] = [-4.0, 0.0]
        branch.rhs_lb[:] = -1.25
        branch.rhs_ub[:] = 1.25
        branch.rhs_ub[: branch.ny] = 0.25

    solver.warm_start_solution()
    solver.update_data()
    assert id(fan) == problem_identity
    assert id(solver) == solver_identity
    assert tuple(map(id, fan.branches)) == branch_identities
    assert not solver.has_result
    assert solver.status is None
    with pytest.raises(RuntimeError, match="solve first"):
        _ = solver.result

    assert solver.solve() == SolverStatus.Converged
    updated_result = solver.result
    assert not np.allclose(previous_solution, updated_result.raw_solution)
    for branch, branch_result in zip(fan.branches, updated_result.branches):
        assert np.allclose(branch_result.states[0], branch.x0)
        assert np.allclose(branch_result.inputs[0], updated_result.shared_input)
        assert_branch_feasible(branch, branch_result.states, branch_result.inputs)
    assert any(
        la.norm(branch.inequality_multipliers[0], np.inf) > 1e-8
        for branch in updated_result.branches
    )
    assert updated_result.kkt_error.stationarity < 1e-7
    assert updated_result.kkt_error.complementarity < 1e-7


def test_fancyqlone_scalar_override(monkeypatch: pytest.MonkeyPatch):
    monkeypatch.setenv("CYQLONE_FAN_VECTOR_LENGTH", "1")
    _, solver = create_solver()
    assert solver.solve() == SolverStatus.Converged
    assert solver.result.kkt_error.stationarity < 1e-7


def test_fancyqlone_validates_problem_and_settings():
    with pytest.raises(ValueError, match="at least one"):
        FanOCP([])
    with pytest.raises(TypeError, match="cyqlone.OCP"):
        FanOCP([object()])
    with pytest.raises(ValueError, match="identical dimensions"):
        FanOCP([create_branch(1.0, 7), create_branch(1.0, 8)])
    with pytest.raises(ValueError, match="at least two"):
        FanOCP([create_branch(1.0, 1)])

    fan = FanOCP([create_branch(0.9), create_branch(1.1)])
    with pytest.raises(ValueError, match="positive integer"):
        FanCyQPALM(fan, 0)

    backend_settings = CyQPALMBackendSettings()
    backend_settings.strategy = WarmStartingStrategy.ShiftNoInequality
    with pytest.raises(ValueError, match="not supported"):
        FanCyQPALM(fan, backend_settings=backend_settings)
