"""High-level Python interface for FanCyQPALM."""

from dataclasses import dataclass
import os
from typing import Any, Optional, Sequence, Tuple

import numpy as np
from numpy.typing import NDArray

from . import cyqlone as _native
from .common import CyQPALMBackendSettings, OCP, Settings, SolverStatus


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class FanKKTError:
    stationarity: float
    inequality_residual: float
    equality_residual: float
    complementarity: float


@dataclass(frozen=True)
class FanBackendStats:
    num_factor: int
    num_updates: int
    rank_updates: int


@dataclass(frozen=True)
class FanBranchResult:
    states: FloatArray
    inputs: FloatArray
    dynamics_multipliers: FloatArray
    inequality_multipliers: Tuple[FloatArray, ...]
    raw_solution: FloatArray
    raw_dynamics_multipliers: FloatArray
    raw_inequality_multipliers: FloatArray


@dataclass(frozen=True)
class FanResult:
    shared_input: FloatArray
    branches: Tuple[FanBranchResult, ...]
    raw_solution: FloatArray
    raw_dynamics_multipliers: FloatArray
    raw_inequality_multipliers: FloatArray
    kkt_error: FanKKTError


class FanOCP:
    """A fixed collection of mutable OCP branches."""

    def __init__(self, branches: Sequence[OCP]):
        self.branches = tuple(branches)
        self._dimensions = self._validate()

    def _validate(self) -> Tuple[int, int, int, int, int]:
        if not self.branches:
            raise ValueError("FanOCP must contain at least one branch")
        if not all(isinstance(branch, OCP) for branch in self.branches):
            raise TypeError("FanOCP branches must be cyqlone.OCP instances")

        dimensions = self.branches[0].dim
        if dimensions[0] < 2:
            raise ValueError("FanOCP branches must have a horizon length of at least two")
        if any(branch.dim != dimensions for branch in self.branches[1:]):
            raise ValueError("All FanOCP branches must have identical dimensions")
        return dimensions

    def _validate_unchanged_dimensions(self) -> None:
        if self._validate() != self._dimensions:
            raise ValueError("FanOCP dimensions cannot change after construction")

    def __len__(self) -> int:
        return len(self.branches)


def _is_power_of_two(value: int) -> bool:
    return value > 0 and value & (value - 1) == 0


def _select_native_solver(processors_per_branch: int) -> Any:
    override = os.getenv("CYQLONE_FAN_VECTOR_LENGTH")
    if override is not None:
        try:
            vector_length = int(override)
        except ValueError as exc:
            raise ValueError("CYQLONE_FAN_VECTOR_LENGTH must be 1, 2, 4, or 8") from exc
        if vector_length not in (1, 2, 4, 8):
            raise ValueError("CYQLONE_FAN_VECTOR_LENGTH must be 1, 2, 4, or 8")
        candidates = [vector_length]
    elif not _is_power_of_two(processors_per_branch):
        candidates = [1]
    else:
        variant = getattr(_native, "variant", "_generic")
        candidates = [8, 4, 2, 1] if variant == "_avx512" else [4, 2, 1]
        if variant not in ("_avx2", "_avx512"):
            candidates = [1]

    for vector_length in candidates:
        module_name = "scalar" if vector_length == 1 else f"simd{vector_length}"
        module = getattr(_native, module_name, None)
        if module is not None and hasattr(module, "_FanCyQPALM"):
            return module._FanCyQPALM
    raise RuntimeError("No compatible FanCyQPALM implementation is available")


