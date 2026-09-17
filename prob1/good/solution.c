#include "../problem.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#define THRESHOLD 500000

struct result {
    size_t count;
    uint32_t *id;
};

struct result sort(struct record *records)
{
    uint32_t *id = calloc(RECORDSIZE, sizeof(uint32_t));

    if (id == NULL) {
        return (struct result){0};
    }

    size_t count = 0;
    for (size_t i = 0; i < RECORDSIZE; i++) {
        int match = (records[i].record > THRESHOLD);
        id[count] = records[i].id;
        count += match;
    }

    return (struct result){
        .count = count,
        .id = id,
    };
}
