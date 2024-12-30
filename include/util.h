#ifndef UTIL_H_
#define UTIL_H_

#include "./proc.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT_MAX_DEFAULT 256
#define PROC_INPUT_MAX_DEFAULT 8
#define NUM_PROC_INPUT_MAX_DEFAULT 4
#define NO_INPUT -1
#define EMPTY_INPUT 0
#define TOO_LONG -2
#define OK 1

int get_input(const char *prmpt, char *buff, size_t size);

int read_procs_from_input_file(char *input_file, proc *(*procs)[1024],
                               int *procs_len);
int read_procs_from_stdin(proc *(*procs)[1024], int *procs_len,
                          int fill_random);

#endif
