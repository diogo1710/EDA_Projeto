#ifndef __Main_h__
#define __Main_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// all memory is dynamic so 3 different types of 'lists' are used

typedef struct option {
    unsigned int machine;
    unsigned int prc_time;
    unsigned int opt_n;
    struct option *next;
} Option;

typedef struct operation {
    unsigned int opr_n; // current operation
    unsigned int opts;  // number of possible options for this operation
    Option *options;    // possible options head pointer
    struct operation *next;
} Operation;

typedef struct job {
    unsigned int job_n;    // jobs number
    unsigned int oprs;     // total of operations to complete the job
    Operation *operations; // operations head pointer
    struct job *next;
} Job;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
void clean_stdin();
#endif // __Main_h__