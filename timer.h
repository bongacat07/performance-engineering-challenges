#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <x86intrin.h>

static inline uint64_t timer_start(void)
{
    _mm_lfence();

    uint64_t t = __rdtsc();

    _mm_lfence();

    return t;
}

static inline uint64_t timer_end(void)
{
    unsigned int aux;

    uint64_t t = __rdtscp(&aux);

    _mm_lfence();

    return t;
}

static inline uint64_t measure_overhead(void)
{
    uint64_t best = UINT64_MAX;

    for (size_t i = 0; i < 10000; i++) {
        uint64_t start = timer_start();
        uint64_t end = timer_end();

        uint64_t ticks = end - start;

        if (ticks < best)
            best = ticks;
    }

    return best;
}

#endif // TIMER_H
