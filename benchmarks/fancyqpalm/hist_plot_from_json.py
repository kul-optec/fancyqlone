#!/usr/bin/env python3
"""
Generate histogram plots using matplotlib and save to PDF.

This script loads benchmark results from a JSON file (Google Benchmark format)
and creates histogram plots showing the distribution of different metrics
across problem instances.
"""

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import json
from pathlib import Path
from typing import Optional, cast
import click
import re

# Configure matplotlib - enable LaTeX
plt.rcParams.update(
    {
        "text.usetex": True,
        "font.size": 11,
        "font.family": "serif",
    }
)

# List of colors for histograms (matching line_colors from perf_plot_pdf.py)
hist_colors = [
    "#1f77b4",  # blue
    "#ff7f0e",  # orange
    "#2ca02c",  # green
    "#d62728",  # red
    "#9467bd",  # purple
    "#e377c2",  # pink
    "#8c564b",  # brown
    "#7f7f7f",  # gray
    "#bcbd22",  # yellow-green
    "#17becf",  # turquoise
]

# Default metrics to plot
DEFAULT_METRICS = [
    "time",
    "stationarity",
    "constr_violation",
    "complementarity",
    "num_iter",
    "num_outer_iter",
    "time_per_iter",
]

# Pretty display names for metrics
METRIC_PRETTY = {
    "time": "total solver run time",
    "time_per_iter": "time per iteration",
    "num_iter": "number of iterations",
    "num_outer_iter": "number of outer iterations",
    "stationarity": "stationarity",
    "constr_violation": "constraint violation",
    "complementarity": "complementarity",
}

# Axis labels for metrics
METRIC_LABELS = {
    "time": "Time [ms]",
    "time_per_iter": "Time per iteration [ms]",
    "num_iter": "Number of iterations",
    "num_outer_iter": "Number of outer iterations",
    "stationarity": "Stationarity",
    "constr_violation": "Constraint violation",
    "complementarity": "Complementarity",
}


IGNORE_KEYS = [
    "name",
    "family_index",
    "per_family_instance_index",
    "run_name",
    "run_type",
    "repetitions",
    "threads",
    "aggregate_unit",
    "iterations",
]


def parse_benchmark_name(run_name: str) -> tuple[str, str, list[str]]:
    """
    Parse a benchmark name into problem_id, solver_id, and aggregate type.

    Example:
        "spring-mass(M=12,N=32,seed=0) - cyqlone(v=4,p=8)/process_time/manual_time"
        -> ("spring-mass(M=12,N=32,seed=0)", "cyqlone(v=4,p=8)", ["process_time", "manual_time"])

    Returns
    -------
    problem_id : str
        The problem identifier
    solver_id : str
        The solver identifier
    rest : list[str]
        The other parts after solver_id
    """
    # Split by "@" or " - " to separate problem from solver
    if "@" in run_name:
        parts = run_name.split("@", 1)
    else:
        parts = run_name.split(" - ", 1)
    if len(parts) != 2:
        raise ValueError(f"Cannot parse benchmark run_name: {run_name}")
    problem_id = parts[0]
    # Split the rest by "/" to get solver and timing info
    rest_parts = parts[1].split("/")
    solver_id = rest_parts[0]
    return problem_id, solver_id, rest_parts[1:]


def extract_dataset_from_problem(problem_id: str) -> str:
    """
    Extract dataset identifier from problem_id.

    Examples:
        "spring-mass(M=12,N=32,seed=0)" -> "MassSprings(M=12, N=32)"
        "centroidal-quadruped(N=32,J=4,seed=0)" -> "CentroidalQuadruped(N=32, J=4)"
    """
    # Group quadruped instances by horizon and number of branches, ignoring seed.
    match = re.search(r"centroidal-quadruped\(N=(\d+),\s*J=(\d+)\b", problem_id)
    if match:
        n, j = match.groups()
        return f"CentroidalQuadruped(N={n}, J={j})"

    # Extract M and N parameters
    match = re.search(r"M=(\d+).*?N=(\d+)", problem_id)
    if match:
        m, n = match.groups()
        return f"MassSprings(M={m}, N={n})"
    return problem_id


def load_data(file: str):
    """Load benchmark results from a JSON file."""
    json_file = Path(file)
    if not json_file.exists():
        raise FileNotFoundError(f"File not found: {json_file}")
    print(f"Loading data from: {json_file}")
    with open(json_file, "r") as f:
        data = json.load(f)
    benchmarks = data.get("benchmarks", [])

    # Convert to list of dicts
    records = []
    for bench in benchmarks:
        if bench.get("run_type") != "aggregate":
            continue

        problem_id, solver_id, _ = parse_benchmark_name(bench["run_name"])
        dataset_id = extract_dataset_from_problem(problem_id)

        record: dict = {
            "problem_id": problem_id,
            "solver_id": solver_id,
            "solver_name": solver_id,  # Use solver_id as name for now
            "dataset_id": dataset_id,
        }

        # Add all numeric metrics
        for key, value in bench.items():
            if key not in IGNORE_KEYS:
                if isinstance(value, (int, float, str)):
                    record[key] = value

        # Map some field names to match expected format
        if "real_time" in record:
            record["time"] = record["real_time"]
        if "iter" in record:
            record["num_iter"] = record["iter"]
        if "inner_iter" in record:
            record["num_iter"] = record["inner_iter"]
        if "outer_iter" in record:
            record["num_outer_iter"] = record["outer_iter"]
        # Constraint violation (use inequality_residual)
        if "inequality_residual" in record:
            record["constr_violation"] = record["inequality_residual"]
        # Check if success
        record["success"] = record.get("success", 1.0) >= 1.0

        records.append(record)

    # Convert to DataFrame
    df = pd.DataFrame(records)

    # Convert time to milliseconds if needed (vectorized)
    time_unit_multipliers = {"ns": 1e-6, "us": 1e-3, "s": 1e3}
    for unit, multiplier in time_unit_multipliers.items():
        mask = df["time_unit"] == unit
        df.loc[mask, "time"] *= multiplier
    df.loc[df["time_unit"].isin(time_unit_multipliers.keys()), "time_unit"] = "ms"
    if not (df["time_unit"] == "ms").all():
        raise ValueError("Unsupported time unit found in data")

    # Add computed metric (time per iteration) in ms
    if "time" in df.columns and "num_iter" in df.columns:
        df["time_per_iter"] = df["time"] / df["num_iter"]

    # Group by solver_id and aggregate_name
    all_results: dict[str, pd.DataFrame] = {}
    for solver_id, group_df in df.groupby("solver_id"):
        assert isinstance(solver_id, str)
        all_results[solver_id] = group_df.sort_values(
            by=["dataset_id", "problem_id"]
        ).reset_index(drop=True)

    return all_results


def extract_timings(
    all_results: dict[str, pd.DataFrame],
    solver: str,
    problem_pattern: Optional[str] = None,
):
    """
    Extract data for a specific solver and optionally filter by problem pattern.

    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    solver : str
        Solver ID to extract
    problem_pattern : str, optional
        Regex pattern to match problem_id. If None, returns all problems.

    Returns
    -------
    pd.DataFrame
        Filtered DataFrame for the solver
    """
    if solver not in all_results:
        raise ValueError(
            f"Solver '{solver}' not found. Available solvers: {list(all_results.keys())}"
        )

    df = all_results[solver]

    if problem_pattern is not None:
        df = df[df["problem_id"].str.match(problem_pattern, na=False)]

    return df


def format_dataset(dataset_id: str, all_datasets: Optional[list[str]] = None) -> tuple[str, Optional[str]]:
    """
    Format dataset string, showing only parameters that vary across datasets.
    
    Parameters
    ----------
    dataset_id : str
        Single dataset identifier like "MassSprings(M=12, N=128)" or
        "CentroidalQuadruped(N=32, J=4)"
    all_datasets : list[str], optional
        List of all dataset IDs to determine which parameters vary
    
    Returns
    -------
    tuple[Optional[str], Optional[str]]
        Formatted dataset string with LaTeX formatting for the current dataset, and for the fixed parameters.
    """
    quadruped_pattern = r"CentroidalQuadruped\(N=(\d+), J=(\d+)\)"
    match = re.fullmatch(quadruped_pattern, dataset_id)
    if match:
        labels = [f"${key}$=\\,{value}" for key, value in zip(("N", "J"), match.groups())]
        if all_datasets is None or len(all_datasets) <= 1:
            return ", ".join(labels), None

        extracted = pd.Series(all_datasets).str.extract(quadruped_pattern)
        varying_labels = []
        fixed_labels = []
        for index, label in enumerate(labels):
            if extracted[index].nunique() > 1:
                varying_labels.append(label)
            else:
                fixed_labels.append(label)
        return ", ".join(varying_labels), ", ".join(fixed_labels) or None

    # Extract M and N from current dataset
    match = re.search(r"MassSprings\(M=(\d+), N=(\d+)\)", dataset_id)
    print(match)
    if not match:
        return dataset_id, None
    
    current_m, current_n = match.groups()
    
    # If all_datasets provided, check which parameters vary
    if all_datasets is not None and len(all_datasets) > 1:
        # Use pandas to extract M and N values efficiently
        datasets_series = pd.Series(all_datasets)
        extracted = datasets_series.str.extract(r"MassSprings\(M=(\d+), N=(\d+)\)")
        all_m_values = set(extracted[0].dropna().unique())
        all_n_values = set(extracted[1].dropna().unique())
        
        # Build label with only varying parameters
        m_varies = len(all_m_values) > 1
        n_varies = len(all_n_values) > 1
        
        if m_varies and n_varies:
            return f"$M$=\\,{current_m}, $N$=\\,{current_n}", None
        elif m_varies:
            return f"$M$=\\,{current_m}", f"$N$=\\,{current_n}"
        elif n_varies:
            return f"$N$=\\,{current_n}", f"$M$=\\,{current_m}"
        else: # Nothing varies
            return "", f"$M$=\\,{current_m}, $N$=\\,{current_n}"
    
    # Default: show only N (for backward compatibility with current code)
    return f"$N$=\\,{current_n}", None