class FanCyQPALM:
    """QPALM solver for a fan of OCP branches with a shared first input."""

    def __init__(
        self,
        problem: FanOCP,
        processors_per_branch: int = 1,
        backend_settings: Optional[CyQPALMBackendSettings] = None,
        settings: Optional[Settings] = None,
    ):
        if not isinstance(problem, FanOCP):
            raise TypeError("problem must be a FanOCP")
        if not isinstance(processors_per_branch, int) or processors_per_branch <= 0:
            raise ValueError("processors_per_branch must be a positive integer")

        problem._validate_unchanged_dimensions()
        native_type = _select_native_solver(processors_per_branch)
        self._problem = problem
        self._native_solver = native_type(
            list(problem.branches),
            processors_per_branch,
            backend_settings if backend_settings is not None else CyQPALMBackendSettings(),
            settings if settings is not None else Settings(),
        )
        self._result: Optional[FanResult] = None
        self._status: Optional[SolverStatus] = None

    @property
    def problem(self) -> FanOCP:
        return self._problem

    @property
    def status(self) -> Optional[SolverStatus]:
        return self._status

    @property
    def has_result(self) -> bool:
        return bool(self._native_solver.has_result)

    @property
    def num_variables(self) -> int:
        return self._native_solver.num_variables

    @property
    def num_equality_constraints(self) -> int:
        return self._native_solver.num_equality_constraints

    @property
    def num_inequality_constraints(self) -> int:
        return self._native_solver.num_inequality_constraints

    @property
    def stats(self) -> Any:
        return self._native_solver.stats

    @property
    def backend_stats(self) -> Optional[FanBackendStats]:
        stats = self._native_solver.backend_stats
        if stats is None:
            return None
        return FanBackendStats(int(stats[0]), int(stats[1]), int(stats[2]))

    @property
    def equality_constraints(self) -> FloatArray:
        return np.asarray(self._native_solver.equality_constraints)

    @property
    def inequality_constraints(self) -> FloatArray:
        return np.asarray(self._native_solver.inequality_constraints)

    def solve(self) -> SolverStatus:
        self._result = None
        self._status = self._native_solver.solve()
        return self._status

    def __call__(self) -> SolverStatus:
        return self.solve()

    def update_data(self) -> None:
        """Synchronize in-place branch data changes with the existing solver."""
        self._problem._validate_unchanged_dimensions()
        self._native_solver.update_data(list(self._problem.branches))
        self._result = None
        self._status = None

    def warm_start_solution(self) -> None:
        self._native_solver.warm_start_solution()

    def stop(self) -> None:
        """Interrupt a running solve and permanently stop this solver instance."""
        self._native_solver.stop()

    @property
    def result(self) -> FanResult:
        if self._result is None:
            self._result = self._build_result(self._native_solver.result)
        return self._result

    def _build_result(self, native_result: Any) -> FanResult:
        raw_solution = np.asarray(native_result[0])
        raw_inequality = np.asarray(native_result[1])
        raw_dynamics = np.asarray(native_result[2])
        branch_results = []

        for branch, native_branch in zip(self._problem.branches, native_result[3]):
            horizon, nx, nu, ny, ny_terminal = branch.dim
            branch_solution = np.asarray(native_branch[0])
            branch_inequality = np.asarray(native_branch[1])
            branch_dynamics = np.asarray(native_branch[2])

            states = np.empty((horizon + 1, nx), dtype=np.float64)
            inputs = np.empty((horizon, nu), dtype=np.float64)
            stage_width = nx + nu
            for stage in range(horizon):
                offset = stage * stage_width
                states[stage] = branch_solution[offset : offset + nx]
                inputs[stage] = branch_solution[offset + nx : offset + stage_width]
            states[horizon] = branch_solution[horizon * stage_width :]

            inequality_multipliers = tuple(
                branch_inequality[stage * ny : (stage + 1) * ny]
                for stage in range(horizon)
            ) + (branch_inequality[horizon * ny : horizon * ny + ny_terminal],)

            branch_results.append(
                FanBranchResult(
                    states=states,
                    inputs=inputs,
                    dynamics_multipliers=branch_dynamics.reshape(horizon + 1, nx),
                    inequality_multipliers=inequality_multipliers,
                    raw_solution=branch_solution,
                    raw_dynamics_multipliers=branch_dynamics,
                    raw_inequality_multipliers=branch_inequality,
                )
            )

        kkt_error = FanKKTError(
            stationarity=float(native_result[4]),
            inequality_residual=float(native_result[5]),
            equality_residual=float(native_result[6]),
            complementarity=float(native_result[7]),
        )
        nu = self._problem.branches[0].nu
        return FanResult(
            shared_input=raw_solution[:nu].copy(),
            branches=tuple(branch_results),
            raw_solution=raw_solution,
            raw_dynamics_multipliers=raw_dynamics,
            raw_inequality_multipliers=raw_inequality,
            kkt_error=kkt_error,
        )


__all__ = [
    "FanBackendStats",
    "FanBranchResult",
    "FanCyQPALM",
    "FanKKTError",
    "FanOCP",
    "FanResult",
]
