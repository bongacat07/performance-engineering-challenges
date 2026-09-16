#ifndef PROBLEM_H
#define PROBLEM_H

#include <stddef.h>
#include <stdint.h>

#define RECORDSIZE 10000000

struct record {
    uint32_t id;
    uint32_t record;
};

struct record *generate_record(void);

#endif
