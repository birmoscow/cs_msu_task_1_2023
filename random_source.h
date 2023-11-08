#ifndef RANDOM_SOURCE_H
#define RANDOM_SOURCE_H

typedef struct RandomSource RandomSource;
typedef struct RandomSourceOperations
{
    RandomSource *(*destroy)(RandomSource *);
    double (*next)(RandomSource *);
} RandomSourceOperations;

struct RandomSource
{
    RandomSourceOperations *ops;
};

#endif
