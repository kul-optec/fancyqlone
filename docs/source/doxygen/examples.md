# Examples {#examples}

- [Solving a block tridiagonal system](@ref solve-block-tridiagonal.cpp)
- [Solving an optimal control problem using Cyqlone](@ref solve-ocp.cpp)
- [Spring-mass OCP benchmark](@ref benchmarks/cyqpalm/spring-mass.cpp)
- [Standalone PCR solver](@ref test/test-pcr.cpp)

@example{lineno} solve-block-tridiagonal.cpp
@par Example demonstrating how to solve a block tridiagonal system in parallel

The system has the form
@f[
\begin{pmatrix}
M_0 & \tp{K_0} & 0 & 0 & \cdots & K_{N-1} \\
K_0 & M_1 & \tp{K_1} & 0 & \cdots & 0 \\
0 & K_1 & M_2 & \tp{K_2} & \cdots & 0 \\
0 & 0 & K_2 & M_3 & \cdots & 0 \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
\tp{K_{N-1}} & 0 & 0 & 0 & \cdots & M_{N-1}
\end{pmatrix}
\begin{pmatrix}
x^0 \\ x^1 \\ x^2 \\ x^3 \\ \vdots \\ x^{N-1}
\end{pmatrix}
=
\begin{pmatrix}
b^0 \\ b^1 \\ b^2 \\ b^3 \\ \vdots \\ b^{N-1}
\end{pmatrix}
@f]

We use @ref fancyqlone::TricyqleSolver to solve the system in parallel. Since this solver uses
vectorization using batched linear algebra operations and partitions the matrices and vectors
across multiple threads, each thread needs to pack its local portion of the system into batches
of matrices and vectors. In this example, we prepare the system in the batches of matrices
`M` and `K`, but in practice, it is often more efficient to prepare the system in parallel, writing
the local blocks into the solver's workspace directly.

The solution produced by this example is stored in a `.mat` file, which can be loaded and verified
using the Python script @ref solve-block-tridiagonal.py.

The example also demonstrates how to perform a factorization update, which is useful when solving
a sequence of related systems. The coefficient matrix is updated by the term
@f[
\begin{pmatrix}
B_0^{\phantom\top} & 0 & 0 & 0 & \cdots & F_{N-1}^{\phantom\top} \\
F_0^{\phantom\top} & B_1^{\phantom\top} & 0 & 0 & \cdots & 0 \\
0 & F_1^{\phantom\top} & B_2^{\phantom\top} & 0 & \cdots & 0 \\
0 & 0 & F_2^{\phantom\top} & B_3^{\phantom\top} & \cdots & 0 \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
0 & 0 & 0 & 0 & F_{N-2}^{\phantom\top} & B_{N-1}^{\phantom\top}
\end{pmatrix}
\begin{pmatrix}
S_0^{\phantom\top} \\
& S_1^{\phantom\top} \\
&& S_2^{\phantom\top} \\
&&& S_3^{\phantom\top} \\
&&&& \ddots \\
&&&&& S_{N-1}^{\phantom\top}
\end{pmatrix}
\begin{pmatrix}
B_0^\top & F_0^\top & 0 & 0 & \cdots & 0 \\
0 & B_1^\top & F_1^\top & 0 & \cdots & 0 \\
0 & 0 & B_2^\top & F_2^\top & \cdots & 0 \\
0 & 0 & 0 & B_3^\top & \cdots & 0 \\
\vdots & \vdots & \vdots & \vdots & \ddots & F_{N-2}^\top \\
F_{N-1}^\top & 0 & 0 & 0 & \cdots & B_{N-1}^\top
\end{pmatrix}
@f]

@example{lineno} solve-block-tridiagonal.py

@example{lineno} solve-ocp.cpp
@par Example demonstrating how to solve an optimal control problem using Cyqlone.

This example generates a random optimal control problem (without inequality constraints),
and solves the resulting KKT system using Cyqlone.

@example{lineno} benchmarks/cyqpalm/spring-mass.cpp
@par Benchmarks from the paper
@see @ref benchmarks/cyqpalm/README.md for instructions to reproduce the results from the paper.

@example{lineno} test/test-pcr.cpp
@par Standalone vectorized PCR solver (independent of the main CyqloneSolver).