def format_solver_name(solver_name: str, plot: Optional[str] = None) -> str:
    sep = "\n" if plot == "box" else " "
    names = {
        "cyqlone(p=8,v=4)": fr"\textsc{{CyQPALM}}{sep}(cold)",
        "cyqlone(p=8,v=4,cm)": fr"\textsc{{CyQPALM}}{sep}(cold)",
        "cyqlone(p=8,v=4,cm,zero)": fr"\textsc{{CyQPALM}}{sep}(cold)",
        "cyqlone(p=8,v=4,cm,shift)": fr"\textsc{{CyQPALM}}{sep}(warm)",
        "cyqlone(p=8,v=4,cm,upd=0)": fr"\textsc{{CyQPALM}}{sep}(no updates)",
        "cyqlone(p=8,v=4,cm,zero,upd=0)": fr"\textsc{{CyQPALM}}{sep}(no updates)",
        "cyqlone(p=8,v=4,cm,shift,upd=0)": fr"\textsc{{CyQPALM}}{sep}(no updates)",
        "cyqlone(p=16,v=4,cm,zero)": fr"\textsc{{CyQPALM}}",
        "cyqlone(p=16,v=4,cm,shift)": fr"\textsc{{CyQPALM}}",
        "cyqlone(p=16,v=4,cm,zero,upd=0)": fr"\textsc{{CyQPALM}}{sep}(no updates)",
        "cyqlone(p=16,v=4,cm,shift,upd=0)": fr"\textsc{{CyQPALM}}{sep}(no updates)",
        "cyqlone(p=4,v=2,cm,zero)": fr"\textsc{{CyQPALM}}{sep}(cold)",
        "cyqlone(p=4,v=2,cm,shift)": fr"\textsc{{CyQPALM}}{sep}(warm)",
        "hpipm": fr"HPIPM{sep}(cold)",
        "hpipm(zero)": fr"HPIPM",
        "hpipm(shift)": fr"HPIPM{sep}(warm)",
        "piqp(multistage)": fr"PIQP",
        "treeqp(qpOasis)": fr"TreeQP",
        "treeqp(clip)": fr"TreeQP",
        "fancyqlone(p=8,v=4,cm,zero)": fr"\textsc{{FanCyQPALM}}{sep}(p=8,v=4)",
        "fancyqlone(p=8,v=1,cm,zero)": fr"\textsc{{FanCyQPALM}}{sep}(p=8,v=1)",
        "serial-fancyqlone(p=8,v=4,cm,zero)": fr"\textsc{{FanCyQPALM}}{sep}(p=8,v=4,serial)",
    }
    solver_name = names.get(solver_name, solver_name)
    solver_name = solver_name.replace("cyqlone._cyqlone_", "")
    solver_name = solver_name.replace("Cyqlone", "\\textsc{CyQPALM}")
    solver_name = solver_name.replace("cyqlone", "\\textsc{CyQPALM}")
    if plot == "scaling":
        solver_name = solver_name.replace(fr"{sep}(cold)", "")
        solver_name = solver_name.replace(fr"{sep}(warm)", "")
    return solver_name.strip()


def filter_by_datasets(
    df: pd.DataFrame,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
) -> pd.DataFrame:
    """
    Filter DataFrame by dataset_id using either a list or regex pattern.
    
    Parameters
    ----------
    df : pd.DataFrame
        DataFrame to filter
    selected_datasets : list[str], optional
        List of dataset_ids to include
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    
    Returns
    -------
    pd.DataFrame
        Filtered DataFrame
    """
    if selected_datasets is not None:
        df = df[df["dataset_id"].isin(selected_datasets)]
    
    if dataset_regex is not None:
        df = df[df["dataset_id"].str.match(dataset_regex, na=False)]
    
    return df


def validate_metric(df: pd.DataFrame, metric: str, solver_id: str) -> None:
    """
    Check if metric exists in the DataFrame.
    
    Parameters
    ----------
    df : pd.DataFrame
        DataFrame to check
    metric : str
        Metric name to validate
    solver_id : str
        Solver ID for error message
    
    Raises
    ------
    ValueError
        If metric not found in DataFrame columns
    """
    if metric not in df.columns:
        raise ValueError(
            f"Metric '{metric}' not found in data for solver '{solver_id}'"
        )


def get_solver_name(
    df: pd.DataFrame,
    solver_id: str,
    plot: Optional[str] = None,
    fallback: Optional[str] = None,
) -> str:
    """
    Extract and format solver name from DataFrame.
    
    Parameters
    ----------
    df : pd.DataFrame
        DataFrame containing solver data
    solver_id : str
        Original solver ID to use as fallback
    plot : str, optional
        Plot type for formatting (e.g., "box", "scaling")
    fallback : str, optional
        Fallback name if solver_name column is empty
    
    Returns
    -------
    str
        Formatted solver name
    """
    if fallback is None:
        fallback = solver_id
    
    solver_name = solver_id
    if "solver_name" in df.columns and not df["solver_name"].isnull().all():
        try:
            solver_name = str(df["solver_name"].iloc[0])
            solver_name = format_solver_name(solver_name, plot=plot)
            if not solver_name:
                solver_name = fallback
        except Exception:
            solver_name = fallback
    
    return solver_name


def round_to_nice_bin_width(
    range_min: float, range_max: float, bins: int
) -> tuple[np.ndarray, int]:
    """
    Round the number of bins so that the bin width is a sensible fraction.
    Also rounds range_min and range_max to nice values.

    Parameters
    ----------
    range_min : float
        Minimum value of the range
    range_max : float
        Maximum value of the range
    bins : int
        Requested number of bins

    Returns
    -------
    bin_edges : np.ndarray
        Array of bin edges
    actual_bins : int
        Actual number of bins used
    """
    range_width = range_max - range_min
    if range_width <= 0:
        return np.array([range_min, range_max]), 1

    # Calculate desired bin width
    desired_width = range_width / bins

    # Find a nice bin width (powers of 10 times common fractions)
    magnitude = 10 ** np.floor(np.log10(desired_width))

    # Common nice fractions
    nice_fractions = [0.1, 0.2, 0.25, 0.5, 1.0, 2.0, 2.5, 5.0, 10.0]

    # Find the closest nice bin width
    normalized_width = desired_width / magnitude
    nice_width = min(nice_fractions, key=lambda x: abs(x - normalized_width))
    bin_width = nice_width * magnitude

    # Round range_min down and range_max up to nice multiples of bin_width
    nice_range_min = np.floor(range_min / bin_width) * bin_width
    nice_range_max = np.ceil(range_max / bin_width) * bin_width

    # Calculate actual number of bins with the nice range
    actual_bins = int(np.round((nice_range_max - nice_range_min) / bin_width))

    # Create bin edges
    bin_edges = np.linspace(nice_range_min, nice_range_max, actual_bins + 1)

    return bin_edges, actual_bins


