#!/usr/bin/env bash

cd "$(dirname "$0")"
machine="${1:-nutella}"
case "$machine" in
    blacksad*) p=8; v=4 ;;
    nutella*) p=8; v=4 ;;
    vsc-ice*) p=16; v=4 ;;
    vsc-sapph) p=32; v=4 ;;
    hpc) p=16; v=4 ;;
    rpi5*) p=4; v=2 ;;
    *) p=8; v=4 ;;
esac
python3 hist_plot_from_json.py "benchmark-scaling.json" \
    --output benchmark-grid-box-$machine-cold-J=4.pdf \
    --metric=time --xlim=0,150 --box-plot --group-by=dataset --figsize=6,3.5 \
    --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)" --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero,balance)" --solver "hpipm(zero,speed)" --solver "piqp(multistage)" --solver "treeqp(clip)" --solver "treeqp(QPOasis)"\
    --dataset-regex 'MassSprings\(12, (32|64|96|128|192|256)\)'
# python3 hist_plot_from_json.py "benchmark-scaling.json" \
#     --output benchmark-grid-box-$machine-warm-J=1.pdf \
#     --metric=time --xlim=0,50 --box-plot --group-by=dataset --figsize=6,3.5 \
#     --solver "fancyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift,balance)" --solver "hpipm(shift,speed)"\
#     --dataset-regex 'MassSprings\(12, (32|64|96|128|192|256)\)'
# python3 hist_plot_from_json.py "$machine/benchmark-grid.json" \
#     --output benchmark-grid-box-$machine.pdf \
#     --metric=time --xlim=0,54 --box-plot --group-by=dataset --figsize=6,3.5 \
#     --solver "cyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" \
#     --solver "cyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift)" \
#     --dataset-regex 'MassSprings\(12, (32|64|96|128|192|256)\)'
# python3 hist_plot_from_json.py "$machine/benchmark-grid.json" \
#     --output benchmark-grid-box-M-$machine.pdf \
#     --metric=time --box-plot --group-by=dataset --figsize=6,3.08 \
#     --solver "cyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" \
#     --solver "cyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift)" \
#     --dataset-regex 'MassSprings\(\d+, 128\)'
# python3 hist_plot_from_json.py "$machine/benchmark-scaling.json" \
#     --output benchmark-scaling-classic-$machine.pdf \
#     --metric=time_per_iter --scaling --figsize=3.75,2.75 \
#     --solver "cyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift)"
# python3 hist_plot_from_json.py "$machine/benchmark-scaling.json" \
#     --output benchmark-scaling-classic-zoom-$machine.pdf \
#     --metric=time_per_iter --scaling --figsize=3.75,2.75 --ylim=0,0.9 \
#     --solver "cyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift)" --solver "cyqlone(p=$p,v=$v,cm,shift,upd=0)"
# python3 plot-scaling-stacked.py "$machine/benchmark-scaling.json" \
#     --output "benchmark-scaling-combined-$machine.pdf"
# python3 plot-scaling.py "$machine/benchmark-scaling-states.json" \
#     --xvar=M --log \
#     --output "benchmark-scaling-states-$machine.pdf" --tex --figsize=6,4.5
# python3 table_from_json.py $machine/benchmark-grid.json \
#     --output table_speedup-time-cold-150-$machine.tex \
#     --solver "cyqlone(p=$p,v=$v,cm,zero)" --reference-solver "hpipm(zero)"
# python3 table_from_json.py $machine/benchmark-grid.json \
#     --output table_speedup-time-warm-150-$machine.tex \
#     --solver "cyqlone(p=$p,v=$v,cm,shift)" --reference-solver "hpipm(shift)"
# python3 table_from_json.py $machine/benchmark-scaling.json \
#     --output table_speedup-time_per_iter-cold-150-$machine.tex --metric=time_per_iter \
#     --solver "cyqlone(p=$p,v=$v,cm,zero)" --reference-solver "hpipm(zero)"
