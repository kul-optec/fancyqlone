
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
branches =[]
backend_settings = CyQPALMBackendSettings()
settings = Settings()


# 1. Create the ocp problem
fan = FanOCP(branches)

# 2. Create the solver
solver = FanCyQPALM(
    fan,
    processors_per_branch=2,
    vector_length=4,
    backend_settings=backend_settings,
    settings=settings,
)

# 3. Update modified OCP data
solver.update_data()

# 4. Solve
status = solver.solve()

# 5. Access the result
result = solver.result
control = result.shared_input.copy()

# 6. check stats
stats = solver.stats
# 7. Prepare the next MPC iteration
solver.warm_start_solution()