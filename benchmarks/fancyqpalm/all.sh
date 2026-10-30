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
# One panel per J, with shared axes; writes a PDF and a PNG preview.
# python3 hist_plot_from_json.py "benchmark-quad.json" \
#     --output "benchmark-quad-scaling-$machine.pdf" \
#     --metric=time_per_iter --scaling --figsize=5.75,5.75\
#      --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "fancyqlone(p=$p,v=1,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)"--solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# python3 hist_plot_from_json.py "benchmark-quad.json" \
#     --output "benchmark-quad-scaling-$machine-log.pdf" \
#     --metric=time_per_iter --scaling --figsize=5.75,5.75 --logy\
#      --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "fancyqlone(p=$p,v=1,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# python3 hist_plot_from_json.py "benchmark-scaling.json" \
#     --output "benchmark-scaling-$machine-log.pdf" \
#     --metric=time_per_iter --scaling --figsize=5.75,5.75 --logy\
#      --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "fancyqlone(p=$p,v=1,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
python3 hist_plot_from_json.py "benchmark-quad.json" \
    --output "benchmark-$machine-quad-cold.pdf" \
    --metric=time --box-plot --logy --group-by=dataset --figsize=5.75,5.75\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# Quadruped total runtime versus J, with proportionally spaced branch counts.
python3 hist_plot_from_json.py "benchmark-quad.json" \
    --output "benchmark-$machine-quad-cold-J.pdf" \
    --metric=time --aggregate=median --box-plot --xvar=J --group-by=dataset --figsize=5.75,5.75 \
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
python3 hist_plot_from_json.py "benchmark-quad.json" \
    --output "benchmark-$machine-quad-cold-J-log.pdf" \
    --metric=time --aggregate=median --box-plot --xvar=J --logy --group-by=dataset --figsize=5.75,5.75 \
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(qpOasis)" --solver "piqp(multistage)"
# python3 hist_plot_from_json.py "benchmark-quad.json" \
#     --output "benchmark-$machine-quad-warm.pdf" \
#     --metric=time --box-plot --group-by=dataset --figsize=5.75,5.75\
#      --solver "fancyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift)" --solver "treeqp(qpOasis,shift)"
python3 hist_plot_from_json.py "benchmark-scaling-p.json" \
    --output "benchmark-scaling-$machine-p.pdf" \
    --metric=time_per_iter --aggregate=mean --scaling --figsize=5.75,5.75\
    --solver "fancyqlone(p=4,v=4,cm,zero)" --solver "serial-fancyqlone(p=4,v=4,cm,zero)"\
    --solver "fancyqlone(p=4,v=1,cm,zero)" --solver "serial-fancyqlone(p=4,v=1,cm,zero)"\
    --solver "fancyqlone(p=8,v=4,cm,zero)" --solver "serial-fancyqlone(p=8,v=4,cm,zero)"\
    --solver "fancyqlone(p=8,v=1,cm,zero)" --solver "serial-fancyqlone(p=8,v=1,cm,zero)"

python3 hist_plot_from_json.py "benchmark-scaling-J.json" \
    --output "benchmark-scaling-$machine-J.pdf" \
    --metric=time_per_iter --aggregate=mean --scaling --xvar=J --figsize=5.75,5.75\
    --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)"
python3 hist_plot_from_json.py "benchmark-scaling.json" \
    --output "benchmark-$machine-cold.pdf" \
    --metric=time --box-plot --group-by=dataset --figsize=5.75,5.75\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
python3 hist_plot_from_json.py "benchmark-scaling.json" \
    --output "benchmark-$machine-cold-log.pdf" \
    --metric=time --box-plot --logy --group-by=dataset --figsize=5.75,5.75\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
python3 hist_plot_from_json.py "benchmark-scaling-states.json" \
    --output "benchmark-$machine-cold-M.pdf" \
    --metric=time --box-plot --xvar=M --group-by=dataset --figsize=5.75,5.75\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
python3 hist_plot_from_json.py "benchmark-scaling-states.json" \
    --output "benchmark-$machine-cold-M-log.pdf" \
    --metric=time --box-plot --xvar=M --logy --xlim=0.5, --group-by=dataset --figsize=5.75,5.75\
     --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "hpipm(zero)" --solver "treeqp(clip)" --solver "piqp(multistage)"
 
 
 
 
    # --solver "fancyqlone(p=$p,v=$v,cm,zero)" --solver "treeqp(zero,QPOasis)"
# python3 hist_plot_from_json.py "benchmark-scaling.json" \
#     --output "benchmark-scaling-$machine-speed-J=4.pdf" \
#     --metric=time --xlim=0,150 --box-plot  --group-by=dataset --figsize=6,3.5\
#     --solver "fancyqlo²²²²²²²²²²²²²²²²²²ne(p=$p,v=$v,cm,zero)" --solver "serial-fancyqlone(p=$p,v=$v,cm,zero)" --solver "treeqp(clip)"\
#      --solver "hpipm(zero)" --solver "piqp(multistage)"  
# python3 hist_plot_from_json.py "benchmark-scaling.json" \
#     --output benchmark-grid-box-$machine-warm-J=4.pdf \
#     --metric=time --xlim=0,180 --box-plot --group-by=dataset --figsize=6,3.5 \
#     --solver "fancyqlone(p=$p,v=$v,cm,shift)" --solver "hpipm(shift,balance)" --solver "treeqp(clip,shift)"\
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
