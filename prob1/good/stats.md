# Stats for good

Records: 10000000
Matches: 4999530
Median:  9659805 ns
Median: 9.660 ms


## Performance counter stats:

824,408,297      cpu_core/cycles/u
2,300,276,883      cpu_core/instructions/u
240,162,757      cpu_core/branches/u
2,956      cpu_core/branch-misses/u

| Metric         |     Naive |     Good |         Improvement |
| -------------- | --------: | -------: | ------------------: |
| Median time    | 37.810 ms | 9.660 ms |    **3.91× faster** |
| Time reduction |         — |        — | **74.4% less time** |
| Cycles         |    3.786B |     824M |     **78.2% fewer** |
| Instructions   |    1.725B |   2.300B |      **33.3% more** |
| Branches       |    470.2M |   240.2M |     **48.9% fewer** |
| Branch misses  |   114.93M |    2,956 |   **99.997% fewer** |