def create_scaling_plot(
    all_results: dict[str, pd.DataFrame],
    metric: str,
    solvers: list[str],
    reference_solver: Optional[str] = None,
    problem_pattern: Optional[str] = None,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
    figsize: tuple[float, float] = (8, 6),
    reduce_metric: str = "min",
    show_legend: bool = True,
    ylim: Optional[tuple[float, float]] = None,
    logy: bool = False,
    color_offset: int = 0,
):
    """
    Create a scaling plot showing speedup (or absolute metric) vs horizon length N.
    
    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    metric : str
        Metric to plot (e.g., "time_per_iter")
    solvers : list[str]
        List of solver IDs to plot
    reference_solver : str, optional
        Reference solver for speedup calculation. If None, plot absolute metric values.
    problem_pattern : str, optional
        Regex pattern to match problem_id
    selected_datasets : list[str], optional
        List of dataset_ids to include. If None, use all datasets.
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    figsize : tuple[float, float]
        Figure size in inches
    reduce_metric : str
        How to aggregate multiple runs of the same problem ("min", "max", "mean")
    logy : bool
        Whether to use logarithmic scale for y-axis (default: False)
    
    Returns
    -------
    fig : matplotlib.figure.Figure
        The generated figure
    """
    # Extract and process reference solver data if provided
    ref_grouped = None
    ref_grouped_min = None
    ref_grouped_max = None
    ref_grouped_q1 = None
    ref_grouped_q3 = None
    ref_name = None
    
    if reference_solver is not None:
        ref_df = extract_timings(all_results, reference_solver, problem_pattern)
        
        # Filter by dataset if specified
        if selected_datasets is not None:
            ref_df = ref_df[ref_df["dataset_id"].isin(selected_datasets)]
        
        # Filter by dataset regex if specified
        if dataset_regex is not None:
            ref_df = ref_df[ref_df["dataset_id"].str.match(dataset_regex, na=False)]
        
        # Select the aggregate type
        ref_df = ref_df[ref_df["aggregate_name"] == reduce_metric]
        
        ref_df = ref_df.copy()
        # Extract N using vectorized string operation
        ref_df["N"] = ref_df["dataset_id"].str.extract(r"N=(\d+)")[0].astype(int)
        
        # Group by N and compute average metric for reference
        ref_grouped = ref_df.groupby("N")[metric].mean()
        ref_grouped_min = ref_df.groupby("N")[metric].min()
        ref_grouped_max = ref_df.groupby("N")[metric].max()
        ref_grouped_q1 = ref_df.groupby("N")[metric].quantile(0.25)
        ref_grouped_q3 = ref_df.groupby("N")[metric].quantile(0.75)
        
        # Get reference solver name for labels
        ref_name = reference_solver
        if "solver_name" in ref_df.columns and not ref_df["solver_name"].isnull().all():
            try:
                ref_name = str(ref_df["solver_name"].iloc[0])
                ref_name = format_solver_name(ref_name, plot="scaling")
                if not ref_name:
                    ref_name = reference_solver
            except Exception:
                pass
    
    # Create figure
    fig, ax = plt.subplots(figsize=figsize)
    
    # First pass: collect all data to determine if we need to scale
    solver_data_list = []
    all_y_values: list[float] = []
    
    for solver_idx, solver in enumerate(solvers):
        # Extract data for this solver
        solver_df = extract_timings(all_results, solver, problem_pattern)
        
        # Filter by dataset if specified
        if selected_datasets is not None:
            solver_df = solver_df[solver_df["dataset_id"].isin(selected_datasets)]
        
        # Filter by dataset regex if specified
        if dataset_regex is not None:
            solver_df = solver_df[solver_df["dataset_id"].str.match(dataset_regex, na=False)]
        
        # Select the aggregate type
        solver_df = solver_df[solver_df["aggregate_name"] == reduce_metric]
        
        solver_df = solver_df.copy()
        # Extract N using vectorized string operation
        solver_df["N"] = solver_df["dataset_id"].str.extract(r"N=(\d+)")[0].astype(int)
        print(f"N values for solver '{solver}': {solver_df['N'].tolist()}")
        # Group by N and compute statistics
        solver_grouped_mean = solver_df.groupby("N")[metric].mean()
        solver_grouped_min = solver_df.groupby("N")[metric].min()
        solver_grouped_max = solver_df.groupby("N")[metric].max()
        solver_grouped_q1 = solver_df.groupby("N")[metric].quantile(0.25)
        solver_grouped_q3 = solver_df.groupby("N")[metric].quantile(0.75)
        
        # Get solver name for label
        solver_name = solver
        if "solver_name" in solver_df.columns and not solver_df["solver_name"].isnull().all():
            try:
                solver_name = str(solver_df["solver_name"].iloc[0])
                solver_name = format_solver_name(solver_name, plot="scaling")
                if not solver_name:
                    solver_name = solver
            except Exception:
                pass
        
        if reference_solver is not None:
            # Compute speedup: reference / solver using pandas operations
            assert ref_grouped is not None  # Type guard: ref_grouped is set when reference_solver is not None
            # Merge solver data with reference data on N
            merged = pd.DataFrame({
                "solver_mean": solver_grouped_mean,
                "solver_min": solver_grouped_min,
                "solver_max": solver_grouped_max,
                "solver_q1": solver_grouped_q1,
                "solver_q3": solver_grouped_q3,
                "ref_mean": ref_grouped,
                "ref_min": ref_grouped_min,
                "ref_max": ref_grouped_max,
                "ref_q1": ref_grouped_q1,
                "ref_q3": ref_grouped_q3,
            }).dropna()
            N_values = sorted(merged.index)
            y_values = (merged["ref_mean"] / merged["solver_mean"]).tolist()
            # Compute speedup range using min/max
            y_min = (merged["ref_min"] / merged["solver_max"]).tolist()
            y_max = (merged["ref_max"] / merged["solver_min"]).tolist()
            # Compute speedup range using quartiles
            y_q1 = (merged["ref_q1"] / merged["solver_q3"]).tolist()
            y_q3 = (merged["ref_q3"] / merged["solver_q1"]).tolist()
            label = f"{solver_name} compared to {ref_name}"
        else:
            # Plot absolute metric values with min/max range
            N_values = sorted(solver_grouped_mean.index)
            y_values = solver_grouped_mean[N_values].tolist()
            y_min = solver_grouped_min[N_values].tolist()
            y_max = solver_grouped_max[N_values].tolist()
            y_q1 = solver_grouped_q1[N_values].tolist()
            y_q3 = solver_grouped_q3[N_values].tolist()
            label = solver_name
        
        solver_data_list.append((solver_idx, N_values, y_values, y_min, y_max, y_q1, y_q3, label, solver_name))
        all_y_values.extend(y_values)
    
    # Determine if we need to convert ms to μs
    scale_factor = 1.0
    ylabel = METRIC_LABELS.get(metric, metric.replace("_", " ").capitalize())
    
    if reference_solver is None:  # Only for absolute metric plots
        max_y = max(all_y_values) if all_y_values else 0
        if ylim is not None:
            max_y = ylim[1]
        
        if max_y <= 1.0 and "[ms]" in ylabel:
            scale_factor = 1e3
            ylabel = ylabel.replace("[ms]", r"[$\mu$s]")
    
    # Second pass: plot with scaling applied
    with_fill_between = False
    for solver_idx, N_values, y_values, y_min, y_max, y_q1, y_q3, label, solver_name in solver_data_list:
        # Apply scaling using numpy for efficiency
        y_values_scaled = np.array(y_values) * scale_factor
        
        color = hist_colors[(solver_idx + color_offset) % len(hist_colors)]
        
        # Plot vs N
        ax.plot(N_values, y_values_scaled, marker='o', linewidth=1.25, markersize=3,
                color=color, label=label)
        
        # Add fill_between for min/max range
        if y_min is not None and y_max is not None and with_fill_between:
            y_min_scaled = np.array(y_min) * scale_factor
            y_max_scaled = np.array(y_max) * scale_factor
            ax.fill_between(N_values, y_min_scaled, y_max_scaled, 
                           color=color, alpha=0.15, linewidth=0)
        
        # Add fill_between for quartile range (Q1-Q3)
        if y_q1 is not None and y_q3 is not None and with_fill_between:
            y_q1_scaled = np.array(y_q1) * scale_factor
            y_q3_scaled = np.array(y_q3) * scale_factor
            ax.fill_between(N_values, y_q1_scaled, y_q3_scaled, 
                           color=color, alpha=0.15, linewidth=0)
    
    # Add horizontal line at speedup = 1.0 (only for speedup plots)
    if reference_solver is not None:
        ax.axhline(y=1.0, color="black", linestyle="--", linewidth=1, alpha=0.7)
    
    ax.set_xlabel("Horizon length $N$")
    
    if reference_solver is not None:
        # Speedup plot
        ax.set_ylabel(f"Speedup ({METRIC_PRETTY.get(metric, metric)})")
        speedup = "Speedup"
        if metric == "time_per_iter":
            speedup = "Speedup per iteration"
        if len(solvers) == 1 and solver_data_list:
            # Get solver name from first (and only) entry
            _, _, _, _, _, _, _, _, solver_name = solver_data_list[0]
            ax.set_title(f"{speedup} of {solver_name}\ncompared to {ref_name}")
        else:
            ax.set_title(f"{speedup}\nfor increasing horizon length $N$")
    else:
        # Absolute metric plot
        ax.set_ylabel(ylabel)
        metric_pretty = METRIC_PRETTY.get(metric, metric.replace("_", " ").capitalize())
        if len(solvers) == 1 and solver_data_list:
            # Get solver name from first (and only) entry
            _, _, _, _, _, _, _, _, solver_name = solver_data_list[0]
            ax.set_title(f"{metric_pretty.capitalize()} of {solver_name}")
        else:
            ax.set_title(f"{metric_pretty.capitalize()}\nfor increasing horizon length $N$")
    
    ax.grid(True, alpha=0.3, which="major")
    ax.grid(True, alpha=0.15, which="minor")

    if logy:
        ax.set_yscale('log')
    if show_legend:
        ax.legend(loc="best", fontsize=9, framealpha=0.6)

    # Set ylim with scaling applied
    if ylim is not None:
        if reference_solver is not None:
            # Speedup plots - use ylim as-is
            ax.set_ylim(ylim)
        else:
            # Absolute metric plots - apply scale factor
            ax.set_ylim(ylim[0] * scale_factor, ylim[1] * scale_factor)
    elif reference_solver is None:
        # For absolute metric plots without explicit ylim, set lower bound to 0
        if not logy:
            ax.set_ylim(0, None)
        else:
            pass
    
    plt.tight_layout()
    
    return fig


