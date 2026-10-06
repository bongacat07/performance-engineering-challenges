# Question

You work on the encoder team for a video streaming platform. Motion estimation, the step that finds how each block of a frame moved relative to the previous frame, runs a sum-of-absolute-differences comparison between candidate blocks millions of times per encoded video. Given two arrays of 50,000,000 `int16_t` values each, compute `sum(|a[i] - b[i]|)` for all `i`, as a 64-bit accumulator (to avoid overflow across 50,000,000 additions). It's one of the hottest inner loops in the entire encoder, run across every video uploaded to the platform, so a few nanoseconds saved per comparison compounds into real infrastructure cost.

## Explicit workload

Array size: 50,000,000 `int16_t` elements each, two arrays, generated via splitmix64 seeded with `0x9E3779B97F4A7C15` (array A) and `0xC2B2AE3D27D4EB4F` (array B), values uniform random over the full `int16_t` range

Total data: 200MB (2 arrays × 100MB), read sequentially once

Correctness: exact 64-bit sum match against a reference implementation
