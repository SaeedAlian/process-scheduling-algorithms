#include "../include/algorithms.h"

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time) {
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

  int gant_chart_procs_max = PROC_GANT_CHART_MAX;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = PROC_GANT_CHART_MAX;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_atqueue(atq);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int gant_chart_time_max = PROC_GANT_CHART_MAX;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_atqueue(atq);
    free(gant_chart_procs);
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
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    ctx_switch_count++;

    int wt;

    if (i == 0) {
      int wt = 0;
    } else {
      proc prev = clone_procs[i - 1];
      int wt = prev.wt + prev.bt + prev.at - top.at + ctx_time;
    }

    int rt = wt;
    int tt = wt + top.bt;

    if (!add_proc_wt(&top, wt) || !add_proc_rt(&top, rt) ||
        !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
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

    if (!print_gant_section(
            &gant_chart_procs, &gant_chart_procs_len, &gant_chart_procs_max,
            &gant_chart_lines, &gant_chart_lines_len, &gant_chart_lines_max,
            &gant_chart_time, &gant_chart_time_len, &gant_chart_time_max,
            top.pid, time, top.bt, ctx_time)) {
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in fcfs algorithm\n");
      return 0;
    }
  }

  printf("%s\n", gant_chart_procs);
  printf("%s\n", gant_chart_lines);
  printf("%s\n", gant_chart_time);

  free_atqueue(atq);

  return 0;
}

int print_gant_section(char **procs_section, int *procs_len, int *procs_max,
                       char **lines_section, int *lines_len, int *lines_max,
                       char **time_section, int *time_len, int *time_max,
                       int pid, int time, int bt, int ctx_time) {
  int line_count = GANT_LINE_COUNT;
  if (!print_gant_proc_section(procs_section, procs_len, procs_max, pid, bt,
                               ctx_time, line_count))
    return 0;

  if (!print_gant_line_section(lines_section, lines_len, lines_max, bt,
                               ctx_time, line_count))
    return 0;

  if (!print_gant_time_section(time_section, time_len, time_max, time, bt,
                               ctx_time, line_count))
    return 0;

  return 1;
}

int print_gant_proc_section(char **procs_section, int *procs_len,
                            int *procs_max, int pid, int bt, int ctx_time,
                            int line_count) {
  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  char pname[32];
  if (sprintf(pname, "%d", pid) < 0) {
    return 0;
  }

  int add_char_res =
      add_str_to_algo_gant_chart(pname, procs_section, procs_len, procs_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines; i++) {
    add_char_res =
        add_char_to_algo_gant_chart(' ', procs_section, procs_len, procs_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  add_char_res = 0;

  return 1;
}

int print_gant_line_section(char **lines_section, int *lines_len,
                            int *lines_max, int bt, int ctx_time,
                            int line_count) {
  int add_char_res =
      add_char_to_algo_gant_chart('|', lines_section, lines_len, lines_max);

  for (int i = 0; i < bt; i++) {
    for (int j = 0; j < line_count; j++) {
      add_char_res +=
          add_char_to_algo_gant_chart('-', lines_section, lines_len, lines_max);
    }
  }

  add_char_res +=
      add_char_to_algo_gant_chart('|', lines_section, lines_len, lines_max);

  for (int i = 0; i < ctx_time; i++) {
    for (int j = 0; j < line_count; j++) {
      add_char_res +=
          add_char_to_algo_gant_chart('*', lines_section, lines_len, lines_max);
    }
  }

  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  if (add_char_res != total_lines) {
    return 0;
  }

  return 1;
}

int print_gant_time_section(char **time_section, int *time_len, int *time_max,
                            int time, int bt, int ctx_time, int line_count) {
  int total_lines = (ctx_time * line_count) + (bt * line_count) + 2;

  int add_char_res = add_number_to_algo_gant_chart(
      time - bt - ctx_time, time_section, time_len, time_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines - (ctx_time * line_count) - 1;
       i++) {
    add_char_res =
        add_char_to_algo_gant_chart(' ', time_section, time_len, time_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  add_char_res = add_number_to_algo_gant_chart(time - ctx_time, time_section,
                                               time_len, time_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < (ctx_time * 3) + 1; i++) {
    add_char_res =
        add_char_to_algo_gant_chart(' ', time_section, time_len, time_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  return 1;
}

int add_number_to_algo_gant_chart(int i, char **stats, int *len, int *max) {
  char str[2048];
  if (sprintf(str, "%d", i) < 0)
    return 0;

  int l = strlen(str);
  int char_added = 0;

  for (int i = 0; i < l; i++) {
    if (!add_char_to_algo_gant_chart(str[i], stats, len, max))
      return 0;

    char_added++;
  }

  return char_added;
}

int add_str_to_algo_gant_chart(char *str, char **stats, int *len, int *max) {
  if (str == NULL)
    return 0;

  int l = strlen(str);
  if (l == 0)
    return 0;

  int char_added = 0;

  for (int i = 0; i < l; i++) {
    if (!add_char_to_algo_gant_chart(str[i], stats, len, max))
      return 0;

    char_added++;
  }

  return char_added;
}

int add_char_to_algo_gant_chart(char c, char **stats, int *len, int *max) {
  if ((*len) >= (*max) - 1) {
    if (!realloc_algo_gant_chart(stats, max)) {
      return 0;
    }
  }

  (*stats)[(*len)++] = c;
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