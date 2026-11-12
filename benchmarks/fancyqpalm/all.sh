#!/usr/bin/env bash

set -euo pipefail

cd "$(dirname "$0")"
machine="${1:-nutella}"
# Usage: all.sh [machine] [output-directory], relative to this script's directory.
output_dir="${2:-../figures}"
mkdir -p "$output_dir"
export MPLBACKEND=Agg
python="${PYTHON:-python3}"
if [[ -z "${PYTHON:-}" && -z "${VIRTUAL_ENV:-}" && -x ../../.cyqlone/bin/python ]]; then
    python=../../.cyqlone/bin/python
fi
failed_plots=()
run_plot() {
    if "$python" "$@"; then
        return 0
    fi
    failed_plots+=("$*")
}
scaling_p_input="benchmark-scaling-p.json"
if [[ ! -f "$scaling_p_input" ]]; then
    scaling_p_input="benchmark-scaling-p-paper.json"
fi
scaling_j_input="benchmark-scaling-J.json"
if [[ ! -f "$scaling_j_input" ]]; then
    scaling_j_input="benchmark-scaling-J-paper.json"
fi
printf 'Scaling inputs: %s, %s\nOutput directory: %s\n' \
    "$scaling_p_input" "$scaling_j_input" "$output_dir"
case "$machine" in
    blacksad*) p=8; v=4 ;;
    nutella*) p=8; v=4 ;;
    vsc-ice*) p=16; v=4 ;;
    vsc-sapph) p=32; v=4 ;;
    hpc) p=16; v=4 ;;
    rpi5*) p=4; v=2 ;;
    *) p=8; v=4 ;;
esac

run_plot hist_plot_from_json.py "benchmark-quad-scaling.json" \
    --output "$output_dir/benchmark-$machine-quad-cold.pdf" \
    --metric=time --reduce-metric=median --box-plot --xvar=N --logy --box-width=0.65 --ylim=,2000 --no-title --group-by=dataset --figsize=5.75,4.0\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# Quadruped total runtime versus J, with proportionally spaced branch counts.

run_plot hist_plot_from_json.py "benchmark-quad-scaling-J.json" \
    --output "$output_dir/benchmark-$machine-quad-cold-J-log.pdf" \
    --metric=time --aggregate=median --reduce-metric=median --box-plot --box-width=0.35 --xvar=J --logy --ylim=,700 --no-title --group-by=dataset --figsize=5.75,4.0 \
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# Alternative: logarithmically spaced branch counts, with the same runtime scale.
run_plot hist_plot_from_json.py "benchmark-quad-scaling-J.json" \
    --output "$output_dir/benchmark-$machine-quad-cold-J-loglog.pdf" \
    --metric=time --aggregate=median --reduce-metric=median --box-plot --box-width=0.35 --xvar=J --logx --logy --ylim=,700 --no-title --group-by=dataset --figsize=5.75,4.0 \
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"

run_plot hist_plot_from_json.py "$scaling_p_input" \
    --output "$output_dir/benchmark-scaling-$machine-p.pdf" \
    --metric=time_per_iter --aggregate=mean --scaling --ylim=0, --no-title --figsize=5.75,5.0\
    --solver "fancyqlone(p=4,v=4,cm,zero)" --solver "serial-fancyqlone(p=4,v=4,cm,zero)"\
    --solver "fancyqlone(p=4,v=1,cm,zero)" --solver "serial-fancyqlone(p=4,v=1,cm,zero)"\
    --solver "fancyqlone(p=8,v=4,cm,zero)" --solver "serial-fancyqlone(p=8,v=4,cm,zero)"\
    --solver "fancyqlone(p=8,v=1,cm,zero)" --solver "serial-fancyqlone(p=8,v=1,cm,zero)"

run_plot hist_plot_from_json.py "$scaling_j_input" \
    --output "$output_dir/benchmark-scaling-$machine-J.pdf" \
    --metric=time_per_iter --aggregate=mean --scaling --xvar=J --ylim=0, --no-title --figsize=5.75,4.0\
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)"

run_plot hist_plot_from_json.py "benchmark-scaling.json" \
    --output "$output_dir/benchmark-$machine-cold-log.pdf" \
    --metric=time --reduce-metric=median --box-plot --xvar=N --logy --ylim=0.7,200 --box-width=0.50 --no-title --group-by=dataset --figsize=5.75,4.0\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"

run_plot hist_plot_from_json.py "benchmark-scaling-states.json" \
    --output "$output_dir/benchmark-$machine-cold-M-log.pdf" \
    --metric=time --reduce-metric=median --box-plot --xvar=M --logy --box-width=0.50 --no-title --ylim=0.5,200 --group-by=dataset --figsize=5.75,4.0\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
if (( ${#failed_plots[@]} )); then
    printf 'Failed plot commands:\n' >&2
    printf '  %s\n' "${failed_plots[@]}" >&2
    exit 1
fi