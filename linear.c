#include "random_source.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static unsigned seed;

enum Consts
{
    MUL = 1103515245,
    INC = 12345,
    MOD = 0x80000000,
    MASK = 0x7FFFFFFF,
    BASE = 10
};

static double
next(RandomSource *src)
{
    double res = 0;
    seed = (MUL * seed + INC) % (unsigned) MOD;
    res = (double) seed / (unsigned) MOD;
    return res;
}

static RandomSource *
destroy(RandomSource *src)
{
    if (src && src->ops) {
        free(src->ops);
    }
    if (src) {
        free(src);
    }
    return NULL;
}

RandomSource *
random_linear_factory(const char *params)
{
    char *eptr = NULL;
    errno = 0;
    long count = strtol(params, &eptr, BASE);
    if (errno || *eptr || eptr == params || count < 0) {
        fprintf(stderr, "linear.c : strtol err\n");
        exit(1);
    }
    seed = count & MASK;

    RandomSource *note = calloc(1, sizeof(*note));
    if (note == NULL) {
        fprintf(stderr, "calloc err\n");
        exit(1);
    }
    note->ops = calloc(1, sizeof(*(note->ops)));
    if (note->ops == NULL) {
        fprintf(stderr, "calloc err\n");
        free(note);
        exit(1);
    }
    note->ops->next = &next;
    note->ops->destroy = &destroy;
    return note;
}
