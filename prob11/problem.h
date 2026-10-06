#ifndef PROBLEM_H
#define PROBLEM_H

#include <stdint.h>
#include <stddef.h>

#define TABLE_SIZE 50000000

int16_t *generate_table(uint64_t seed);

#endif
