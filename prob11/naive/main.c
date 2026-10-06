#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "../problem.h"

#define WARMUP_RUNS 3
#define MEASURED_RUNS 20

uint64_t absolute_sum(int16_t *array1, int16_t *array2);

static int compare_u64(const void *a, const void *b)
{
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;

    return (x > y) - (x < y);
}

static uint64_t elapsed_ns(struct timespec start, struct timespec end)
{
    return (uint64_t)(end.tv_sec - start.tv_sec) * 1000000000ULL
         + (uint64_t)end.tv_nsec
         - (uint64_t)start.tv_nsec;
}

int main(void)
{
    uint64_t seed1 = 0x9E3779B97F4A7C15ULL;
    uint64_t seed2 = 0xC2B2AE3D27D4EB4FULL;

    int16_t *array1 = create_table(seed1);
    int16_t *array2 = create_table(seed2);

    if (array1 == NULL || array2 == NULL) {
        fprintf(stderr, "Failed to generate arrays\n");
        return 1;
    }

   volatile uint64_t benchmark_sink;

    for (int i = 0; i < WARMUP_RUNS; i++) {
        benchmark_sink = absolute_sum(array1, array2);
    }

    uint64_t times[MEASURED_RUNS];


    for (int i = 0; i < MEASURED_RUNS; i++) {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        benchmark_sink = absolute_sum(array1, array2);

        clock_gettime(CLOCK_MONOTONIC, &end);

        times[i] = elapsed_ns(start, end);
    }

    qsort(times, MEASURED_RUNS, sizeof(times[0]), compare_u64);

    uint64_t median = times[MEASURED_RUNS / 2];

    printf("Records: %zu\n", TABLE_SIZE);
    printf("Median: %" PRIu64 " ns\n", median);
    printf("Median: %.3f ms\n", median / 1000000.0);

    free(array1);
    free(array2);

    return 0;
}