def create_box_plot(
    all_results: dict[str, pd.DataFrame],
    metric: str,
    selected_solvers: list[str],
    reference_solver: Optional[list[str]] = None,
    problem_pattern: Optional[str] = None,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
    figsize: tuple[float, float] = (10, 8),
    reduce_metric: str = "min",
    show_legend: bool = True,
    group_by: str = "dataset",
    xlim: Optional[tuple[float, float]] = None,
    logy: bool = False,
):
    """
    Create box plots for multiple solvers on a single subplot.
    The metric is shown on the vertical axis, with one vertical box plot
    for each solver and dataset combination. Results can be grouped either by
    dataset or by solver.

    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    metric : str
        Metric to plot (e.g., "time", "num_iter")
    selected_solvers : list[str]
        List of solver_ids to include in the plot
    reference_solver : list[str], optional
        Reference solver(s) for speedup calculation. Can be:
        - None: plot absolute metric values
        - list[str] with single element: reference solver for all selected solvers
        - list[str] with same length as selected_solvers: each selected solver
          is compared to the corresponding reference solver at the same index
    problem_pattern : str, optional
        Regex pattern to match problem_id
    selected_datasets : list[str], optional
        List of dataset_ids to include. If None, use all datasets.
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    figsize : tuple[float, float]
        Figure size in inches
    reduce_metric : str
        How to aggregate multiple runs of the same problem ("min", "max", "mean")
    show_legend : bool
        Whether to show the legend
    group_by : str
        How to group the box plots: "dataset" or "solver" (default: "dataset")
    xlim : tuple[float, float], optional
        Metric-axis limits (min, max). For vertical box plots these are applied
        to the y-axis. If None, auto-computed.

    Returns
    -------
    fig : matplotlib.figure.Figure
        The generated figure
    """
    if len(selected_solvers) == 0:
        raise ValueError("No solvers selected")
    
    if group_by not in ["dataset", "solver"]:
        raise ValueError(f"group_by must be 'dataset' or 'solver', got '{group_by}'")

    # Validate reference_solver if provided
    if reference_solver is not None:
        if len(reference_solver) != 1 and len(reference_solver) != len(selected_solvers):
            raise ValueError(
                f"Number of reference solvers ({len(reference_solver)}) must be either 1 "
                f"or equal to the number of selected solvers ({len(selected_solvers)})"
            )
    
    # Extract and filter data for reference solvers if specified
    # Map from solver_id to its reference data
    ref_values_map: dict[str, pd.DataFrame] = {}
    ref_names_map: dict[str, str] = {}
    
    if reference_solver is not None:
        # Determine which reference solver to use for each selected solver
        if len(reference_solver) == 1:
            # Single reference for all solvers
            solver_to_ref = {solver: reference_solver[0] for solver in selected_solvers}
        else:
            # One-to-one mapping
            solver_to_ref = {solver: ref for solver, ref in zip(selected_solvers, reference_solver)}
        
        # Extract data for each unique reference solver
        unique_refs = set(solver_to_ref.values())
        for ref_solver in unique_refs:
            if ref_solver not in all_results:
                raise ValueError(
                    f"Reference solver '{ref_solver}' not found. "
                    f"Available solvers: {list(all_results.keys())}"
                )
            
            ref_df = extract_timings(all_results, ref_solver, problem_pattern)
            ref_df = filter_by_datasets(ref_df, selected_datasets, dataset_regex)
            validate_metric(ref_df, metric, ref_solver)
            
            # Select the aggregate type
            ref_df = ref_df[ref_df["aggregate_name"] == reduce_metric]
            
            # Keep reference data as DataFrame for efficient merging
            ref_values = ref_df[["problem_id", metric]].rename(columns={metric: "ref_metric"})
            
            # Get reference solver name for labels
            ref_name = get_solver_name(ref_df, ref_solver)
            
            # Store for each solver that uses this reference
            for solver in selected_solvers:
                if solver_to_ref[solver] == ref_solver:
                    ref_values_map[solver] = ref_values
                    ref_names_map[solver] = ref_name
        
        print(solver_to_ref)

    # Extract and filter data for each solver
    solver_data = {}
    all_datasets = set()

    for solver_id in selected_solvers:
        df = extract_timings(all_results, solver_id, problem_pattern)
        df = filter_by_datasets(df, selected_datasets, dataset_regex)
        validate_metric(df, metric, solver_id)

        # Select the aggregate type
        df = df[df["aggregate_name"] == reduce_metric].copy()
        
        # Compute speedup if reference solver is specified using merge
        if reference_solver is not None and solver_id in ref_values_map:
            ref_values = ref_values_map[solver_id]
            df = df.merge(ref_values, on="problem_id", how="left")
            df["speedup"] = np.where(df[metric] != 0, df["ref_metric"] / df[metric], np.nan)
            df = df.drop(columns=["ref_metric"])
        
        solver_data[solver_id] = df
        all_datasets.update(df["dataset_id"].unique())

    # Sort datasets naturally (considering numeric values in parentheses)
    def natural_sort_key(dataset_name):
        """Extract numeric components for natural sorting."""
        parts = re.findall(r"(\d+)", str(dataset_name))
        return [int(part) for part in parts] if parts else [0]

    all_datasets_sorted = sorted(all_datasets, key=natural_sort_key)

    # Color mapping based on grouping
    color_stride = 1 if reference_solver is None else 2
    if group_by == "dataset":
        # Color by solver when grouping by dataset
        color_map = {
            solver: hist_colors[(i * color_stride) % len(hist_colors)]
            for i, solver in enumerate(selected_solvers)
        }
    else:
        # Color by dataset when grouping by solver
        color_map = {
            dataset: hist_colors[i % len(hist_colors)]
            for i, dataset in enumerate(all_datasets_sorted)
        }

    # Create figure
    fig = plt.figure(figsize=figsize)
    ax = fig.add_subplot(111)

    # Prepare data for box plots
    box_data = []
    box_positions = []
    box_colors = []
    box_labels = []  # Labels for each box (solver or solver+reference)
    group_tick_positions = []
    group_tick_labels = []
    
    # Determine which metric to use for box plots
    plot_metric = "speedup" if reference_solver is not None else metric

    position = 0
    gap_between_groups = 1.5
    dataset_fixed = None

    if group_by == "dataset":
        # Group by dataset (original behavior)
        for dataset_idx, dataset_id in enumerate(all_datasets_sorted):
            dataset_formatted, dataset_fixed = format_dataset(dataset_id, all_datasets_sorted)
            
            group_start_position = position
            for solver_idx, solver_id in enumerate(selected_solvers):
                df = solver_data[solver_id]
                dataset_df = df[df["dataset_id"] == dataset_id]
                
                if len(dataset_df) > 0:
                    values = dataset_df[plot_metric].dropna().values
                    box_data.append(values)
                    box_positions.append(position)
                    box_colors.append(color_map[solver_id])
                    
                    # Build label with reference solver if applicable
                    solver_name = get_solver_name(df, solver_id)
                    
                    if reference_solver is not None and solver_id in ref_names_map:
                        # Include reference solver in label
                        ref_name = ref_names_map[solver_id]
                        box_labels.append(f"{solver_name} vs {ref_name}")
                    else:
                        box_labels.append(solver_name)
                    
                    position += 1
            
            # Calculate middle position of the group for the tick
            group_end_position = position - 1
            group_middle = (group_start_position + group_end_position) / 2
            group_tick_positions.append(group_middle)
            group_tick_labels.append(dataset_formatted)
            
            # Add gap between datasets
            position += gap_between_groups
    
    else:
        # Group by solver (new behavior)
        for solver_idx, solver_id in enumerate(selected_solvers):
            df = solver_data[solver_id]
            
            # Get solver name for label
            solver_name = get_solver_name(df, solver_id, plot="box")
            
            group_start_position = position
            for dataset_idx, dataset_id in enumerate(all_datasets_sorted):
                dataset_df = df[df["dataset_id"] == dataset_id]
                
                if len(dataset_df) > 0:
                    values = dataset_df[plot_metric].dropna().values
                    box_data.append(values)
                    box_positions.append(position)
                    box_colors.append(color_map[dataset_id])
                    
                    # Build label with reference solver if applicable
                    dataset_label, dataset_fixed = format_dataset(dataset_id, all_datasets_sorted)
                    if reference_solver is not None and solver_id in ref_names_map:
                        # Include reference solver in label
                        ref_name = ref_names_map[solver_id]
                        box_labels.append(f"{dataset_label}")
                    else:
                        box_labels.append(dataset_label)
                    
                    position += 1
            
            # Calculate middle position of the group for the tick
            group_end_position = position - 1
            group_middle = (group_start_position + group_end_position) / 2
            group_tick_positions.append(group_middle)
            group_tick_labels.append(solver_name)
            
            # Add gap between solvers
            position += gap_between_groups

    # Create vertical box plots
    bp = ax.boxplot(
        box_data,
        positions=box_positions,
        notch=True,
        vert=True,
        widths=0.5,
        patch_artist=True,
        showfliers=True,
        flierprops=dict(
            marker='+',
            markerfacecolor='black',
            markeredgecolor='black',
            markersize=3,
            markeredgewidth=0.25,
            alpha=0.5,
        ),
        medianprops=dict(color='black', linewidth=0.8),
    )

    # Color the boxes
    for patch, color in zip(bp['boxes'], box_colors):
        patch.set_facecolor(color)
        patch.set_alpha(1)
        patch.set_linewidth(0.8)
        patch.set_edgecolor('black')
    # Color the whiskers
    whis_colors = np.array(box_colors).repeat(2)
    for patch, color in zip(bp['whiskers'], whis_colors):
        patch.set_alpha(1)
        patch.set_linewidth(0.8)
        patch.set_color(color)
    # Set whisker cap line width
    for cap in bp['caps']:
        cap.set_linewidth(0.8)

    # Set x-tick labels at the center of each group
    ax.set_xticks(group_tick_positions)
    ax.set_xticklabels(group_tick_labels, fontsize=10)
    ax.set_xlim(-1, position - gap_between_groups)
    
    # Set x-axis label and title
    if reference_solver is not None:
        # Speedup plot
        ax.set_ylabel("Speedup")
        metric_pretty = METRIC_PRETTY.get(metric, metric.replace("_", " "))
        ax.set_title(f"Speedup ({metric_pretty})")
        # Add horizontal line at speedup = 1.0
        ax.axhline(y=1.0, color="black", linestyle="--", linewidth=1, alpha=0.7)
    else:
        # Absolute metric plot
        ax.set_ylabel(METRIC_LABELS.get(metric, metric.replace("_", " ").capitalize()))
        title = METRIC_PRETTY.get(metric, metric.replace("_", " ")).capitalize()
        if dataset_fixed is not None:
            # title = f"{title}\\rlap{{\\quad\\normalsize{{({dataset_fixed})}}}}"
            title = f"{title}\\hspace{{9em}}\\llap{{\\normalsize{{({dataset_fixed})}}}}"
        ax.set_title(title, loc="right")
    
    # Grid and metric-axis limits
    if xlim is not None:
        ax.set_ylim(xlim)
        if xlim == (0, 52) or xlim == (0, 54):
            ax.set_yticks([0, 10, 20, 30, 40, 50])
            ax.set_yticks([2, 4, 6, 8], minor=True)
    else:
        if not logy:
            ax.set_ylim(0, None)
    if logy:
        ax.set_yscale('log')
    if 175 <= ax.get_ylim()[1] <= 190:
        ax.set_yticks([5, 10, 15, 20], minor=True)
    ax.grid(True, alpha=0.3, axis="y")
    ax.grid(True, alpha=0.15, axis="y", which="minor")
    # Create legend if requested and there are multiple items
    if show_legend:
        from matplotlib.patches import Patch
        
        if reference_solver is not None:
            # When using reference solvers, show all box labels with their colors
            # Remove duplicates while preserving order
            seen = set()
            legend_elements = []
            for label, color in zip(reversed(box_labels), reversed(box_colors)):
                if label not in seen:
                    seen.add(label)
                    legend_elements.append(Patch(facecolor=color, alpha=1, label=label))
            ax.legend(handles=legend_elements, loc="best", fontsize=9, framealpha=0.6)
        elif group_by == "dataset" and len(selected_solvers) > 1:
            # Legend shows solvers (no reference)
            legend_elements = [
                Patch(
                    facecolor=color_map[solver_id],
                    alpha=1,
                    label=get_solver_name(solver_data[solver_id], solver_id)
                )
                for solver_id in selected_solvers
            ]
            ax.legend(handles=legend_elements, loc="best", fontsize=9, framealpha=0.6)
        elif group_by == "solver" and len(all_datasets_sorted) > 1:
            # Legend shows datasets (no reference)
            legend_elements = [
                Patch(facecolor=color_map[dataset_id], alpha=1, label=format_dataset(dataset_id, all_datasets_sorted)[0])
                for dataset_id in all_datasets_sorted
            ]
            ax.legend(handles=legend_elements, loc="best", fontsize=9, framealpha=0.6)
    
    plt.tight_layout()
    
    return fig
