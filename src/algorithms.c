#include "../include/algorithms.h"

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max) {
  if (output_info == NULL || output_info_len == NULL ||
      output_info_max == NULL) {
    fprintf(stderr, "Error: the output info string is empty\n");
    return 0;
  }

  int i = 0;
  proc clone_procs[procs_len];

  atqueue *atq = new_atqueue(procs_len, DESC);

  if (atq == NULL) {
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;

  while (!atqueue_is_empty(atq) && i < procs_len) {
    if (!at_dequeue(atq, &top)) {
      free_atqueue(atq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    ctx_switch_count++;

    int wt;

    if (i == 0) {
      wt = 0;
      time = top.at;
    } else {
      if (time <= top.at) {
        wt = 0;
        time = top.at;
      } else {
        proc prev = clone_procs[i - 1];
        wt = prev.wt + prev.bt + prev.at - top.at + ctx_time;
      }
    }

    int rt = wt;
    int tt = wt + top.bt;

    if (!add_proc_wt(&top, wt) || !add_proc_rt(&top, rt) ||
        !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into"
                      "processes\n");
      return 0;
    }

    time += top.bt + ctx_time;
    wt_sum += wt;
    tt_sum += tt;
    rt_sum += rt;

    clone_procs[i++] = top;

    if (!set_gant_section(
            &gant_chart_procs, &gant_chart_procs_len, &gant_chart_procs_max,
            &gant_chart_lines, &gant_chart_lines_len, &gant_chart_lines_max,
            &gant_chart_time, &gant_chart_time_len, &gant_chart_time_max,
            top.pid, time, top.bt, ctx_time)) {
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in fcfs algorithm\n");
      return 0;
    }
  }

  if (!set_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                      clone_procs, procs_len)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the process table in fcfs algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in fcfs algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in fcfs algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!set_algo_info(output_info, output_info_len, output_info_max,
                     (char *)"FCFS", gant_chart_procs, gant_chart_lines,
                     gant_chart_time, proc_table, wt_avg, rt_avg, tt_avg,
                     ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in fcfs algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free(proc_table);
  free(gant_chart_lines);
  free(gant_chart_procs);
  free(gant_chart_time);

  return 1;
}

int rr(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max) {
  return 0;
}

int sjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max) {
  return 0;
}

int ljf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max) {
  return 0;
}

int srjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max) {
  return 0;
}

int lrjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max) {
  return 0;
}

int ps(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max) {
  return 0;
}

int hrrn(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max) {
  return 0;
}

