#include "random_source.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>

static RandomSource *destroy(RandomSource *src);
static double next(RandomSource *src);

const char name_l[] = "linear";
const char name_r[] = "random";

enum {
    ARGC = 4,
    FOO_NAME = 1,
    FOO_SIZE = 2,
    FOO_ARG = 3,
    BASE = 10,
    MAX_SIZE = 100000
};

int
main(int argc, char **argv)
{
    if (argc != ARGC) {
        fprintf(stderr, "Input error\n");
        exit(1);
    }

    errno = 0;
    char *eptr = NULL;
    long count = strtol(argv[FOO_SIZE], &eptr, BASE);
    if (errno || *eptr || eptr == argv[FOO_SIZE] || count < 0 || count > MAX_SIZE) {
        fprintf(stderr, "Input err\n");
        exit(1);
    }

    RandomSource *rr;

    void *handle = dlopen(NULL, RTLD_LAZY);
    if (handle == NULL) {
        fprintf(stderr, "dlopen err\n");
        exit(1);
    }


    void *sym;
    if (strncmp(name_l, argv[FOO_NAME], sizeof(name_l) / sizeof(name_l[0])) == 0) {
        sym = dlsym(handle, "random_linear_factory");
        if (sym == NULL) {
            fprintf(stderr, "dlsym err\n");
            exit(1);
        }
        rr = ((RandomSource *(*) (const char *)) sym)(argv[FOO_ARG]);
    } else if (strncmp(name_r, argv[FOO_NAME], sizeof(name_r) / sizeof(name_r[0])) == 0) {
        sym = dlsym(handle, "random_random_factory");
        if (sym == NULL) {
            fprintf(stderr, "dlsym err\n");
            exit(1);
        }
        rr = ((RandomSource *(*) (const char *)) sym)(argv[FOO_ARG]);
    } else {
        fprintf(stderr, "STR ERR\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        printf("%.10g\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);

    return 0;
}