def create_timing_breakdown_plot(
    all_results: dict[str, pd.DataFrame],
    solver: str,
    problem_pattern: Optional[str] = None,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
    figsize: tuple[float, float] = (10, 6),
    reduce_metric: str = "min",
    show_legend: bool = True,
    relative: bool = False,
):
    """
    Create a stacked bar chart showing timing breakdown for each dataset.
    
    The bars show the time spent in different phases:
    - time_active_set_change
    - time_line_search
    - time_recompute_inner
    - time_recompute_outer
    - time_solve
    - overhead (remaining time not accounted for)
    
    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    solver : str
        Solver ID to plot
    problem_pattern : str, optional
        Regex pattern to match problem_id
    selected_datasets : list[str], optional
        List of dataset_ids to include. If None, use all datasets.
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    figsize : tuple[float, float]
        Figure size in inches
    reduce_metric : str
        How to aggregate multiple runs of the same problem ("min", "max", "mean")
    show_legend : bool
        Whether to show the legend
    
    Returns
    -------
    fig : matplotlib.figure.Figure
        The generated figure
    """
    # Extract data for the solver
    df = extract_timings(all_results, solver, problem_pattern)
    df = filter_by_datasets(df, selected_datasets, dataset_regex)
    
    # Select the aggregate type
    df = df[df["aggregate_name"] == reduce_metric].copy()
    df["time_recompute"] = df["time_recompute_inner"] + df["time_recompute_outer"]
    if "time_mat_vec" in df.columns:
        df["time_mat_vec_total"] = df["time_recompute"] + df["time_mat_vec"]
    else:
        df["time_mat_vec_total"] = df["time_recompute"]

    # Define timing components (in seconds)
    timing_components = [
        "time_solve",
        "time_active_set_change",
        "time_line_search",
        "time_mat_vec_total",
    ]
    
    # Check if all timing components exist
    missing_components = [c for c in timing_components if c not in df.columns]
    if missing_components:
        raise ValueError(
            f"Missing timing components in data: {missing_components}. "
            f"Available columns: {list(df.columns)}"
        )
    
    if "time" not in df.columns:
        raise ValueError("'time' column not found in data")
    
    # Convert timing components from seconds to milliseconds (matching "time" unit)
    for component in timing_components:
        df[component] = df[component] * 1000  # seconds to ms
    
    # Group by dataset and compute mean for each timing component
    grouped = df.groupby("dataset_id")
    
    # Collect data for plotting
    datasets = []
    timing_data = {component: [] for component in timing_components}
    timing_data["overhead"] = []
    timing_data["total_time"] = []
    
    # Sort datasets naturally
    def natural_sort_key(dataset_name):
        parts = re.findall(r"(\d+)", str(dataset_name))
        return [int(part) for part in parts] if parts else [0]
    
    all_datasets_sorted = sorted(grouped.groups.keys(), key=natural_sort_key)
    all_datasets_sorted_str = [str(d) for d in all_datasets_sorted]
    
    for dataset_id in all_datasets_sorted:
        dataset_df = grouped.get_group(dataset_id)
        datasets.append(dataset_id)
        
        # Compute mean for each component
        total_time = dataset_df["time"].mean()
        component_sum = 0
        
        for component in timing_components:
            value = dataset_df[component].mean()
            timing_data[component].append(value)
            component_sum += value
        
        # Calculate overhead (remaining time)
        overhead = max(0, total_time - component_sum)
        timing_data["overhead"].append(overhead)
        timing_data["total_time"].append(total_time)
    
    # Create figure
    fig, ax = plt.subplots(figsize=figsize)
    
    # Prepare data for stacked bar chart
    x_pos = np.arange(len(datasets))
    bar_width = 0.6
    
    # Colors for each component
    component_colors = {
        "time_solve":
        "#1f77b4",  # blue
        "time_active_set_change":
        "#ff7f0e",  # orange
        "time_line_search":
        "#2ca02c",  # green
        "time_mat_vec_total":
        "#d62728",  # red
        "overhead":
        "#9467bd",  # purple
    }
    
    # Pretty names for legend
    component_labels = {
        "time_solve": "Factor and solve Newton system",
        "time_active_set_change": "Factorization updates",
        "time_line_search": "Line search",
        "time_mat_vec_total": "Matrix--vector products",
        "overhead": "Other",
    }
    
    # Create stacked bars
    bottom = np.zeros(len(datasets))
    
    for component in timing_components + ["overhead"]:
        if relative:
            values = np.array(timing_data[component]) / np.array(timing_data["total_time"])
        else:
            values = np.array(timing_data[component])
        ax.bar(
            x_pos,
            values,
            bar_width,
            bottom=bottom,
            label=component_labels[component],
            color=component_colors[component],
            alpha=0.9,
        )
        bottom += values
    
    # Format x-axis labels
    formatted_labels = [format_dataset(d, all_datasets_sorted_str)[0] for d in datasets]
    ax.set_xticks(x_pos)
    if all(l.startswith("$N$=\\,") for l in formatted_labels):
        ax.set_xlabel("Horizon length $N$")
        formatted_labels = [l.removeprefix("$N$=\\,") for l in formatted_labels]
    elif all(l.startswith("$M$=\\,") for l in formatted_labels):
        ax.set_xlabel("Number of masses $M$")
        formatted_labels = [l.removeprefix("$M$=\\,") for l in formatted_labels]
    elif all(l.startswith("$J$=\\,") for l in formatted_labels):
        ax.set_xlabel("Number of branches $J$")
        formatted_labels = [l.removeprefix("$J$=\\,") for l in formatted_labels]
    ax.set_xticklabels(formatted_labels, rotation=0)
    
    # Labels and title
    if relative:
        ax.set_ylabel("Fraction of total run time")
    else:
        ax.set_ylabel("Time [ms]")
    
    # Get solver name for title
    solver_name = get_solver_name(df, solver)
    ax.set_title(f"Timings for {solver_name}")
    
    ax.grid(True, alpha=0.3, axis="y")
    
    if show_legend:
        ax.legend(loc="lower right" if relative else "best", fontsize=9, framealpha=0.8)
    
    plt.tight_layout()
    
    return fig


