#ifndef UTIL_H_
#define UTIL_H_

#include "./proc.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PROMPT_MAX_DEFAULT 256
#define PROC_INPUT_MAX_DEFAULT 8
#define NUM_PROC_INPUT_MAX_DEFAULT 4
#define NO_INPUT -1
#define EMPTY_INPUT 0
#define TOO_LONG -2
#define OK 1

int ensure_directory_exists(char *dir_path);
FILE *create_file(char *filename);
int append_str_to_file(FILE *f, char *s, int len);

int get_input(const char *prmpt, char *buff, size_t size);

int read_procs_from_input_file(char *input_file, proc *(*procs)[1024],
                               int *procs_len);
int read_procs_from_stdin(proc *(*procs)[1024], int *procs_len,
                          int fill_random);

#endif
