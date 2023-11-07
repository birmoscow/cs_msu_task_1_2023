#include "random_source.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int fd;

static double
next(RandomSource *src)
{
    unsigned long long buf;
    read(fd, &buf, 4);
    printf("OTLADKA R : %llu, %llu\n", buf, ULLONG_MAX);
    return (double) buf / ULLONG_MAX;
}

static RandomSource
*destroy(RandomSource *src)
{
    if (src && src->ops) {
        free(src->ops);
    }
    if (src) {
        free(src);
    }
    return NULL;
}

RandomSource
*random_random_factory(const char *params) {
    fd = open("/dev/urandom", O_RDONLY);
    // check

    RandomSource *note = calloc(1, sizeof(*note));
    note->ops = calloc(1, sizeof(*(note->ops)));
    note->ops->next = &next;
    note->ops->destroy = &destroy;
    return note;
}
