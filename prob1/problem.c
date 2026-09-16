#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

const size_t RECORDSIZE = 10000000;

struct record {
    uint32_t id;
    uint32_t record;
};

const uint64_t SEED = 0x2545F4914F6CDD1DULL;

uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

struct record *generate_record(void)
{
    uint64_t state = SEED;

    struct record *table =
        calloc(RECORDSIZE, sizeof(struct record));

    if (table == NULL)
        return NULL;

    for (size_t i = 0; i < RECORDSIZE; i++) {
        state = splitmix64(state);

        table[i].id = (uint32_t)i;
        table[i].record = (uint32_t)state;
    }

    return table;
}
