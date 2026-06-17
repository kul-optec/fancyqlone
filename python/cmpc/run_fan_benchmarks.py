#!/usr/bin/env python3
# """
# Run fan-CyQPALM benchmark sweeps and generate a PGFPlots figure.

# Sweep:
#     num_branches in {2, 4, 8}
#     nx in NX_VALUES
#     nu = nx / 3

# Outputs:
#     - CSV with raw benchmark rows
#     - PGFPlots .tex figure plotting nx vs speedup
#     - one .dat file per branch count, used by PGFPlots

# Example:
#     python3 run_fan_benchmarks.py \
#         --exe build/Release/examples/fan-cyqlone \
#         --N 256 \
#         --processors 8 \
#         --nx-values 6 9 12 15 18 24 30 36 48 60 \
#         --branches 2 4 8 \
#         --out-csv fan_qpalm_sweep.csv \
#         --out-tex fan_qpalm_speedup_vs_nx.tex

# Then in LaTeX/Beamer:
#     \input{fan_qpalm_speedup_vs_nx.tex}

# Required LaTeX packages:
#     \usepackage{pgfplots}
#     \pgfplotsset{compat=1.18}
# """

from __future__ import annotations

import argparse
import csv
import math
import os
import subprocess
import sys
from pathlib import Path
from typing import Iterable

import pandas as pd


DEFAULT_NX_VALUES = [6, 9, 12, 15, 18, 24, 30, 36, 48, 60]
DEFAULT_BRANCHES = [2, 4, 8]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run fan benchmark sweep and generate PGFPlots output."
    )

    parser.add_argument(
        "--exe",
        type=Path,
        default=Path("build/Release/examples/fan-cyqlone"),
        help="Path to benchmark executable.",
    )
    parser.add_argument("--N", type=int, default=256, help="Prediction horizon.")
    parser.add_argument("--ny", type=int, default=5, help="Number of stage constraints.")
    parser.add_argument("--ny-N", type=int, default=0, help="Number of terminal constraints.")
    parser.add_argument("--processors", type=int, default=8, help="Number of processors.")
    parser.add_argument("--warmup", type=int, default=50, help="Number of warmup runs.")
    parser.add_argument("--tol", type=str, default="1e-7", help="Solver tolerance.")
    parser.add_argument(
        "--nx-values",
        type=int,
        nargs="+",
        default=DEFAULT_NX_VALUES,
        help="Values of nx. nu is set to nx/3, so these should be divisible by 3.",
    )
    parser.add_argument(
        "--branches",
        type=int,
        nargs="+",
        default=DEFAULT_BRANCHES,
        help="Numbers of fan branches to benchmark.",
    )
    parser.add_argument(
        "--out-csv",
        type=Path,
        default=Path("fan_qpalm_sweep.csv"),
        help="Output CSV file. The benchmark appends to this file.",
    )
    parser.add_argument(
        "--out-tex",
        type=Path,
        default=Path("fan_qpalm_speedup_vs_nx.tex"),
        help="Output PGFPlots .tex file.",
    )
    parser.add_argument(
        "--dat-dir",
        type=Path,
        default=Path("pgfplots_data"),
        help="Directory for PGFPlots .dat files.",
    )
    parser.add_argument(
        "--append",
        action="store_true",
        help="Append to existing CSV instead of deleting it first.",
    )
    parser.add_argument(
        "--repeat",
        type=int,
        default=1,
        help="Repeat each benchmark point this many times. PGFPlots uses mean speedup.",
    )
    parser.add_argument(
        "--skip-run",
        action="store_true",
        help="Do not run benchmark; only regenerate PGFPlots files from existing CSV.",
    )

    return parser.parse_args()


def run_command(cmd: list[str]) -> None:
    print("Running:", " ".join(cmd), flush=True)
    subprocess.run(cmd, check=True)


def run_sweep(args: argparse.Namespace) -> None:
    exe = args.exe

    if not exe.exists():
        raise FileNotFoundError(f"Benchmark executable does not exist: {exe}")

    if not os.access(exe, os.X_OK):
        raise PermissionError(f"Benchmark executable is not executable: {exe}")

    if not args.append and args.out_csv.exists():
        args.out_csv.unlink()

    for branches in args.branches:
        for nx in args.nx_values:
            if nx % 3 != 0:
                print(f"Skipping nx={nx}: not divisible by 3", file=sys.stderr)
                continue

            nu = nx // 3
            if nu == 1:
                ny=1
            else:
                ny = nu //2
            for rep in range(args.repeat):
                print(
                    f"\n=== branches={branches}, nx={nx}, nu={nu}, repeat={rep + 1}/{args.repeat} ==="
                )

                cmd = [
                    str(exe),
                    "--N", str(args.N),
                    "--nx", str(nx),
                    "--nu", str(nu),
                    "--ny", str(ny),
                    "--ny-N", str(args.ny_N),
                    "--branches", str(branches),
                    "--processors", str(args.processors),
                    "--warmup", str(args.warmup),
                    "--tol", str(args.tol),
                    "--out", str(args.out_csv),
                ]

                run_command(cmd)


