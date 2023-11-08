#include "random_source.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int fd;

enum
{
    BYTES = 4,
};

static double
next(RandomSource *src)
{
    unsigned long long buf;
    if (read(fd, &buf, BYTES) != BYTES) {
        fprintf(stderr, "read err\n");
        exit(1);
    }

    buf %= ULLONG_MAX;
    return (double) buf / ULLONG_MAX;
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

    if (close(fd) == EOF) {
        fprintf(stderr, "fclose err\n");
        exit(1);
    }

    return NULL;
}

RandomSource *
random_random_factory(const char *params)
{
    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "open err\n");
        exit(1);
    }

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
