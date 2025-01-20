#include "../include/algorithms.h"

int run_non_preemptive_algo(const char *algo_name, char *dirname,
                            non_preemptive_algo_func func,
                            proc *procs[MAX_PROC], int procs_len, int ctx_time,
                            double *wt_avg_res, double *rt_avg_res,
                            double *tt_avg_res, int *totaltime_res,
                            int *ctx_switch_count_res) {
  int info_max = MAX_ALGO_INFO_FILESIZE;
  char *info = (char *)malloc(sizeof(char) * info_max);
  int info_len = 0;

  if (!func(procs, procs_len, ctx_time, &info, &info_len, &info_max, wt_avg_res,
            rt_avg_res, tt_avg_res, totaltime_res, ctx_switch_count_res)) {
    free(info);
    fprintf(stderr, "Error: something went wrong in running %s algorithm\n",
            algo_name);
    return 0;
  }

  char filename[1024];
  if (sprintf(filename, "%s/%s.txt", dirname, algo_name) < 0) {
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  FILE *file = create_file(filename);
  if (file == NULL) {
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  if (!append_str_to_file(file, info, info_len)) {
    fclose(file);
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  printf("%i --- %s Printed Successfully \n", info_len, algo_name);
  fclose(file);
  free(info);

  return 1;
}

int run_preemptive_algo(const char *algo_name, char *dirname,
                        preemptive_algo_func func, proc *procs[MAX_PROC],
                        int procs_len, int ctx_time, int quant,
                        double *wt_avg_res, double *rt_avg_res,
                        double *tt_avg_res, int *totaltime_res,
                        int *ctx_switch_count_res) {
  int info_max = MAX_ALGO_INFO_FILESIZE;
  char *info = (char *)malloc(sizeof(char) * info_max);
  int info_len = 0;

  if (!func(procs, procs_len, ctx_time, &info, &info_len, &info_max, quant,
            wt_avg_res, rt_avg_res, tt_avg_res, totaltime_res,
            ctx_switch_count_res)) {
    free(info);
    fprintf(stderr, "Error: something went wrong in running %s algorithm\n",
            algo_name);
    return 0;
  }

  char filename[1024];
  if (sprintf(filename, "%s/%s.txt", dirname, algo_name) < 0) {
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  FILE *file = create_file(filename);
  if (file == NULL) {
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  if (!append_str_to_file(file, info, info_len)) {
    fclose(file);
    free(info);
    fprintf(stderr,
            "Error: something went wrong in creating the output file\n");
    return 0;
  }

  printf("%i --- %s Printed Successfully \n", info_len, algo_name);
  fclose(file);
  free(info);

  return 1;
}

int fcfs(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, double *wt_avg_res,
         double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
         int *ctx_switch_count_res) {
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

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
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

    if (!increment_sbt(&top, top.bt) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if (!draw_gant(
            &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
            &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
            &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
            &gant_chart_time_len, &gant_chart_time_max, top.pid, time, top.bt,
            GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in fcfs algorithm\n");
      return 0;
    }

    if (i != procs_len - 1) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time + top.bt,
              ctx_time, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in fcfs algorithm\n");
        return 0;
      }
    }

    time += top.bt + ctx_time;
    wt_sum += wt;
    tt_sum += tt;
    rt_sum += rt;

    clone_procs[i++] = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
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

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in fcfs algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"FCFS", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
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
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int sjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max, double *wt_avg_res,
        double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
        int *ctx_switch_count_res) {
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

  btqueue *btq = new_btqueue(procs_len, DESC);

  if (btq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_btqueue(btq);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for sjf algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for sjf algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for sjf algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for sjf algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;

  while ((!atqueue_is_empty(atq) || !btqueue_is_empty(btq)) && i < procs_len) {
    if (btqueue_is_empty(btq)) {
      if (atqueue_is_empty(atq) && i < procs_len) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (top.at > time - ctx_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    if (btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    if (!bt_dequeue(btq, &top)) {
      free_atqueue(atq);
      free_btqueue(btq);
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

    if (!increment_sbt(&top, top.bt) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if (!draw_gant(
            &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
            &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
            &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
            &gant_chart_time_len, &gant_chart_time_max, top.pid, time, top.bt,
            GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in sjf algorithm\n");
      return 0;
    }

    if (i != procs_len - 1) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time + top.bt,
              ctx_time, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in sjf algorithm\n");
        return 0;
      }
    }

    time += top.bt + ctx_time;
    wt_sum += wt;
    tt_sum += tt;
    rt_sum += rt;

    clone_procs[i++] = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the process table in sjf algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in sjf algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in sjf algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in sjf algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"SJF", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in sjf algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free_btqueue(btq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int ljf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
        int *output_info_len, int *output_info_max, double *wt_avg_res,
        double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
        int *ctx_switch_count_res) {
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

  btqueue *btq = new_btqueue(procs_len, ASC);

  if (btq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_btqueue(btq);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for ljf algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for ljf algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for ljf algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for ljf algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;

  while ((!atqueue_is_empty(atq) || !btqueue_is_empty(btq)) && i < procs_len) {
    if (btqueue_is_empty(btq)) {
      if (atqueue_is_empty(atq) && i < procs_len) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (top.at > time - ctx_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    if (btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    if (!bt_dequeue(btq, &top)) {
      free_atqueue(atq);
      free_btqueue(btq);
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

    if (!increment_sbt(&top, top.bt) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if (!draw_gant(
            &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
            &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
            &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
            &gant_chart_time_len, &gant_chart_time_max, top.pid, time, top.bt,
            GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in ljf algorithm\n");
      return 0;
    }

    if (i != procs_len - 1) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time + top.bt,
              ctx_time, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in ljf algorithm\n");
        return 0;
      }
    }

    time += top.bt + ctx_time;
    wt_sum += wt;
    tt_sum += tt;
    rt_sum += rt;

    clone_procs[i++] = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the process table in ljf algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ljf algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ljf algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ljf algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"LJF", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in ljf algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free_btqueue(btq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int srjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, int quant,
         double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
         int *totaltime_res, int *ctx_switch_count_res) {
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

  btqueue *btq = new_btqueue(procs_len, DESC);

  if (btq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_btqueue(btq);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for srjf algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for srjf algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for srjf algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for srjf algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  int quant_count = 0;

  proc top;
  proc prev;
  prev.pid = -1;

  while (i < procs_len) {
    int arrived_immediately = 0;
    int has_ctx_switch = 0;

    if (atqueue_is_empty(atq) && btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (btqueue_is_empty(btq)) {
      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      arrived_immediately = 1;

      if (prev.pid != -1 && prev.pid != top.pid && top.at < time + ctx_time) {
        has_ctx_switch = 1;
      } else {
        time = top.at;
        has_ctx_switch = 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    proc top_bt;
    if (!peek_btqueue(btq, &top_bt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in peeking the queue\n");
      return 0;
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in peeking the queue\n");
        return 0;
      }

      int current_time =
          prev.pid != -1 && prev.pid != top.pid ? time + ctx_time : time;

      if (top.at > current_time - ctx_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    if (btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (!bt_dequeue(btq, &top)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    int proc_is_switched = prev.pid != -1 && prev.pid != top.pid;

    int bt_remaining = top.bt - top.sbt;
    int bt_increment = 1;
    quant_count += bt_increment;

    int updated_bt_remaining = bt_remaining - bt_increment;
    int is_finished_before_quant = 0;

    if (updated_bt_remaining <= 0) {
      bt_increment = bt_remaining;
      updated_bt_remaining = bt_remaining - bt_increment;
      is_finished_before_quant = 1;
    }

    int is_finished = is_finished_before_quant || bt_remaining <= 0;

    int wt;
    int tt;
    int rt = top.rt;

    if (prev.pid == -1) {
      wt = 0;
    } else {
      if (arrived_immediately) {
        if (has_ctx_switch) {
          wt = top.wt != -1 ? top.wt + time + ctx_time - top.at
                            : time + ctx_time - top.at;
        } else {
          wt = top.wt != -1 ? top.wt : 0;
        }
      } else {
        wt = (time - top.at) - top.sbt;

        if (proc_is_switched) {
          wt += ctx_time;
        }
      }
    }

    if (top.rt == -1) {
      rt = wt;
    }

    tt = wt + top.sbt + bt_increment;

    if (!increment_sbt(&top, bt_increment) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if ((arrived_immediately && has_ctx_switch) ||
        (!arrived_immediately && proc_is_switched)) {
      if (prev.sbt < prev.bt) {
        if (!draw_gant(&gant_chart, &gant_chart_len, &gant_chart_max,
                       &gant_chart_procs, &gant_chart_procs_len,
                       &gant_chart_procs_max, &gant_chart_lines,
                       &gant_chart_lines_len, &gant_chart_lines_max,
                       &gant_chart_time, &gant_chart_time_len,
                       &gant_chart_time_max, prev.pid, time - quant_count + 1,
                       quant_count, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
          free_atqueue(atq);
          free_btqueue(btq);
          free(proc_table);
          free(gant_chart_lines);
          free(gant_chart_procs);
          free(gant_chart_time);
          fprintf(stderr,
                  "Error: something went wrong in printing the gant chart "
                  "in srjf algorithm\n");
          return 0;
        }
      }

      quant_count = 1;

      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time, ctx_time,
              GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in srjf algorithm\n");
        return 0;
      }

      ctx_switch_count++;
      time += ctx_time;
    }

    time += bt_increment;

    if (quant_count == quant || is_finished_before_quant) {
      if (!is_finished || is_finished_before_quant) {
        if (!draw_gant(&gant_chart, &gant_chart_len, &gant_chart_max,
                       &gant_chart_procs, &gant_chart_procs_len,
                       &gant_chart_procs_max, &gant_chart_lines,
                       &gant_chart_lines_len, &gant_chart_lines_max,
                       &gant_chart_time, &gant_chart_time_len,
                       &gant_chart_time_max, top.pid, time - quant_count,
                       quant_count, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
          free_atqueue(atq);
          free_btqueue(btq);
          free(proc_table);
          free(gant_chart_lines);
          free(gant_chart_procs);
          free(gant_chart_time);
          fprintf(stderr,
                  "Error: something went wrong in printing the gant chart "
                  "in srjf algorithm\n");
          return 0;
        }

        quant_count = 0;
      }
    }

    if (is_finished) {
      wt_sum += wt;
      tt_sum += tt;
      rt_sum += rt;

      clone_procs[i++] = top;
    } else {
      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    prev = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the process table in srjf algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in srjf algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in srjf algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in srjf algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"SRJF", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in srjf algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free_btqueue(btq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int lrjf(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, int quant,
         double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
         int *totaltime_res, int *ctx_switch_count_res) {
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

  btqueue *btq = new_btqueue(procs_len, ASC);

  if (btq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_btqueue(btq);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for lrjf algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for lrjf algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for lrjf algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for lrjf algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_btqueue(btq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;
  proc prev;
  prev.pid = -1;

  while (i < procs_len) {
    int arrived_immediately = 0;
    int has_ctx_switch = 0;

    if (atqueue_is_empty(atq) && btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (btqueue_is_empty(btq)) {
      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      arrived_immediately = 1;

      if (prev.pid != -1 && prev.pid != top.pid && top.at < time + ctx_time) {
        has_ctx_switch = 1;
      } else {
        time = top.at;
        has_ctx_switch = 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    proc top_bt;
    if (!peek_btqueue(btq, &top_bt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in peeking the queue\n");
      return 0;
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in peeking the queue\n");
        return 0;
      }

      int current_time =
          prev.pid != -1 && prev.pid != top.pid ? time + ctx_time : time;

      if (top.at > current_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    if (btqueue_is_empty(btq)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (!bt_dequeue(btq, &top)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    int proc_is_switched = prev.pid != -1 && prev.pid != top.pid;

    int bt_remaining = top.bt - top.sbt;
    int bt_increment = quant;
    int updated_bt_remaining = bt_remaining - bt_increment;
    int is_finished_before_quant = 0;

    if (updated_bt_remaining <= 0) {
      bt_increment = bt_remaining;
      updated_bt_remaining = bt_remaining - bt_increment;
      is_finished_before_quant = 1;
    }

    int is_finished = is_finished_before_quant || bt_remaining <= 0;

    int wt;
    int tt;
    int rt = top.rt;

    if (prev.pid == -1) {
      wt = 0;
    } else {
      if (arrived_immediately) {
        if (has_ctx_switch) {
          wt = top.wt != -1 ? top.wt + time + ctx_time - top.at
                            : time + ctx_time - top.at;
        } else {
          wt = top.wt != -1 ? top.wt : 0;
        }
      } else {
        wt = (time - top.at) - top.sbt;

        if (proc_is_switched) {
          wt += ctx_time;
        }
      }
    }

    if (top.rt == -1) {
      rt = wt;
    }

    tt = wt + top.sbt + bt_increment;

    if (!increment_sbt(&top, bt_increment) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free_btqueue(btq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if ((arrived_immediately && has_ctx_switch) ||
        (!arrived_immediately && proc_is_switched)) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time, ctx_time,
              GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in lrjf algorithm\n");
        return 0;
      }

      ctx_switch_count++;
      time += ctx_time;
    }

    if (!is_finished || is_finished_before_quant) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, top.pid, time,
              bt_increment, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in lrjf algorithm\n");
        return 0;
      }
    }

    time += bt_increment;

    if (is_finished) {
      wt_sum += wt;
      tt_sum += tt;
      rt_sum += rt;

      clone_procs[i++] = top;
    } else {
      if (!bt_enqueue(btq, top)) {
        free_atqueue(atq);
        free_btqueue(btq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    prev = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the process table in lrjf algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in lrjf algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free_btqueue(btq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in lrjf algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in lrjf algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"LRJF", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in lrjf algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free_btqueue(btq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int hrrn(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
         int *output_info_len, int *output_info_max, double *wt_avg_res,
         double *rt_avg_res, double *tt_avg_res, int *totaltime_res,
         int *ctx_switch_count_res) {
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

  rrqueue *rrq = new_rrqueue(procs_len, ASC);

  if (rrq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_atqueue(atq);
      free_rrqueue(rrq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    fprintf(stderr, "Error: cannot create the gant chart for hrrn algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for hrrn algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for hrrn algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_atqueue(atq);
    free(gant_chart_procs);
    free_rrqueue(rrq);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for hrrn algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_rrqueue(rrq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;

  while (i < procs_len) {
    if (atqueue_is_empty(atq) && rrqueue_is_empty(rrq)) {
      free_atqueue(atq);
      free_rrqueue(rrq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (rrqueue_is_empty(rrq)) {
      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      time = top.at;

      if (!rr_enqueue(rrq, top)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    if (rrqueue_is_empty(rrq)) {
      free_atqueue(atq);
      free_rrqueue(rrq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (!rr_dequeue(rrq, &top)) {
      free_atqueue(atq);
      free_rrqueue(rrq);
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

    if (!increment_sbt(&top, top.bt) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_atqueue(atq);
      free_rrqueue(rrq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if (!draw_gant(
            &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
            &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
            &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
            &gant_chart_time_len, &gant_chart_time_max, top.pid, time, top.bt,
            GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
      free_atqueue(atq);
      free_rrqueue(rrq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in printing the gant chart "
                      "in hrrn algorithm\n");
      return 0;
    }

    if (i != procs_len - 1) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time + top.bt,
              ctx_time, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in hrrn algorithm\n");
        return 0;
      }
    }

    time += top.bt + ctx_time;
    wt_sum += wt;
    tt_sum += tt;
    rt_sum += rt;

    clone_procs[i++] = top;

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in peeking the queue\n");
        return 0;
      }

      if (top.at > time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      int wt = time - top.at;

      if (!add_proc_wt(&top, wt)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in adding stats into "
                        "processes\n");
        return 0;
      }

      if (!rr_enqueue(rrq, top)) {
        free_atqueue(atq);
        free_rrqueue(rrq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the process table in hrrn algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in hrrn algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_atqueue(atq);
    free_rrqueue(rrq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in hrrn algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in hrrn algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"HRRN", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr,
            "Error: couldn't set the algorithm info in hrrn algorithm\n");
    return 0;
  }

  free_atqueue(atq);
  free_rrqueue(rrq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int ps(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max, int quant,
       double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
       int *totaltime_res, int *ctx_switch_count_res) {
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

  pqueue *pq = new_pqueue(procs_len, ASC);

  if (pq == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_pqueue(pq);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_pqueue(pq);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for ps algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for ps algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for ps algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for ps algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;
  proc prev;
  prev.pid = -1;

  while (i < procs_len) {
    int arrived_immediately = 0;
    int has_ctx_switch = 0;

    if (atqueue_is_empty(atq) && pqueue_is_empty(pq)) {
      free_atqueue(atq);
      free_pqueue(pq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (pqueue_is_empty(pq)) {
      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      arrived_immediately = 1;

      if (prev.pid != -1 && prev.pid != top.pid && top.at < time + ctx_time) {
        has_ctx_switch = 1;
      } else {
        time = top.at;
        has_ctx_switch = 0;
      }

      if (!p_enqueue(pq, top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    proc top_bt;
    if (!peek_pqueue(pq, &top_bt)) {
      free_atqueue(atq);
      free_pqueue(pq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in peeking the queue\n");
      return 0;
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in peeking the queue\n");
        return 0;
      }

      int current_time =
          prev.pid != -1 && prev.pid != top.pid ? time + ctx_time : time;

      if (top.at > current_time - ctx_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!p_enqueue(pq, top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    if (pqueue_is_empty(pq)) {
      free_atqueue(atq);
      free_pqueue(pq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (!p_dequeue(pq, &top)) {
      free_atqueue(atq);
      free_pqueue(pq);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    int proc_is_switched = prev.pid != -1 && prev.pid != top.pid;

    int bt_remaining = top.bt - top.sbt;
    int bt_increment = quant;
    int updated_bt_remaining = bt_remaining - bt_increment;
    int is_finished_before_quant = 0;

    if (updated_bt_remaining <= 0) {
      bt_increment = bt_remaining;
      updated_bt_remaining = bt_remaining - bt_increment;
      is_finished_before_quant = 1;
    }

    int is_finished = is_finished_before_quant || bt_remaining <= 0;

    int wt;
    int tt;
    int rt = top.rt;

    if (prev.pid == -1) {
      wt = 0;
    } else {
      if (arrived_immediately) {
        if (has_ctx_switch) {
          wt = top.wt != -1 ? top.wt + time + ctx_time - top.at
                            : time + ctx_time - top.at;
        } else {
          wt = top.wt != -1 ? top.wt : 0;
        }
      } else {
        wt = (time - top.at) - top.sbt;

        if (proc_is_switched) {
          wt += ctx_time;
        }
      }
    }

    if (top.rt == -1) {
      rt = wt;
    }

    tt = wt + top.sbt + bt_increment;

    if (!increment_sbt(&top, bt_increment) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_pqueue(pq);
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if ((arrived_immediately && has_ctx_switch) ||
        (!arrived_immediately && proc_is_switched)) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time, ctx_time,
              GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_pqueue(pq);
        free_atqueue(atq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in ps algorithm\n");
        return 0;
      }

      ctx_switch_count++;
      time += ctx_time;
    }

    if (!is_finished || is_finished_before_quant) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, top.pid, time,
              bt_increment, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_pqueue(pq);
        free_atqueue(atq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in ps algorithm\n");
        return 0;
      }
    }

    time += bt_increment;

    if (is_finished) {
      wt_sum += wt;
      tt_sum += tt;
      rt_sum += rt;

      clone_procs[i++] = top;
    } else {
      if (!p_enqueue(pq, top)) {
        free_atqueue(atq);
        free_pqueue(pq);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    prev = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the process table in ps algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ps algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_pqueue(pq);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ps algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in ps algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"PS", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the algorithm info in ps algorithm\n");
    return 0;
  }

  free_pqueue(pq);
  free_atqueue(atq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int rr(proc *procs[MAX_PROC], int procs_len, int ctx_time, char **output_info,
       int *output_info_len, int *output_info_max, int quant,
       double *wt_avg_res, double *rt_avg_res, double *tt_avg_res,
       int *totaltime_res, int *ctx_switch_count_res) {
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

  queue *q = new_queue(procs_len);

  if (q == NULL) {
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot put processes into queue\n");
    return 0;
  }

  for (int i = 0; i < procs_len; i++) {
    if (!at_enqueue(atq, *(procs[i]))) {
      free_queue(q);
      free_atqueue(atq);
      fprintf(stderr, "Error: cannot put processes into queue\n");
      return 0;
    }
  }

  int proc_table_max = ALGO_INFO_SECTION_SIZE;
  int proc_table_len = 0;
  char *proc_table = (char *)malloc(sizeof(char) * proc_table_max);

  if (proc_table == NULL) {
    free_queue(q);
    free_atqueue(atq);
    fprintf(stderr, "Error: cannot create the gant chart for rr algorithm\n");
    return 0;
  }

  int gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_procs_len = 0;
  char *gant_chart_procs = (char *)malloc(sizeof(char) * gant_chart_procs_max);

  if (gant_chart_procs == NULL) {
    free_queue(q);
    free_atqueue(atq);
    free(proc_table);
    fprintf(stderr, "Error: cannot create the gant chart for rr algorithm\n");
    return 0;
  }

  int gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_lines_len = 0;
  char *gant_chart_lines = (char *)malloc(sizeof(char) * gant_chart_lines_max);

  if (gant_chart_lines == NULL) {
    free_queue(q);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_procs);
    fprintf(stderr, "Error: cannot create the gant chart for rr algorithm\n");
    return 0;
  }

  int gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_time_len = 0;
  char *gant_chart_time = (char *)malloc(sizeof(char) * gant_chart_time_max);

  if (gant_chart_time == NULL) {
    free_queue(q);
    free_atqueue(atq);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_lines);
    fprintf(stderr, "Error: cannot create the gant chart for rr algorithm\n");
    return 0;
  }

  int gant_chart_max = ALGO_INFO_SECTION_SIZE;
  int gant_chart_len = 0;
  char *gant_chart = (char *)malloc(sizeof(char) * gant_chart_max);

  if (gant_chart == NULL) {
    free_queue(q);
    free_atqueue(atq);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(proc_table);
    free(gant_chart_time);
    fprintf(stderr, "Error: cannot create the gant chart for fcfs algorithm\n");
    return 0;
  }

  int time = 0;
  int ctx_switch_count = 0;
  int wt_sum = 0;
  int rt_sum = 0;
  int tt_sum = 0;

  proc top;
  proc prev;
  prev.pid = -1;

  while (i < procs_len) {
    int arrived_immediately = 0;
    int has_ctx_switch = 0;

    if (atqueue_is_empty(atq) && queue_is_empty(q)) {
      free_atqueue(atq);
      free_queue(q);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (queue_is_empty(q)) {
      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      arrived_immediately = 1;

      if (prev.pid != -1 && prev.pid != top.pid && top.at < time + ctx_time) {
        has_ctx_switch = 1;
      } else {
        time = top.at;
        has_ctx_switch = 0;
      }

      if (!enqueue(q, top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    proc top_bt;
    if (!peek_queue(q, &top_bt)) {
      free_atqueue(atq);
      free_queue(q);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in peeking the queue\n");
      return 0;
    }

    while (!atqueue_is_empty(atq)) {
      if (!peek_atqueue(atq, &top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in peeking the queue\n");
        return 0;
      }

      int current_time =
          prev.pid != -1 && prev.pid != top.pid ? time + ctx_time : time;

      if (top.at > current_time)
        break;

      if (!at_dequeue(atq, &top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }

      if (!enqueue(q, top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in enqueuing\n");
        return 0;
      }
    }

    if (queue_is_empty(q)) {
      free_atqueue(atq);
      free_queue(q);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in enqueuing\n");
      return 0;
    }

    if (!dequeue(q, &top)) {
      free_atqueue(atq);
      free_queue(q);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(proc_table);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in dequeuing\n");
      return 0;
    }

    int proc_is_switched = prev.pid != -1 && prev.pid != top.pid;

    int bt_remaining = top.bt - top.sbt;
    int bt_increment = quant;
    int updated_bt_remaining = bt_remaining - bt_increment;
    int is_finished_before_quant = 0;

    if (updated_bt_remaining <= 0) {
      bt_increment = bt_remaining;
      updated_bt_remaining = bt_remaining - bt_increment;
      is_finished_before_quant = 1;
    }

    int is_finished = is_finished_before_quant || bt_remaining <= 0;

    int wt;
    int tt;
    int rt = top.rt;

    if (prev.pid == -1) {
      wt = 0;
    } else {
      if (arrived_immediately) {
        if (has_ctx_switch) {
          wt = top.wt != -1 ? top.wt + time + ctx_time - top.at
                            : time + ctx_time - top.at;
        } else {
          wt = top.wt != -1 ? top.wt : 0;
        }
      } else {
        wt = (time - top.at) - top.sbt;

        if (proc_is_switched) {
          wt += ctx_time;
        }
      }
    }

    if (top.rt == -1) {
      rt = wt;
    }

    tt = wt + top.sbt + bt_increment;

    if (!increment_sbt(&top, bt_increment) || !add_proc_wt(&top, wt) ||
        !add_proc_rt(&top, rt) || !add_proc_tt(&top, tt)) {
      free_queue(q);
      free_atqueue(atq);
      free(proc_table);
      free(gant_chart_lines);
      free(gant_chart_procs);
      free(gant_chart_time);
      fprintf(stderr, "Error: something went wrong in adding stats into "
                      "processes\n");
      return 0;
    }

    if ((arrived_immediately && has_ctx_switch) ||
        (!arrived_immediately && proc_is_switched)) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, -1, time, ctx_time,
              GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_queue(q);
        free_atqueue(atq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in rr algorithm\n");
        return 0;
      }

      ctx_switch_count++;
      time += ctx_time;
    }

    if (!is_finished || is_finished_before_quant) {
      if (!draw_gant(
              &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
              &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
              &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
              &gant_chart_time_len, &gant_chart_time_max, top.pid, time,
              bt_increment, GANT_LINE_COUNT, GANT_LINE_MAX_CHAR)) {
        free_queue(q);
        free_atqueue(atq);
        free(proc_table);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(gant_chart_time);
        fprintf(stderr,
                "Error: something went wrong in printing the gant chart "
                "in rr algorithm\n");
        return 0;
      }
    }

    time += bt_increment;

    if (is_finished) {
      wt_sum += wt;
      tt_sum += tt;
      rt_sum += rt;

      clone_procs[i++] = top;
    } else {
      if (!enqueue(q, top)) {
        free_atqueue(atq);
        free_queue(q);
        free(gant_chart_lines);
        free(gant_chart_procs);
        free(proc_table);
        free(gant_chart_time);
        fprintf(stderr, "Error: something went wrong in dequeuing\n");
        return 0;
      }
    }

    prev = top;
  }

  if (!draw_proc_table(&proc_table, &proc_table_len, &proc_table_max,
                       clone_procs, procs_len)) {
    free_queue(q);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the process table in rr algorithm\n");
    return 0;
  }

  if (!append_char_to_str('|', &gant_chart_lines, &gant_chart_lines_len,
                          &gant_chart_lines_max)) {
    free_queue(q);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in rr algorithm\n");
    return 0;
  }

  if (!append_num_to_str(time, &gant_chart_time, &gant_chart_time_len,
                         &gant_chart_time_max)) {
    free_queue(q);
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in rr algorithm\n");
    return 0;
  }

  double wt_avg = (double)wt_sum / procs_len;
  double rt_avg = (double)rt_sum / procs_len;
  double tt_avg = (double)tt_sum / procs_len;

  if (!update_gant_chart(
          &gant_chart, &gant_chart_len, &gant_chart_max, &gant_chart_procs,
          &gant_chart_procs_len, &gant_chart_procs_max, &gant_chart_lines,
          &gant_chart_lines_len, &gant_chart_lines_max, &gant_chart_time,
          &gant_chart_time_len, &gant_chart_time_max)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: something went wrong in printing the gant chart "
                    "in rr algorithm\n");
    return 0;
  }

  if (!draw_algo_info(output_info, output_info_len, output_info_max,
                      (char *)"RR", gant_chart, proc_table, wt_avg, rt_avg,
                      tt_avg, ctx_time, ctx_switch_count, time)) {
    free_atqueue(atq);
    free(proc_table);
    free(gant_chart_lines);
    free(gant_chart_procs);
    free(gant_chart_time);
    fprintf(stderr, "Error: couldn't set the algorithm info in rr algorithm\n");
    return 0;
  }

  free_queue(q);
  free_atqueue(atq);
  free(proc_table);
  free(gant_chart);

  *wt_avg_res = wt_avg;
  *rt_avg_res = rt_avg;
  *tt_avg_res = tt_avg;
  *totaltime_res = time;
  *ctx_switch_count_res = ctx_switch_count;

  return 1;
}

int draw_algo_info(char **algo_info, int *algo_info_len, int *algo_info_max,
                   char *algo_name, char *gant_chart, char *proc_table,
                   double wt_avg, double rt_avg, double tt_avg, int ctx_time,
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

  if (!append_str_to_str(gant_chart, algo_info, algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"\n\n", algo_info, algo_info_len,
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

  if (!append_str_to_str((char *)"Top numbers : PID\n", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_str_to_str((char *)"Bottom numbers : TIME\n", algo_info,
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

  if (!append_str_to_str((char *)"* Context Switch Time: ", algo_info,
                         algo_info_len, algo_info_max)) {
    return 0;
  }

  if (!append_num_to_str(ctx_switch_count * ctx_time, algo_info, algo_info_len,
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

  for (int i = 0; i < 300; i++) {
    if (!append_char_to_str('-', algo_info, algo_info_len, algo_info_max)) {
      return 0;
    }
  }

  if (!append_str_to_str((char *)"\n", algo_info, algo_info_len,
                         algo_info_max)) {
    return 0;
  }

  (*algo_info)[(*algo_info_len)] = '\0';

  return 1;
}

int draw_proc_table(char **table, int *len, int *max, proc *procs,
                    int procs_len) {
  int add_char_res = append_str_to_str((char *)"   ", table, len, max);

  int margin = 15;

  add_char_res += append_str_to_str((char *)"PID", table, len, max);

  for (int i = 3; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"PRI", table, len, max);

  for (int i = 3; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"AT", table, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"BT", table, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"WT", table, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"RT", table, len, max);

  for (int i = 2; i < margin; i++) {
    add_char_res += append_str_to_str((char *)" ", table, len, max);
  }

  add_char_res += append_str_to_str((char *)"TT", table, len, max);

  add_char_res += append_str_to_str((char *)"\n", table, len, max);
  add_char_res += append_str_to_str((char *)"   ", table, len, max);

  if (add_char_res != 23 + (margin - 2) * 4 + (margin - 3) * 2) {
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

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.pri) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.at) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.bt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.wt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.rt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += margin - formatted_str_len;
    for (int i = formatted_str_len; i < margin; i++) {
      second_add_char_res += append_str_to_str((char *)" ", table, len, max);
    }

    if (sprintf(formatted_str, "%d", p.tt) < 0) {
      return 0;
    }

    add_char_res = append_str_to_str(formatted_str, table, len, max);
    if (add_char_res == 0) {
      return 0;
    }

    second_add_char_res += append_str_to_str((char *)"\n", table, len, max);
    second_add_char_res += append_str_to_str((char *)"   ", table, len, max);

    if (second_add_char_res != expected_second_add_char_res + 4) {
      return 0;
    }

    second_add_char_res = 0;
    expected_second_add_char_res = 0;
  }

  (*table)[(*len)] = '\0';

  return 1;
}

int update_gant_chart(char **gant_chart, int *gant_chart_len,
                      int *gant_chart_max, char **procs_section,
                      int *procs_section_len, int *procs_section_max,
                      char **lines_section, int *lines_section_len,
                      int *lines_section_max, char **time_section,
                      int *time_section_len, int *time_section_max) {
  if (!append_str_to_str(*procs_section, gant_chart, gant_chart_len,
                         gant_chart_max)) {
    return 0;
  }

  if (!append_str_to_str("\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  if (!append_str_to_str(*lines_section, gant_chart, gant_chart_len,
                         gant_chart_max)) {
    return 0;
  }

  if (!append_str_to_str("\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  if (!append_str_to_str(*time_section, gant_chart, gant_chart_len,
                         gant_chart_max)) {
    return 0;
  }

  if (!append_str_to_str("\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  (*gant_chart)[(*gant_chart_len)] = '\0';

  free(*procs_section);
  free(*lines_section);
  free(*time_section);

  return 1;
}

int draw_gant(char **gant_chart, int *gant_chart_len, int *gant_chart_max,
              char **procs_section, int *procs_section_len,
              int *procs_section_max, char **lines_section,
              int *lines_section_len, int *lines_section_max,
              char **time_section, int *time_section_len, int *time_section_max,
              int pid, int current_time, int burst, int line_count,
              int max_line_char) {
  if (burst == 0)
    return 1;

  if (!draw_gant_proc(procs_section, procs_section_len, procs_section_max, pid,
                      burst, line_count))
    return 0;

  if (!draw_gant_line(lines_section, lines_section_len, lines_section_max,
                      burst, pid == -1, line_count))
    return 0;

  if (!draw_gant_time(time_section, time_section_len, time_section_max,
                      current_time, burst, line_count))
    return 0;

  if (!line_break_gant(gant_chart, gant_chart_len, gant_chart_max,
                       procs_section, procs_section_len, procs_section_max,
                       lines_section, lines_section_len, lines_section_max,
                       time_section, time_section_len, time_section_max,
                       max_line_char)) {
    return 0;
  }

  return 1;
}

int draw_gant_proc(char **procs_section, int *procs_section_len,
                   int *procs_section_max, int pid, int burst, int line_count) {
  int total_lines = (burst * line_count) + 1;

  char pname[32];
  if (pid == -1) {
    if (sprintf(pname, " ") < 0) {
      return 0;
    }
  } else {
    if (sprintf(pname, "%d", pid) < 0) {
      return 0;
    }
  }

  int add_char_res = append_str_to_str(pname, procs_section, procs_section_len,
                                       procs_section_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines; i++) {
    add_char_res = append_char_to_str(' ', procs_section, procs_section_len,
                                      procs_section_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  add_char_res = 0;

  (*procs_section)[(*procs_section_len)] = '\0';

  return 1;
}

int draw_gant_line(char **lines_section, int *lines_section_len,
                   int *lines_section_max, int burst, int is_ctx,
                   int line_count) {
  int add_char_res = append_char_to_str('|', lines_section, lines_section_len,
                                        lines_section_max);

  for (int i = 0; i < burst; i++) {
    for (int j = 0; j < line_count; j++) {
      add_char_res +=
          is_ctx ? append_char_to_str('*', lines_section, lines_section_len,
                                      lines_section_max)
                 : append_char_to_str('-', lines_section, lines_section_len,
                                      lines_section_max);
    }
  }

  int total_lines = (burst * line_count) + 1;
  if (add_char_res != total_lines) {
    return 0;
  }

  (*lines_section)[(*lines_section_len)] = '\0';

  return 1;
}

int draw_gant_time(char **time_section, int *time_section_len,
                   int *time_section_max, int current_time, int burst,
                   int line_count) {
  int total_lines = (burst * line_count) + 1;

  int add_char_res = append_num_to_str(current_time, time_section,
                                       time_section_len, time_section_max);

  if (add_char_res == 0) {
    return 0;
  }

  for (int i = add_char_res; i < total_lines; i++) {
    add_char_res = append_char_to_str(' ', time_section, time_section_len,
                                      time_section_max);

    if (add_char_res == 0) {
      return 0;
    }
  }

  (*time_section)[(*time_section_len)] = '\0';

  return 1;
}

int line_break_gant(char **gant_chart, int *gant_chart_len, int *gant_chart_max,
                    char **procs_section, int *procs_section_len,
                    int *procs_section_max, char **lines_section,
                    int *lines_section_len, int *lines_section_max,
                    char **time_section, int *time_section_len,
                    int *time_section_max, int max_line_char) {
  if ((*procs_section_len) < max_line_char &&
      (*lines_section_len) < max_line_char &&
      (*time_section_len) < max_line_char) {
    return 1;
  }

  for (int i = 0; i < max_line_char; i++) {
    if (!append_char_to_str((*procs_section)[i], gant_chart, gant_chart_len,
                            gant_chart_max)) {
      return 0;
    }
  }

  if (!append_str_to_str("\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  for (int i = 0; i < max_line_char; i++) {
    if (!append_char_to_str((*lines_section)[i], gant_chart, gant_chart_len,
                            gant_chart_max)) {
      return 0;
    }
  }

  if (!append_str_to_str("\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  for (int i = 0; i < max_line_char; i++) {
    if (!append_char_to_str((*time_section)[i], gant_chart, gant_chart_len,
                            gant_chart_max)) {
      return 0;
    }
  }

  if (!append_str_to_str("\n\n", gant_chart, gant_chart_len, gant_chart_max)) {
    return 0;
  }

  (*gant_chart)[(*gant_chart_len)] = '\0';

  int new_gant_chart_procs_max = ALGO_INFO_SECTION_SIZE;
  int new_gant_chart_procs_len = 0;
  char *new_gant_chart_procs =
      (char *)malloc(sizeof(char) * new_gant_chart_procs_max);

  if (new_gant_chart_procs == NULL) {
    return 0;
  }

  int new_gant_chart_lines_max = ALGO_INFO_SECTION_SIZE;
  int new_gant_chart_lines_len = 0;
  char *new_gant_chart_lines =
      (char *)malloc(sizeof(char) * new_gant_chart_lines_max);

  if (new_gant_chart_lines == NULL) {
    free(new_gant_chart_procs);
    return 0;
  }

  int new_gant_chart_time_max = ALGO_INFO_SECTION_SIZE;
  int new_gant_chart_time_len = 0;
  char *new_gant_chart_time =
      (char *)malloc(sizeof(char) * new_gant_chart_time_max);

  if (new_gant_chart_time == NULL) {
    free(new_gant_chart_procs);
    free(new_gant_chart_lines);
    return 0;
  }

  for (int i = max_line_char; i < (*procs_section_len); i++) {
    if (!append_char_to_str((*procs_section)[i], &new_gant_chart_procs,
                            &new_gant_chart_procs_len,
                            &new_gant_chart_procs_max)) {
      free(new_gant_chart_procs);
      free(new_gant_chart_lines);
      free(new_gant_chart_time);
      return 0;
    }
  }

  for (int i = max_line_char; i < (*lines_section_len); i++) {
    if (!append_char_to_str((*lines_section)[i], &new_gant_chart_lines,
                            &new_gant_chart_lines_len,
                            &new_gant_chart_lines_max)) {
      free(new_gant_chart_procs);
      free(new_gant_chart_lines);
      free(new_gant_chart_time);
      return 0;
    }
  }

  for (int i = max_line_char; i < (*time_section_len); i++) {
    if (!append_char_to_str((*time_section)[i], &new_gant_chart_time,
                            &new_gant_chart_time_len,
                            &new_gant_chart_time_max)) {
      free(new_gant_chart_procs);
      free(new_gant_chart_lines);
      free(new_gant_chart_time);
      return 0;
    }
  }

  free(*procs_section);
  free(*lines_section);
  free(*time_section);

  new_gant_chart_procs[new_gant_chart_procs_len] = '\0';
  new_gant_chart_lines[new_gant_chart_lines_len] = '\0';
  new_gant_chart_time[new_gant_chart_time_len] = '\0';

  *procs_section = new_gant_chart_procs;
  *procs_section_len = new_gant_chart_procs_len;
  *procs_section_max = new_gant_chart_procs_max;

  *lines_section = new_gant_chart_lines;
  *lines_section_len = new_gant_chart_lines_len;
  *lines_section_max = new_gant_chart_lines_max;

  *time_section = new_gant_chart_time;
  *time_section_len = new_gant_chart_time_len;
  *time_section_max = new_gant_chart_time_max;

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

  (*str)[(*len)] = '\0';

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

  (*str)[(*len)] = '\0';

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

  (*str)[(*len)] = '\0';

  return char_added;
}

int append_char_to_str(char c, char **str, int *len, int *max) {
  if ((*len) >= (*max) - 1) {
    if (!realloc_str(str, max)) {
      return 0;
    }
  }

  (*str)[(*len)++] = c;
  (*str)[(*len)] = '\0';
  return 1;
}

int realloc_str(char **stats, int *max) {
  *max *= 2;
  char *temp = (char *)realloc(*stats, sizeof(char) * (*max));
  if (temp == NULL)
    return 0;
  *stats = temp;
  return 1;
}
