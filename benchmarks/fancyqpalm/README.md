# FanCyqlone benchmarks

Benchmarks used for the numerical experiments in the FanCyqlone paper.

```bash
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

