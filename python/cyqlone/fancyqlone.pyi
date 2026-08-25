from dataclasses import dataclass
from typing import Any, Optional, Sequence, Tuple

import numpy as np
from numpy.typing import NDArray

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
    branches: Tuple[OCP, ...]
    def __init__(self, branches: Sequence[OCP]) -> None: ...
    def __len__(self) -> int: ...

class FanCyQPALM:
    def __init__(
        self,
        problem: FanOCP,
        processors_per_branch: int = ...,
        backend_settings: Optional[CyQPALMBackendSettings] = ...,
        settings: Optional[Settings] = ...,
    ) -> None: ...
    @property
    def problem(self) -> FanOCP: ...
    @property
    def status(self) -> Optional[SolverStatus]: ...
    @property
    def has_result(self) -> bool: ...
    @property
    def num_variables(self) -> int: ...
    @property
    def num_equality_constraints(self) -> int: ...
    @property
    def num_inequality_constraints(self) -> int: ...
    @property
    def stats(self) -> Any: ...
    @property
    def backend_stats(self) -> Optional[FanBackendStats]: ...
    @property
    def equality_constraints(self) -> FloatArray: ...
    @property
    def inequality_constraints(self) -> FloatArray: ...
    @property
    def result(self) -> FanResult: ...
    def solve(self) -> SolverStatus: ...
    def __call__(self) -> SolverStatus: ...
    def update_data(self) -> None: ...
    def warm_start_solution(self) -> None: ...
    def stop(self) -> None: ...
