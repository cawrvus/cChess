#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void *new_mem(size_t mem_size, size_t mem_count, _Bool zeroed) {
    void *mem = zeroed ? calloc(mem_count, mem_size) : malloc(mem_count * mem_size);
    if (mem == NULL)
        terminate("Failure during memory allocation.");
    return mem;
}

void terminate(char *msg) {
    fprintf(stderr, msg);
    exit(EXIT_FAILURE);
}
