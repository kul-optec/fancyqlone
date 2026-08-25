"""Closed-loop FanCyQPALM example with in-place OCP data updates."""

import argparse
import time

import numpy as np

from cyqlone import (
    CyQPALMBackendSettings,
    FanCyQPALM,
    FanOCP,
    OCP,
    Settings,
    SolverStatus,
    WarmStartingStrategy,
)


def create_branch(horizon: int, time_step: float, model_scale: float) -> OCP:
    nx, nu, ny, ny_terminal = 2, 1, 1, 0
    AB = np.empty((horizon, nx, nx + nu), order="F")
    CD = np.zeros((horizon, ny, nx + nu), order="F")
    QRS = np.zeros((horizon, nx + nu, nx + nu), order="F")

    A = np.array([[1.0, time_step], [0.0, 1.0]])
    B = model_scale * np.array([[0.5 * time_step**2], [time_step]])
    for stage in range(horizon):
        AB[stage, :, :nx] = A
        AB[stage, :, nx:] = B
        CD[stage, 0, nx] = 1.0
        QRS[stage, :nx, :nx] = np.diag([8.0, 0.5])
        QRS[stage, nx:, nx:] = 0.2

    rhs_eq = np.zeros((horizon + 1) * nx)
    rhs_lb = np.full(horizon * ny + ny_terminal, -1.5)
    rhs_ub = np.full(horizon * ny + ny_terminal, 1.5)
    qr = np.zeros(horizon * (nx + nu) + nx)
    return OCP(
        AB=AB,
        CD=CD,
        CN=np.empty((ny_terminal, nx), order="F"),
        QRS=QRS,
        QN=np.asfortranarray(np.diag([14.0, 1.0])),
        rhs_eq=rhs_eq,
        rhs_lb=rhs_lb,
        rhs_ub=rhs_ub,
        qr=qr,
    )


def update_prediction_data(
    fan: FanOCP,
    state: np.ndarray,
    mpc_step: int,
    time_step: float,
) -> None:
    target = 1.0 if mpc_step < 18 else -0.25
    model_scales = (0.85, 1.0, 1.15)
    disturbance_signs = (-1.0, 0.0, 1.0)

    for branch, model_scale, disturbance_sign in zip(
        fan.branches, model_scales, disturbance_signs
    ):
        branch.x0[:] = state
        branch.rhs_eq[branch.nx :] = 0.0

        for stage in range(branch.N_horiz):
            drag = 0.04 + 0.015 * np.sin(0.2 * (mpc_step + stage))
            A = np.array([[1.0, time_step], [0.0, 1.0 - drag * time_step]])
            B = model_scale * np.array([[0.5 * time_step**2], [time_step]])
            branch.A(stage)[:, :] = A
            branch.B(stage)[:, :] = B

            state_weight = 8.0 + 0.15 * stage
            branch.Q(stage)[:, :] = np.diag([state_weight, 0.5])
            branch.R(stage)[:, :] = 0.2 + 0.01 * stage
            branch.q(stage)[:] = np.array([-state_weight * target, 0.0])
            branch.r(stage)[:] = 0.0

            disturbance = disturbance_sign * 0.015 * np.array([0.5 * time_step**2, time_step])
            branch.b(stage + 1)[:] = disturbance

        terminal_weight = 14.0 + 0.2 * mpc_step
        branch.Q(branch.N_horiz)[:, :] = np.diag([terminal_weight, 1.0])
        branch.q(branch.N_horiz)[:] = np.array([-terminal_weight * target, 0.0])
        branch.rhs_lb[:] = -1.5
        branch.rhs_ub[:] = 1.5


def run_mpc(num_steps: int = 35, plot: bool = True) -> tuple[np.ndarray, np.ndarray]:
    time_step = 0.15
    N=64
    branches = [create_branch(N, time_step, scale) for scale in (0.85, 1.0, 1.15)]
    fan = FanOCP(branches)

    backend_settings = CyQPALMBackendSettings()
    backend_settings.strategy = WarmStartingStrategy.Shift
    backend_settings.max_update_count = 0
    settings = Settings()
    settings.max_outer_iter = 40
    settings.max_total_inner_iter = 500
    settings.tolerance = 1e-8
    settings.dual_tolerance = 1e-8
    settings.eq_constr_tolerance = 1e-8
    settings.verbose = False

    solver = FanCyQPALM(
        fan,
        processors_per_branch=2,
        backend_settings=backend_settings,
        settings=settings,
    )

    state = np.array([-0.8, 0.0])
    state_history = [state.copy()]
    input_history = []

    for mpc_step in range(num_steps):
        start_time = time.time()
        update_prediction_data(fan, state, mpc_step, time_step)
        solver.update_data()
        status = solver.solve()
        if status != SolverStatus.Converged:
            raise RuntimeError(f"FanCyQPALM failed at MPC step {mpc_step}: {status}")

        result = solver.result
        control = result.shared_input.copy()
        if not all(np.allclose(branch.inputs[0], control) for branch in result.branches):
            raise RuntimeError("Branches do not share the first control input")

        solver.warm_start_solution()
        actual_drag = 0.05 + 0.01 * np.sin(0.2 * mpc_step)
        actual_A = np.array([[1.0, time_step], [0.0, 1.0 - actual_drag * time_step]])
        actual_B = np.array([[0.5 * time_step**2], [time_step]])
        state = actual_A @ state + actual_B @ control
        state_history.append(state.copy())
        input_history.append(control.copy())

        error = result.kkt_error
        end_time = time.time()
        print(
            
            f"step={mpc_step:02d} status={status} input={control[0]:+.4f} "
            f"state=({state[0]:+.4f}, {state[1]:+.4f}) "
            f"inner={solver.stats.inner_iter} "
            f"outer={solver.stats.outer_iter} "
            f"time={solver.stats.timings.total.wall_time.microseconds/1000} ms "
            f"total_time={1000*(end_time - start_time):.3f} ms "
            f"kkt={max(error.stationarity, error.equality_residual):.2e}"
        )

    states = np.asarray(state_history)
    inputs = np.asarray(input_history)
    if plot:
        import matplotlib.pyplot as plt

        time_states = time_step * np.arange(states.shape[0])
        time_inputs = time_step * np.arange(inputs.shape[0])
        figure, (state_axis, input_axis) = plt.subplots(2, 1, sharex=True)
        state_axis.plot(time_states, states[:, 0], label="position")
        state_axis.plot(time_states, states[:, 1], label="velocity")
        state_axis.axhline(1.0, color="black", linestyle="--", linewidth=1, label="first target")
        state_axis.axhline(-0.25, color="gray", linestyle="--", linewidth=1, label="second target")
        state_axis.legend()
        state_axis.grid(True)
        input_axis.step(time_inputs, inputs[:, 0], where="post", label="shared input")
        input_axis.axhline(1.5, color="black", linestyle=":")
        input_axis.axhline(-1.5, color="black", linestyle=":")
        input_axis.set_xlabel("time [s]")
        input_axis.legend()
        input_axis.grid(True)
        figure.tight_layout()
        plt.show()
        plt.savefig("fancyqlone_mpc.png", dpi=300)

    return states, inputs


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--no-plot", action="store_true")
    parser.add_argument("--steps", type=int, default=35)
    arguments = parser.parse_args()
    run_mpc(num_steps=arguments.steps, plot=not arguments.no_plot)