def create_histogram_plot(
    all_results: dict[str, pd.DataFrame],
    metric: str,
    selected_solvers: list[str],
    problem_pattern: Optional[str] = None,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
    bins: int = 50,
    bin_range: Optional[tuple[float, float]] = None,
    figsize: tuple[float, float] = (10, 8),
    reduce_metric: str = "min",
    show_legend: bool = True,
):
    """
    Create histogram plots for multiple solvers, each in its own subplot.
    Each dataset is shown in a different color, with stacked bars.

    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    metric : str
        Metric to plot (e.g., "time", "num_iter")
    selected_solvers : list[str]
        List of solver_ids to include in the plot
    problem_pattern : str, optional
        Regex pattern to match problem_id
    selected_datasets : list[str], optional
        List of dataset_ids to include. If None, use all datasets.
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    bins : int
        Number of histogram bins
    bin_range : tuple[float, float], optional
        Range for bins (min, max). If None, auto-computed.
    figsize : tuple[float, float]
        Figure size in inches
    reduce_metric : str
        How to aggregate multiple runs of the same problem ("min", "max", "mean")

    Returns
    -------
    fig : matplotlib.figure.Figure
        The generated figure
    """
    if len(selected_solvers) == 0:
        raise ValueError("No solvers selected")

    # Extract and filter data for each solver
    solver_data = {}
    all_datasets = set()

    for solver_id in selected_solvers:
        df = extract_timings(all_results, solver_id, problem_pattern)

        # Filter by dataset if specified
        if selected_datasets is not None:
            df = df[df["dataset_id"].isin(selected_datasets)]

        # Filter by dataset regex if specified
        if dataset_regex is not None:
            df = df[df["dataset_id"].str.match(dataset_regex, na=False)]

        # Check if metric exists
        if metric not in df.columns:
            raise ValueError(
                f"Metric '{metric}' not found in data for solver '{solver_id}'"
            )

        # Select the aggregate type
        df = df[df["aggregate_name"] == reduce_metric]
        solver_data[solver_id] = df
        all_datasets.update(df["dataset_id"].unique())

    # Determine bin range if not specified
    if bin_range is None:
        # Concatenate all metric values efficiently
        all_values = pd.concat([df[metric].dropna() for df in solver_data.values()], ignore_index=True)
        if len(all_values) == 0:
            raise ValueError("No data available for the selected metric and filters")
        bin_range = (all_values.min(), all_values.max())

    # Create bins with nice bin width
    bin_edges, actual_bins = round_to_nice_bin_width(bin_range[0], bin_range[1], bins)

    if metric == "num_iter":
        bin_edges = np.arange(bin_range[0], bin_range[1] + 1)

    # Sort datasets naturally (considering numeric values in parentheses)
    def natural_sort_key(dataset_name):
        """Extract numeric components for natural sorting."""
        # Extract numbers from strings like "MassSprings(30, 64)"
        parts = re.findall(r"(\d+)", str(dataset_name))
        return [int(part) for part in parts] if parts else [0]

    all_datasets_sorted = sorted(all_datasets, key=natural_sort_key)

    # Color mapping for datasets (not solvers anymore)
    dataset_color_map = {
        dataset: hist_colors[i % len(hist_colors)]
        for i, dataset in enumerate(all_datasets_sorted)
    }

    # Create figure with subplots (one per solver)
    n_solvers = len(selected_solvers)
    fig, axes = plt.subplots(n_solvers, 1, sharex=True, sharey=True, figsize=figsize)
    if n_solvers == 1:
        axes = [axes]

    for ax, solver_id in zip(axes, selected_solvers):
        df = solver_data[solver_id]

        # Get solver name for label
        label = solver_id
        if "solver_name" in df.columns and not df["solver_name"].isnull().all():
            try:
                label = str(df["solver_name"].iloc[0])
                label = format_solver_name(label)
                if not label:
                    label = solver_id
            except Exception:
                pass

        # Create stacked histogram with one series per dataset
        dataset_values = []
        dataset_labels = []
        dataset_colors = []

        for dataset_id in all_datasets_sorted:
            dataset_df = df[df["dataset_id"] == dataset_id]
            if len(dataset_df) > 0:
                dataset_values.append(dataset_df[metric].dropna().values)
                n_inst = len(dataset_df)
                lbl, _ = format_dataset(dataset_id, all_datasets_sorted)
                dataset_labels.append(f"${n_inst}\\times$ {lbl}")
                dataset_colors.append(dataset_color_map[dataset_id])

        # Plot stacked histogram
        ax.hist(
            dataset_values,
            bins=bin_edges.tolist(),
            rwidth=0.85,
            color=dataset_colors,
            alpha=0.8,
            stacked=True,
            label=dataset_labels,
        )

        ax.set_title(label)
        ax.set_ylabel("Count")
        ax.grid(True, alpha=0.3, axis="y")

        # Add legend only to the first subplot
        if show_legend and ax == axes[0] and len(dataset_labels) > 1:
            ax.legend(loc="best", fontsize=9, framealpha=0.6)

    # Set x-label only on bottom plot
    axes[-1].set_xlabel(
        METRIC_LABELS.get(metric, metric.replace("_", " ").capitalize())
    )
    axes[-1].set_xlim(0, None)

    # Super title
    metric_pretty = METRIC_PRETTY.get(metric, metric.replace("_", " ").capitalize())
    fig.suptitle(f"Histogram of {metric_pretty}", fontsize=14)

    fig.align_ylabels()
    plt.tight_layout()

    return fig


