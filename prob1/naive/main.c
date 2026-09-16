#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "../problem.h"

#define WARMUP_RUNS 3
#define MEASURED_RUNS 20

struct result {
    size_t count;
    uint32_t *id;
};

struct result sort(struct record *records);

static uint64_t elapsed_ns(struct timespec start, struct timespec end)
{
    return (uint64_t)(end.tv_sec - start.tv_sec) * 1000000000ULL
         + (uint64_t)end.tv_nsec
         - (uint64_t)start.tv_nsec;
}

static int compare_u64(const void *a, const void *b)
{
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;

    return (x > y) - (x < y);
}

int main(void)
{
    struct record *records = generate_record();

    if (records == NULL) {
        fprintf(stderr, "Failed to generate records\n");
        return 1;
    }


    for (int i = 0; i < WARMUP_RUNS; i++) {
        struct result result = sort(records);
        free(result.id);
    }

    uint64_t times[MEASURED_RUNS];
    size_t count = 0;

    for (int i = 0; i < MEASURED_RUNS; i++) {
        struct timespec start;
        struct timespec end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        struct result result = sort(records);

        clock_gettime(CLOCK_MONOTONIC, &end);

        if (result.id == NULL && result.count != 0) {
            fprintf(stderr, "Failed to allocate result\n");
            free(records);
            return 1;
        }

        times[i] = elapsed_ns(start, end);

        if (i == 0)
            count = result.count;

        free(result.id);
    }

    qsort(times, MEASURED_RUNS, sizeof(times[0]), compare_u64);

    uint64_t median = times[MEASURED_RUNS / 2];

    printf("Records: %zu\n", RECORDSIZE);
    printf("Matches: %zu\n", count);
    printf("Median:  %lu ns\n", median);
    printf("Median: %.3f ms\n", median / 1000000.0);

    free(records);

    return 0;
}
