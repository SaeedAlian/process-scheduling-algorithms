#ifndef _H_ALGORITHMS
#define _H_ALGORITHMS

#include "./proc.h"
#include "./queue.h"
#include "./util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GANT_LINE_COUNT 5
#define ALGO_INFO_SECTION_SIZE 2048
#define MAX_ALGO_INFO_FILESIZE 2048 * 6

typedef int (*algo_func)(proc *procs[MAX_PROC], int procs_len, int ctx_time,
                         char **output_info, int *output_info_len,
                         int *output_info_max);

int set_algo_info(char **algo_info, int *algo_info_len, int *algo_info_max,
                  char *algo_name, char *gant_chart_procs,
                  char *gant_chart_lines, char *gant_chart_time,
                  char *proc_table, double wt_avg, double rt_avg, double tt_avg,
                  int ctx_time, int ctx_switch_count, int totaltime);

int set_proc_table(char **info, int *len, int *max, proc *procs, int procs_len);

int realloc_str(char **stats, int *max);
int append_char_to_str(char c, char **str, int *len, int *max);
int append_str_to_str(char *s, char **str, int *len, int *max);
int append_num_to_str(int i, char **str, int *len, int *max);
int append_decimal_to_str(double i, char **str, int *len, int *max);

int draw_gant_proc(char **procs_section, int *procs_len, int *procs_max,
                   int pid, int burst, int line_count);

int draw_gant_line(char **lines_section, int *lines_section_len,
                   int *lines_section_max, int burst, int is_ctx,
                   int line_count);

int draw_gant_time(char **time_section, int *time_section_len,
                   int *time_section_max, int current_time, int burst,
                   int line_count);

int draw_gant(char **procs_section, int *procs_len, int *procs_max,
              char **lines_section, int *lines_len, int *lines_max,
              char **time_section, int *time_len, int *time_max, int pid,
              int current_time, int burst, int line_count);

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max);
int rr(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max);
int sjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max);
int ljf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max);
int srjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max);
int lrjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max);
int ps(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max);
int hrrn(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max);

int run_algo(const char *algo_name, char *dirname, algo_func func,
             proc *procs[MAX_PROC], int procs_len, int ctx_time);

#endif