int set_algo_info(char **algo_info, int *algo_info_len, int *algo_info_max,
                  char *algo_name, char *gant_chart_procs,
                  char *gant_chart_lines, char *gant_chart_time,
                  char *proc_table, double wt_avg, double rt_avg, double tt_avg,
                  int ctx_switch_count, int totaltime) {
  if (!append_str_to_str((char *)"-->>", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str(algo_name, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"<<--", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n\nGant Chart:\n\n", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"PID\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"|\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"▼\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str(gant_chart_procs, algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str(gant_chart_lines, algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str(gant_chart_time, algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"▲\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"|\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"TIME\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"Legend:\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"--- : process is running\n", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"*** : context switch is running\n", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\nProcess Table:\n\n", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str(proc_table, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"* Waiting Time Avg: ", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_decimal_to_str(wt_avg, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"* Response Time Avg: ", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_decimal_to_str(rt_avg, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"* Turnaround Time Avg: ", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_decimal_to_str(tt_avg, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"* Context Switch Count: ", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_num_to_str(ctx_switch_count, algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"* Total Time: ", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  if (!append_num_to_str(totaltime, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  for (int i = 0; i < 200; i++) {
    if (!append_char_to_str('-', algo_info, algo_info_len, algo_info_max)) {
      return 0;
    }
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  return 1;
}

int set_proc_table(char **info, int *len, int *max, proc *procs,
                   int procs_len) {
  int add_char_res = append_str_to_str((char *)"   ", info, len, max);

  int margin = 15;

  add_char_res += append_str_to_str((char *)"PID", info, len, max);

  for (int i = 3; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", info, len, max);
  }

  add_char_res += append_str_to_str((char *)"AT", info, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", info, len, max);
  }

  add_char_res += append_str_to_str((char *)"BT", info, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", info, len, max);
  }

  add_char_res += append_str_to_str((char *)"WT", info, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", info, len, max);
  }

  add_char_res += append_str_to_str((char *)"RT", info, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", info, len, max);
  }

  add_char_res += append_str_to_str((char *)"TT", info, len, max);

  add_char_res += append_str_to_str((char *)"\n", info, len, max);
  add_char_res += append_str_to_str((char *)"   ", info, len, max);

  if (add_char_res != 20 + (margin - 2) * 4 + margin - 3) {
    return 0;
  }
  add_char_res = 0;
  int second_add_char_res = 0;
  int expected_second_add_char_res = 0;

  char formatted_str[256];
  int formatted_str_len = 0;

  for (int i = 0; i < procs_len; i++) {
    proc p = procs[i];

    if (sprintf(formatted_str, "%d", p.pid) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", info, len, max);
    }

    if (sprintf(formatted_str, "%d", p.at) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", info, len, max);
    }

    if (sprintf(formatted_str, "%d", p.bt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", info, len, max);
    }

    if (sprintf(formatted_str, "%d", p.wt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", info, len, max);
    }

    if (sprintf(formatted_str, "%d", p.rt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", info, len, max);
    }

    if (sprintf(formatted_str, "%d", p.tt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, info, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    second_add_char_res += append_str_to_str((char *)"\n", info, len, max);
    second_add_char_res += append_str_to_str((char *)"   ", info, len, max);

    if (second_add_char_res != expected_second_add_char_res + 4) {
      return 0;
    }

    second_add_char_res = 0;
    expected_second_add_char_res = 0;
  }

  return 1;
}

int set_gant_section(char **procs_section, int *procs_len, int *procs_max,
                     char **lines_section, int *lines_len, int *lines_max,
                     char **time_section, int *time_len, int *time_max, int pid,
                     int time, int bt, int ctx_time) {
  int line_count = GANT_LINE_COUNT;
  if (!set_gant_proc_section(procs_section, procs_len, procs_max, pid, bt,
                             ctx_time, line_count))
    return 0;

  if (!set_gant_line_section(lines_section, lines_len, lines_max, bt, ctx_time,
                             line_count))
    return 0;

  if (!set_gant_time_section(time_section, time_len, time_max, time, bt,
                             ctx_time, line_count))
    return 0;

  return 1;
}

int set_gant_proc_section(char **procs_section, int *procs_len, int *procs_max,
                          int pid, int bt, int ctx_time, int line_count) {
  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  char pname[32];
  if (sprintf(pname, "%d", pid) < 0) {
    return 0;
  }

  int add_char_res =
      append_str_to_str(pname, procs_section, procs_len, procs_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines; i++) {
    add_char_res = append_char_to_str(' ', procs_section, procs_len, procs_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  add_char_res = 0;

  return 1;
}

int set_gant_line_section(char **lines_section, int *lines_len, int *lines_max,
                          int bt, int ctx_time, int line_count) {
  int add_char_res =
      append_char_to_str('|', lines_section, lines_len, lines_max);

  for (int i = 0; i < bt; i++) {
    for (int j = 0; j < line_count; j++) {
      add_char_res +=
          append_char_to_str('-', lines_section, lines_len, lines_max);
    }
  }

  add_char_res += append_char_to_str('|', lines_section, lines_len, lines_max);

  for (int i = 0; i < ctx_time; i++) {
    for (int j = 0; j < line_count; j++) {
      add_char_res +=
          append_char_to_str('*', lines_section, lines_len, lines_max);
    }
  }

  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  if (add_char_res != total_lines) {
    return 0;
  }

  return 1;
}

int set_gant_time_section(char **time_section, int *time_len, int *time_max,
                          int time, int bt, int ctx_time, int line_count) {
  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  int add_char_res =
      append_num_to_str(time - bt - ctx_time, time_section, time_len, time_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines - (ctx_time * line_count) - 1;
       i++) {
    add_char_res = append_char_to_str(' ', time_section, time_len, time_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  add_char_res =
      append_num_to_str(time - ctx_time, time_section, time_len, time_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < (ctx_time * 3) + 1; i++) {
    add_char_res = append_char_to_str(' ', time_section, time_len, time_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  return 1;
}

int append_num_to_str(int i, char **str, int *len, int *max) {
  char res[2048];
  if (sprintf(res, "%d", i) < 0)
    return 0;

  int l = strlen(res);
  int char_added = 0;

  for (int i = 0; i < l; i++) {
    if (!append_char_to_str(res[i], str, len, max))
      return 0;

    char_added++;
  }

  return char_added;
}

int append_decimal_to_str(double i, char **str, int *len, int *max) {
  char res[2048];
  if (sprintf(res, "%.3f", i) < 0)
    return 0;

  int l = strlen(res);
  int char_added = 0;

  for (int i = 0; i < l; i++) {
    if (!append_char_to_str(res[i], str, len, max))
      return 0;

    char_added++;
  }

  return char_added;
}

int append_str_to_str(char *s, char **str, int *len, int *max) {
  if (str == NULL)
    return 0;

  int l = strlen(s);
  if (l == 0)
    return 0;

  int char_added = 0;

  for (int i = 0; i < l; i++) {
    if (!append_char_to_str(s[i], str, len, max))
      return 0;

    char_added++;
  }

  return char_added;
}

int append_char_to_str(char c, char **str, int *len, int *max) {
  if ((*len) >= (*max) - 1) {
    if (!realloc_algo_gant_chart(str, max)) {
      return 0;
    }
  }

  (*str)[(*len)++] = c;
  return 1;
}

int realloc_algo_gant_chart(char **stats, int *max) {
  *max *= 2;
  char *temp = (char *)realloc(*stats, sizeof(char) * (*max));
  if (temp == NULL)
    return 0;
  *stats = temp;
  return 1;
}
