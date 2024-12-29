#ifndef _H_ALGORITHMS
#define _H_ALGORITHMS

#include "./proc.h"
#include "./queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GANT_LINE_COUNT 3
#define PROC_GANT_CHART_MAX 2048

int realloc_algo_gant_chart(char **stats, int *max);
int add_char_to_algo_gant_chart(char c, char **stats, int *len, int *max);
int add_str_to_algo_gant_chart(char *str, char **stats, int *len, int *max);
int add_number_to_algo_gant_chart(int i, char **stats, int *len, int *max);

int print_gant_proc_section(char **procs_section, int *procs_len,
                            int *procs_max, int pid, int bt, int ctx_time,
                            int line_count);

int print_gant_line_section(char **lines_section, int *lines_len,
                            int *lines_max, int bt, int ctx_time,
                            int line_count);

int print_gant_time_section(char **time_section, int *time_len, int *time_max,
                            int time, int bt, int ctx_time, int line_count);

int print_gant_section(char **procs_section, int *procs_len, int *procs_max,
                       char **lines_section, int *lines_len, int *lines_max,
                       char **time_section, int *time_len, int *time_max,
                       int pid, int time, int bt, int ctx_time);

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int rr(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int sjf(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int ljf(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int srjf(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int lrjf(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int ps(proc *procs[MAX_PROC], int procs_len, int ctx_time);
int hrrn(proc *procs[MAX_PROC], int procs_len, int ctx_time);

#endif
