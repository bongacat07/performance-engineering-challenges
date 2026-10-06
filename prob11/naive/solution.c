
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "../problem.h"


uint64_t absolute_sum(int16_t *array1, int16_t *array2) {

    uint64_t sum = 0;

    for(size_t i = 0; i<TABLE_SIZE; i++) {
        sum  = sum + abs(array1[i]-array2[i]);
    }

    return sum;
}