def create_speedup_plot(
    all_results: dict[str, pd.DataFrame],
    metric: str,
    reference_solver: str,
    selected_solvers: list[str],
    problem_pattern: Optional[str] = None,
    selected_datasets: Optional[list[str]] = None,
    dataset_regex: Optional[str] = None,
    bins: int = 50,
    bin_range: Optional[tuple[float, float]] = None,
    figsize: tuple[float, float] = (10, 8),
    reduce_metric: str = "min",
    show_legend: bool = True,
):
    """
    Create histogram plots showing speedup relative to a reference solver.
    Each solver is shown in its own subplot, with datasets in different colors.

    Parameters
    ----------
    all_results : dict[str, pd.DataFrame]
        Dictionary mapping solver_id to DataFrame of results
    metric : str
        Metric to plot (e.g., "time", "num_iter")
    reference_solver : str
        Solver ID to use as reference (denominator for speedup calculation)
    selected_solvers : list[str]
        List of solver_ids to include in the plot
    problem_pattern : str, optional
        Regex pattern to match problem_id
    selected_datasets : list[str], optional
        List of dataset_ids to include. If None, use all datasets.
    dataset_regex : str, optional
        Regex pattern to match dataset_id
    bins : int
        Number of histogram bins
    bin_range : tuple[float, float], optional
        Range for bins (min, max). If None, auto-computed.
    figsize : tuple[float, float]
        Figure size in inches
    reduce_metric : str
        How to aggregate multiple runs of the same problem ("min", "max", "mean")

    Returns
    -------
    fig : matplotlib.figure.Figure
        The generated figure
    """
    if len(selected_solvers) == 0:
        raise ValueError("No solvers selected")

    if reference_solver not in all_results:
        raise ValueError(
            f"Reference solver '{reference_solver}' not found. "
            f"Available solvers: {list(all_results.keys())}"
        )

    # Extract and filter data for reference solver
    ref_df = extract_timings(all_results, reference_solver, problem_pattern)

    # Filter by dataset if specified
    if selected_datasets is not None:
        ref_df = ref_df[ref_df["dataset_id"].isin(selected_datasets)]

    # Filter by dataset regex if specified
    if dataset_regex is not None:
        ref_df = ref_df[ref_df["dataset_id"].str.match(dataset_regex, na=False)]

    # Check if metric exists
    if metric not in ref_df.columns:
        raise ValueError(
            f"Metric '{metric}' not found in data for reference solver '{reference_solver}'"
        )

    # Select the aggregate type
    ref_df = ref_df[ref_df["aggregate_name"] == reduce_metric]

    # Keep reference data as DataFrame for efficient merging
    ref_values = ref_df[["problem_id", metric]].rename(columns={metric: "ref_metric"})

    # Extract and filter data for each solver, computing speedup
    solver_data = {}
    all_datasets = set()

    for solver_id in selected_solvers:
        df = extract_timings(all_results, solver_id, problem_pattern)

        # Filter by dataset if specified
        if selected_datasets is not None:
            df = df[df["dataset_id"].isin(selected_datasets)]

        # Filter by dataset regex if specified
        if dataset_regex is not None:
            df = df[df["dataset_id"].str.match(dataset_regex, na=False)]

        # Check if metric exists
        if metric not in df.columns:
            raise ValueError(
                f"Metric '{metric}' not found in data for solver '{solver_id}'"
            )

        # Select the aggregate type
        df = df[df["aggregate_name"] == reduce_metric]

        # Compute speedup: reference_value / solver_value using merge
        df = df.merge(ref_values, on="problem_id", how="inner").copy()
        df["speedup"] = np.where(df[metric] != 0, df["ref_metric"] / df[metric], np.nan)
        df = df.drop(columns=["ref_metric"])

        solver_data[solver_id] = df
        all_datasets.update(df["dataset_id"].unique())

    # Determine bin range if not specified
    if bin_range is None:
        # Concatenate all speedup values efficiently
        all_values = pd.concat([df["speedup"].dropna() for df in solver_data.values()], ignore_index=True)
        if len(all_values) == 0:
            raise ValueError("No data available for the selected metric and filters")
        bin_range = (all_values.min(), all_values.max())

    # Create bins with nice bin width
    bin_edges, actual_bins = round_to_nice_bin_width(bin_range[0], bin_range[1], bins)

    # Sort datasets naturally (considering numeric values in parentheses)
    def natural_sort_key(dataset_name):
        """Extract numeric components for natural sorting."""
        # Extract numbers from strings like "MassSprings(30, 64)"
        parts = re.findall(r"(\d+)", str(dataset_name))
        return [int(part) for part in parts] if parts else [0]

    all_datasets_sorted = sorted(all_datasets, key=natural_sort_key)

    # Color mapping for datasets (not solvers anymore)
    dataset_color_map = {
        dataset: hist_colors[i % len(hist_colors)]
        for i, dataset in enumerate(all_datasets_sorted)
    }

    # Create figure with subplots (one per solver)
    n_solvers = len(selected_solvers)
    fig, axes = plt.subplots(n_solvers, 1, sharex=True, sharey=True, figsize=figsize)
    if n_solvers == 1:
        axes = [axes]

    # Get reference solver name for labels
    ref_name = reference_solver
    if "solver_name" in ref_df.columns and not ref_df["solver_name"].isnull().all():
        try:
            ref_name = str(ref_df["solver_name"].iloc[0])
            ref_name = format_solver_name(ref_name)
            if not ref_name:
                ref_name = reference_solver
        except Exception:
            pass

    for ax, solver_id in zip(axes, selected_solvers):
        df = solver_data[solver_id]

        # Get solver name for label
        label = solver_id
        if "solver_name" in df.columns and not df["solver_name"].isnull().all():
            try:
                label = str(df["solver_name"].iloc[0])
                label = format_solver_name(label)
                if not label:
                    label = solver_id
            except Exception:
                pass

        # Create stacked histogram with one series per dataset
        dataset_values = []
        dataset_labels = []
        dataset_colors = []

        for dataset_id in all_datasets_sorted:
            dataset_df = df[df["dataset_id"] == dataset_id]
            if len(dataset_df) > 0:
                dataset_values.append(dataset_df["speedup"].dropna().values)
                n_inst = len(dataset_df)
                lbl, _ = format_dataset(dataset_id, all_datasets_sorted)
                dataset_labels.append(f"${n_inst}\\times$ {lbl}")
                dataset_colors.append(dataset_color_map[dataset_id])

        # Plot stacked histogram
        ax.hist(
            dataset_values,
            bins=bin_edges.tolist(),
            rwidth=0.85,
            color=dataset_colors,
            alpha=0.8,
            stacked=True,
            label=dataset_labels,
        )

        # Set title as "solver compared to reference"
        ax.set_title(f"{label} compared to {ref_name}")
        ax.set_ylabel("Count")
        ax.grid(True, alpha=0.3, axis="y")

        # Add vertical line at speedup = 1.0
        ax.axvline(x=1.0, color="black", linestyle="--", linewidth=1, alpha=0.7)

        # Add legend only to the first subplot
        if show_legend and ax == axes[0] and len(dataset_labels) > 1:
            ax.legend(loc="best", fontsize=9, framealpha=0.6)

    # Set x-label only on bottom plot
    axes[-1].set_xlabel("Speedup")
    axes[-1].set_xlim(0, None)

    # Super title - without "relative to {solver}"
    metric_pretty = METRIC_PRETTY.get(metric, metric.replace("_", " ").capitalize())
    fig.suptitle(
        f"Histogram of speedup ({metric_pretty})",
        fontsize=14,
    )

    fig.align_ylabels()
    plt.tight_layout()

    return fig


