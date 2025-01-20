#ifndef _H_ALGORITHMS
#define _H_ALGORITHMS

#include "./proc.h"
#include "./queue.h"
#include "./util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GANT_LINE_COUNT 5
#define GANT_LINE_MAX_CHAR 160
#define ALGO_INFO_SECTION_SIZE 2048
#define MAX_ALGO_INFO_FILESIZE 2048 * 6

typedef int (*non_preemptive_algo_func)(proc *procs[MAX_PROC], int procs_len,
                                        int ctx_time, char **output_info,
                                        int *output_info_len,
                                        int *output_info_max,
                                        double *wt_avg_res, double *rt_avg_res,
                                        double *tt_avg_res, int *totaltime_res,
                                        int *ctx_switch_count_res);

typedef int (*preemptive_algo_func)(proc *procs[MAX_PROC], int procs_len,
                                    int ctx_time, char **output_info,
                                    int *output_info_len, int *output_info_max,
                                    int quant, double *wt_avg_res,
                                    double *rt_avg_res, double *tt_avg_res,
                                    int *totaltime_res,
                                    int *ctx_switch_count_res);

int draw_algo_info(char **algo_info, int *algo_info_len, int *algo_info_max,
                   char *algo_name, char *gant_chart, char *proc_table,
                   double wt_avg, double rt_avg, double tt_avg, int ctx_time,
                   int ctx_switch_count, int totaltime);

int draw_proc_table(char **table, int *len, int *max, proc *procs,
                    int procs_len);

int realloc_str(char **stats, int *max);
int append_char_to_str(char c, char **str, int *len, int *max);
int append_str_to_str(char *s, char **str, int *len, int *max);
int append_num_to_str(int i, char **str, int *len, int *max);
int append_decimal_to_str(double i, char **str, int *len, int *max);

int update_gant_chart(char **gant_chart, int *gant_chart_len,
                      int *gant_chart_max, char **procs_section,
                      int *procs_section_len, int *procs_section_max,
                      char **lines_section, int *lines_section_len,
                      int *lines_section_max, char **time_section,
                      int *time_section_len, int *time_section_max);

int line_break_gant(char **gant_chart, int *gant_chart_len, int *gant_chart_max,
                    char **procs_section, int *procs_section_len,
                    int *procs_section_max, char **lines_section,
                    int *lines_section_len, int *lines_section_max,
                    char **time_section, int *time_section_len,
                    int *time_section_max, int max_line_char);

int draw_gant_proc(char **procs_section, int *procs_section_len,
                   int *procs_section_max, int pid, int burst, int line_count);

int draw_gant_line(char **lines_section, int *lines_section_len,
                   int *lines_section_max, int burst, int is_ctx,
                   int line_count);

int draw_gant_time(char **time_section, int *time_section_len,
                   int *time_section_max, int current_time, int burst,
                   int line_count);

int draw_gant(char **gant_chart, int *gant_chart_len, int *gant_chart_max,
              char **procs_section, int *procs_section_len,
              int *procs_section_max, char **lines_section,
              int *lines_section_len, int *lines_section_max,
              char **time_section, int *time_section_len, int *time_section_max,
              int pid, int current_time, int burst, int line_count,
              int max_line_char);

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, double *wt_avg_res,
         double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
         int *ctx_switch_count_res);
int rr(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max, int quant,
       double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
       int *totaltime_res, int *ctx_switch_count_res);
int sjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max, double *wt_avg_res,
        double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
        int *ctx_switch_count_res);
int ljf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max, double *wt_avg_res,
        double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
        int *ctx_switch_count_res);
int srjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, int quant,
         double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
         int *totaltime_res, int *ctx_switch_count_res);
int lrjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, int quant,
         double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
         int *totaltime_res, int *ctx_switch_count_res);
int ps(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max, int quant,
       double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
       int *totaltime_res, int *ctx_switch_count_res);
int hrrn(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, double *wt_avg_res,
         double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
         int *ctx_switch_count_res);

int run_non_preemptive_algo(const char *algo_name, char *dirname,
                            non_preemptive_algo_func func,
                            proc *procs[MAX_PROC], int procs_len, int ctx_time,
                            double *wt_avg_res, double *rt_avg_res,
                            double *tt_avg_res, int *totaltime_res,
                            int *ctx_switch_count_res);

int run_preemptive_algo(const char *algo_name, char *dirname,
                        preemptive_algo_func func, proc *procs[MAX_PROC],
                        int procs_len, int ctx_time, int quant,
                        double *wt_avg_res, double *rt_avg_res,
                        double *tt_avg_res, int *totaltime_res,
                        int *ctx_switch_count_res);

#endif
