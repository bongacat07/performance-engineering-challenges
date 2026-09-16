# Question

You work on the real-time risk engine at a payments company. A separate scoring model has already assigned every incoming transaction a fraud score, and your job is the next stage of the pipeline: given **10,000,000 fixed-size records**, each containing a `uint32_t id` and a `uint32_t score`, output, in original order, densely packed with no gaps, the **id** of every record whose score exceeds a given threshold `T`. The case-review queue will pick them up.

Return the count of matches.

The threshold is tuned so that roughly half of all transactions clear it, which is exactly the distribution that makes this stage expensive.

## Explicit Workload

**Input size:** 10,000,000 records

**Layout:** 8 bytes/record, 80 MB total, well beyond the 24 MB L3 cache.

| Offset | Type       | Field   |
| -----: | ---------- | ------- |
|      0 | `uint32_t` | `id`    |
|      4 | `uint32_t` | `score` |

**Distribution:** Scores are uniformly random in `[0, 1,000,000)`, generated via `splitmix64` seeded with `0x2545F4914F6CDD1D`.

**Threshold:** `T = 500,000`, chosen so roughly 50% of scores pass. This is the worst case for branch prediction because the outcome is close to a coin flip.

## Correctness Requirements

The output order must match the input order.

The output array must be densely packed with no gaps.

The output array length must equal the true match count exactly.
