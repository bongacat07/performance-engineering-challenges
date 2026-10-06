#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

const size_t TABLE_SIZE = 50000000;

const u_int64_t SEED_1 = 0x9E3779B97F4A7C15;
const u_int64_t SEED_2 = 0xC2B2AE3D27D4EB4F;

uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

int16_t* create_table(u_int64_t seed)
{
    uint64_t state = seed;

    int16_t *table = calloc(TABLE_SIZE, sizeof(int16_t));
    if (table == NULL)
        return NULL;

    for (size_t i = 0; i < TABLE_SIZE; i++) {
        state = splitmix64(state);
        table[i] = (int16_t)(state >> 48);
    }

    return table;
}
