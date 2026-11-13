# FanCyqlone benchmarks

Benchmarks used for the numerical experiments in the FanCyqlone paper.
From the repository root:

```bash
cd benchmarks/fancyqpalm
./benchmark.sh deps
./benchmark.sh build
```

| Paper figure | Command |
|---|---|
| Fig. 2a — branch/time parallelism vs. horizon | `./benchmark.sh benchmark-scaling-p` |
| Fig. 2b — branch parallelism vs. number of branches | `./benchmark.sh benchmark-scaling-J` |
| Fig. 3 — spring-mass, varying horizon | `./benchmark.sh benchmark-scaling` |
| Fig. 4 — spring-mass, varying number of masses | `./benchmark.sh benchmark-scaling-states` |
| Fig. 5 — quadruped, varying horizon | `./benchmark.sh benchmark-quad-scaling` |
| Fig. 6 — quadruped, varying number of branches | `./benchmark.sh benchmark-quad-scaling-J` |

## Results

Benchmark commands save Google Benchmark JSON reports in `results/`.

## Plotting

After generating the results, run the standalone plotting script:

```bash
./plot.sh
```

To specify the machine label and output directory:

```bash
./plot.sh base ./figures
```