@click.command()
@click.argument("file", type=click.Path(exists=True))
@click.option(
    "--metric",
    "metrics",
    multiple=True,
    default=None,
    help="Metric to plot (default: time, ignored for --timing-breakdown)",
)
@click.option(
    "--solver",
    "solvers",
    multiple=True,
    required=True,
    help="Solver ID to plot (can be specified multiple times)",
)
@click.option(
    "--aggregate",
    default="min",
    help="Aggregate type to use: min, max, mean, median (default: min)",
)
@click.option(
    "--problem-pattern",
    help="Regex pattern to filter problem_id (e.g., 'spring-mass.*seed=0')",
)
@click.option(
    "--dataset",
    "datasets",
    multiple=True,
    help="Dataset ID to include (can be specified multiple times, default: all)",
)
@click.option(
    "--dataset-regex",
    help="Regex pattern to filter dataset_id (e.g., 'CentroidalQuadruped\\(N=\\d+, J=4\\)')",
)
@click.option("--bins", default=50, help="Number of histogram bins (default: 50)")
@click.option("--bin-range", help="Bin range as 'min,max' (default: auto)")
@click.option(
    "--output", default=None, help="Output PDF filename (default: hist_{metric}.pdf)"
)
@click.option(
    "--figsize", default="6,5", help="Figure size as 'width,height' in inches"
)
@click.option(
    "--reduce-metric",
    default="min",
    help="How to aggregate multiple runs: 'median', 'mean' or 'min' (default: min)",
)
@click.option(
    "--all-metrics", is_flag=True, help="Generate histograms for all common metrics"
)
@click.option(
    "--speedup", is_flag=True, help="Plot speedup relative to a reference solver"
)
@click.option(
    "--reference-solver",
    "reference_solvers",
    multiple=True,
    help="Reference solver for speedup calculation (can be specified multiple times for box plots)",
)
@click.option(
    "--no-legend", is_flag=True, help="Hide the legend in the plots"
)
@click.option(
    "--scaling", is_flag=True, help="Create a scaling plot (speedup vs horizon length N)"
)
@click.option("--ylim", help="Y-axis limits for scaling plot as 'min,max' (default: auto)")
@click.option(
    "--logy", is_flag=True, help="Use logarithmic scale for y-axis in scaling plot"
)
@click.option(
    "--color-offset", default=0, help="Color offset for scaling plots (default: 0)"
)
@click.option(
    "--box-plot", is_flag=True, help="Create box plots on a single subplot"
)
@click.option(
    "--group-by",
    default="solver",
    help="How to group box plots: 'dataset' or 'solver' (default: solver)",
)
@click.option("--xlim", help="X-axis limits for box plot as 'min,max' (default: auto)")
@click.option(
    "--timing-breakdown", is_flag=True, help="Create a stacked bar chart showing timing breakdown"
)
@click.option(
    "--relative", is_flag=True, help="Show timing breakdown as fraction of total run time"
)
def main(
    file: str,
    metrics: tuple[str, ...],
    solvers: tuple[str, ...],
    aggregate: str,
    problem_pattern: Optional[str],
    datasets: tuple[str, ...],
    dataset_regex: Optional[str],
    bins: int,
    bin_range: Optional[str],
    output: Optional[str],
    figsize: str,
    reduce_metric: str,
    all_metrics: bool,
    speedup: bool,
    reference_solvers: tuple[str, ...],
    no_legend: bool,
    scaling: bool,
    ylim: Optional[str],
    logy: bool,
    color_offset: int,
    box_plot: bool,
    group_by: str,
    xlim: Optional[str],
    timing_breakdown: bool,
    relative: bool,
):
    """
    Generate histogram plots from benchmark JSON results and save to PDF.
    Each solver is plotted in its own subplot.
    
    Examples:
    
        # Positional file argument
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" --solver "cyqlone(v=1,p=1)"
        
        # Use mean aggregate instead of minimum
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" --aggregate mean
        
        # Plot with problem pattern filter
        python hist_plot_from_json.py spring-mass.json --metric inner_iter \\
            --solver "cyqlone(v=4,p=8)" --solver "cyqlone(v=1,p=1)" \\
            --problem-pattern "spring-mass.*seed=0"
        
        # Filter by specific datasets
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" \\
            --dataset "MassSprings(12, 32)" --dataset "MassSprings(12, 64)"
        
        # Filter by dataset regex pattern
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" \\
            --dataset-regex "MassSprings\\(6, \\d+\\)"
        
        # Generate histograms for all common metrics
        python hist_plot_from_json.py spring-mass.json \\
            --solver "cyqlone(v=4,p=8)" --solver "cyqlone(v=1,p=1)" --all-metrics
        
        # Plot speedup relative to a reference solver
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" --solver "cyqlone(v=1,p=1)" \\
            --speedup --reference-solver "hpipm"
        
        # Create box plots
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" --solver "hpipm" --box-plot

        # Create quadruped box plots, grouping seeds by N and J
        python hist_plot_from_json.py benchmark-quad-full.json --metric time \\
            --solver "fancyqlone(p=8,v=4,cm,zero)" --solver "hpipm(zero)" \\
            --box-plot --group-by dataset \\
            --dataset-regex "CentroidalQuadruped\\(N=\\d+, J=4\\)"
        
        # Create box plots with speedup relative to reference solver
        python hist_plot_from_json.py spring-mass.json --metric time \\
            --solver "cyqlone(v=4,p=8)" --solver "cyqlone(v=1,p=1)" \\
            --box-plot --speedup --reference-solver "hpipm"
        
        # Create timing breakdown plot for a single solver
        python hist_plot_from_json.py spring-mass.json \\
            --solver "cyqlone(v=4,p=8)" --timing-breakdown
    """
    print(f"Loading data from: {file}")
    all_results = load_data(file)

    # Validate speedup option
    if speedup and not reference_solvers:
        raise click.UsageError(
            "--reference-solver is required when --speedup is specified"
        )

    # Parse solvers with aggregate suffix
    solver_list = [
        f"{s}_{aggregate}" if f"{s}_{aggregate}" in all_results else s for s in solvers
    ]

    # Parse reference solver(s) with aggregate suffix if speedup, scaling, or box_plot is enabled
    reference_solver_ids = None
    if reference_solvers:
        reference_solver_ids = []
        for ref_solver in reference_solvers:
            ref_id = (
                f"{ref_solver}_{aggregate}"
                if f"{ref_solver}_{aggregate}" in all_results
                else ref_solver
            )
            if ref_id not in all_results:
                raise ValueError(
                    f"Reference solver '{ref_solver}' not found. "
                    f"Available solvers: {list(all_results.keys())}"
                )
            reference_solver_ids.append(ref_id)

    # Parse datasets
    dataset_list = list(datasets) if datasets else None

    # Parse bin_range
    bin_range_tuple = None
    if bin_range:
        try:
            min_val, max_val = map(float, bin_range.split(","))
            bin_range_tuple = (min_val, max_val)
        except:
            print(f"Warning: Invalid bin-range '{bin_range}', using auto range")

    # Parse ylim
    ylim_tuple = None
    if ylim:
        try:
            min_val, max_val = map(float, ylim.split(","))
            ylim_tuple = (min_val, max_val)
        except:
            print(f"Warning: Invalid ylim '{ylim}', using auto range")

    # Parse xlim
    xlim_tuple = None
    if xlim:
        try:
            min_val, max_val = map(float, xlim.split(","))
            xlim_tuple = (min_val, max_val)
        except:
            print(f"Warning: Invalid xlim '{xlim}', using auto range")

    # Parse figsize
    try:
        width, height = map(float, figsize.split(","))
        fig_size = (width, height)
    except:
        print(f"Warning: Invalid figsize '{figsize}', using default (10, 8)")
        fig_size = (10, 8)

    # Get available datasets and solvers
    first_df = next(iter(all_results.values()))
    available_datasets = list(first_df["dataset_id"].unique())
    available_solvers = list(all_results.keys())

    print(f"Available datasets: {available_datasets}")
    print(f"Available solvers: {available_solvers}")
    print(f"Selected solvers: {solver_list}")

    # Determine metrics to plot
    if timing_breakdown:
        # For timing breakdown, we don't use the metric option
        metrics_to_plot = ["time"]  # Use a dummy metric for the loop
    elif all_metrics:
        metrics_to_plot = [m for m in DEFAULT_METRICS if m in first_df.columns]
        # Add extra metrics
        extra_metrics = [
            c
            for c in first_df.columns
            if c.startswith("time_") and c not in metrics_to_plot
        ]
        metrics_to_plot.extend(extra_metrics)
        print(f"Generating plots for {len(metrics_to_plot)} metrics: {metrics_to_plot}")
    elif metrics:
        metrics_to_plot = metrics
    else:
        # Default to "time" if no metric specified
        metrics_to_plot = ("time",)

    # Generate plots
    for current_metric in metrics_to_plot:
        try:
            print(f"\nGenerating histogram for metric: {current_metric}")

            if timing_breakdown:
                # Generate timing breakdown plot (requires a single solver)
                if len(solver_list) != 1:
                    raise click.UsageError(
                        "--timing-breakdown requires exactly one solver to be specified"
                    )
                fig = create_timing_breakdown_plot(
                    all_results,
                    solver=solver_list[0],
                    problem_pattern=problem_pattern,
                    selected_datasets=dataset_list,
                    dataset_regex=dataset_regex,
                    figsize=fig_size,
                    reduce_metric=reduce_metric,
                    show_legend=not no_legend,
                    relative=relative,
                )
            elif scaling:
                # Generate scaling plot (reference_solver is optional)
                fig = create_scaling_plot(
                    all_results,
                    current_metric,
                    solvers=solver_list,
                    reference_solver=reference_solver_ids[0] if reference_solver_ids else None,
                    problem_pattern=problem_pattern,
                    selected_datasets=dataset_list,
                    dataset_regex=dataset_regex,
                    figsize=fig_size,
                    reduce_metric=reduce_metric,
                    show_legend=not no_legend,
                    ylim=ylim_tuple,
                    logy=logy,
                    color_offset=color_offset,
                )
            elif speedup:
                # Generate speedup plot
                assert reference_solver_ids is not None  # Validated above
                fig = create_speedup_plot(
                    all_results,
                    current_metric,
                    reference_solver=reference_solver_ids[0],
                    selected_solvers=solver_list,
                    problem_pattern=problem_pattern,
                    selected_datasets=dataset_list,
                    dataset_regex=dataset_regex,
                    bins=bins,
                    bin_range=bin_range_tuple,
                    figsize=fig_size,
                    reduce_metric=reduce_metric,
                    show_legend=not no_legend,
                )
            elif box_plot:
                # Generate box plot
                fig = create_box_plot(
                    all_results,
                    current_metric,
                    selected_solvers=solver_list,
                    reference_solver=reference_solver_ids,
                    problem_pattern=problem_pattern,
                    selected_datasets=dataset_list,
                    dataset_regex=dataset_regex,
                    figsize=fig_size,
                    reduce_metric=reduce_metric,
                    show_legend=not no_legend,
                    group_by=group_by,
                    xlim=xlim_tuple,
                    logy=logy
                )
            else:
                # Generate regular histogram
                fig = create_histogram_plot(
                    all_results,
                    current_metric,
                    selected_solvers=solver_list,
                    problem_pattern=problem_pattern,
                    selected_datasets=dataset_list,
                    dataset_regex=dataset_regex,
                    bins=bins,
                    bin_range=bin_range_tuple,
                    figsize=fig_size,
                    reduce_metric=reduce_metric,
                    show_legend=not no_legend,
                )

            # Determine output filename
            if output and not all_metrics:
                output_file = output
                output_file = output_file.replace("{metric}", current_metric)
            else:
                # Sanitize metric name for filename
                safe_metric = current_metric.replace(":", "_").replace("/", "_")
                if timing_breakdown:
                    prefix = "timing_breakdown"
                elif scaling:
                    prefix = "scaling"
                elif speedup:
                    prefix = "speedup"
                elif box_plot:
                    prefix = "box"
                else:
                    prefix = "hist"
                output_file = f"{prefix}_{safe_metric}.pdf"

            # Save to PDF
            fig.savefig(output_file, dpi=300)
            print(f"Saved histogram to: {output_file}")

            plt.close(fig)

        except Exception as e:
            print(f"Error generating histogram for metric '{current_metric}': {e}")
            import traceback

            traceback.print_exc()
            continue

    print("\nDone!")


if __name__ == "__main__":
    main()
