#ifndef _H_ARGS
#define _H_ARGS

#define MAX_ALGORITHMS 256

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum algorithms {
  FCFS = 1,
  PS = 2,
  SRJF = 3,
  LRJF = 4,
  RR = 5,
  SJF = 6,
  LJF = 7,
  HRRN = 8,
};

typedef struct {
  int *algorithms;
  int algorithms_len;
  int ctx_time;
  int quant;
  char *output_dir;
  char *input_file;
  int fill_random;
} arguments;

int *tokenize_algorithms(char *algorithms, int *length);
int validate_ctx_time(int ctx_time);
int validate_quant(int quant);

int parse_arguments(int argc, char *argv[], arguments *args);

#endif