def normalize_dataframe(df: pd.DataFrame) -> pd.DataFrame:
    """Normalize column names and filter invalid rows."""
    if "branches" in df.columns and "num_branches" not in df.columns:
        df = df.rename(columns={"branches": "num_branches"})
    if "num_proc" in df.columns and "processors" not in df.columns:
        df = df.rename(columns={"num_proc": "processors"})

    required = {"nx", "nu", "num_branches", "speedup"}
    missing = required - set(df.columns)
    if missing:
        raise RuntimeError(
            f"CSV is missing required columns {missing}. Available columns: {list(df.columns)}"
        )

    # Filter statuses if available. This supports either strings or numeric enum values.
    # If your converged enum is printed as 0, this keeps 0 as well.
    for col in ["fan_status", "combined_status"]:
        if col in df.columns:
            s = df[col].astype(str)
            mask = s.str.contains("Converged", case=False, regex=False) | (s == "0")
            df = df[mask].copy()

    for col in ["nx", "nu", "num_branches", "speedup"]:
        df[col] = pd.to_numeric(df[col], errors="coerce")

    df = df.dropna(subset=["nx", "nu", "num_branches", "speedup"])
    df = df[df["speedup"].map(math.isfinite)]

    return df


def write_dat_files(df: pd.DataFrame, dat_dir: Path) -> dict[int, Path]:
    dat_dir.mkdir(parents=True, exist_ok=True)

    dat_files: dict[int, Path] = {}

    for branches, group in sorted(df.groupby("num_branches")):
        branches_int = int(branches)
        out = dat_dir / f"speedup_branches_{branches_int}.dat"

        # Average repeats at the same (nx, nu, branches).
        grouped = (
            group.groupby(["nx", "nu"], as_index=False)
            .agg(
                speedup_mean=("speedup", "mean"),
                speedup_std=("speedup", "std"),
                samples=("speedup", "count"),
            )
            .sort_values("nx")
        )
        grouped["speedup_std"] = grouped["speedup_std"].fillna(0.0)

        grouped.to_csv(out, sep=" ", index=False, float_format="%.12g")
        dat_files[branches_int] = out

    return dat_files


def write_pgfplots_tex(
    *,
    tex_path: Path,
    dat_files: dict[int, Path],
    N: int,
    processors: int,
) -> None:
    """Write a standalone PGFPlots figure fragment."""
    tex_path.parent.mkdir(parents=True, exist_ok=True)

    lines: list[str] = []
    lines.append(r"% Auto-generated by run_fan_benchmarks.py")
    lines.append(r"% Requires: \usepackage{pgfplots} and \pgfplotsset{compat=1.18}")
    lines.append(r"\begin{tikzpicture}")
    lines.append(r"\begin{axis}[")
    lines.append(r"    width=0.86\linewidth,")
    lines.append(r"    height=0.55\linewidth,")
    lines.append(r"    grid=both,")
    lines.append(r"    xlabel={$n_x$},")
    lines.append(r"    ylabel={Speedup},")
    lines.append(rf"    title={{Fan solver speedup, $N={N}$, processors={processors}, $n_u=n_x/3$}},")
    lines.append(r"    legend pos=north west,")
    lines.append(r"    mark options={scale=0.85},")
    lines.append(r"    every axis plot/.append style={thick},")
    lines.append(r"]")

    marks = ["*", "square*", "triangle*", "diamond*", "otimes*"]

    for idx, (branches, dat_path) in enumerate(sorted(dat_files.items())):
        # Use path relative to tex file if possible.
        try:
            plot_path = dat_path.relative_to(tex_path.parent)
        except ValueError:
            plot_path = dat_path

        mark = marks[idx % len(marks)]
        lines.append(
            rf"\addplot+[mark={mark}] table[x=nx,y=speedup_mean] {{{plot_path.as_posix()}}};"
        )
        lines.append(rf"\addlegendentry{{{branches} branches}}")

    lines.append(r"\end{axis}")
    lines.append(r"\end{tikzpicture}")
    lines.append("")

    tex_path.write_text("\n".join(lines))


def main() -> None:
    args = parse_args()

    if not args.skip_run:
        run_sweep(args)

    if not args.out_csv.exists():
        raise FileNotFoundError(f"CSV file does not exist: {args.out_csv}")

    df = pd.read_csv(args.out_csv)
    df = normalize_dataframe(df)

    if df.empty:
        raise RuntimeError("No valid benchmark rows found after filtering.")

    dat_files = write_dat_files(df, args.dat_dir)
    write_pgfplots_tex(
        tex_path=args.out_tex,
        dat_files=dat_files,
        N=args.N,
        processors=args.processors,
    )

    print("\nGenerated files:")
    print(f"  CSV:       {args.out_csv}")
    print(f"  PGFPlots:  {args.out_tex}")
    print(f"  data dir:  {args.dat_dir}")

    print("\nMean speedups:")
    summary = (
        df.groupby(["num_branches", "nx", "nu"], as_index=False)
        .agg(speedup_mean=("speedup", "mean"), samples=("speedup", "count"))
        .sort_values(["num_branches", "nx"])
    )
    print(summary.to_string(index=False))


if __name__ == "__main__":
    main()
