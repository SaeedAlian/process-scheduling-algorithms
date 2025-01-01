#include "../include/algorithms.h"
#include "../include/args.h"
#include "../include/proc.h"
#include "../include/util.h"
#include <stdio.h>

int main(int argc, char **argv) {
  srand(time(NULL));

  arguments args;
  int procs_len = 0;
  proc *procs[MAX_PROC];

  if (!parse_arguments(argc, argv, &args)) {
    return 1;
  }

  if (!args.fill_random && args.input_file != NULL &&
      strlen(args.input_file) != 0) {
    if (!read_procs_from_input_file(args.input_file, &procs, &procs_len)) {

      if (args.output_dir_is_default)
        free(args.output_dir);

      free(args.algorithms);
      return 1;
    }
  } else {
    if (!read_procs_from_stdin(&procs, &procs_len, args.fill_random)) {
      if (args.output_dir_is_default)
        free(args.output_dir);

      free(args.algorithms);
      return 1;
    }
  }

  if (!ensure_directory_exists(args.output_dir)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }

    if (args.output_dir_is_default)
      free(args.output_dir);

    free(args.algorithms);
    fprintf(stderr,
            "Error: something went wrong in creating the output directory\n");
    return 1;
  }

  int total_result_max = MAX_ALGO_INFO_FILESIZE;
  int total_result_len = 0;
  char *total_result = (char *)malloc(sizeof(char) * total_result_max);
  if (total_result == NULL) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }

    if (args.output_dir_is_default)
      free(args.output_dir);

    free(args.algorithms);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  int total_result_margin = 14;

  if (!append_str_to_str((char *)"   ", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }

    if (args.output_dir_is_default)
      free(args.output_dir);

    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  if (!append_str_to_str((char *)"Name", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 4; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"WT AVG", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 6; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"RT AVG", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 6; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"TT AVG", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 6; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"CTX", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 3; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"TOTAL", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 5; i < total_result_margin; i++) {
    if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  if (!append_str_to_str((char *)"\n\n", &total_result, &total_result_len,
                         &total_result_max)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  for (int i = 0; i < args.algorithms_len; i++) {
    int alg = args.algorithms[i];

    double wt_avg;
    double rt_avg;
    double tt_avg;
    int totaltime;
    int ctx_switch_count;

    const char *algo_name;

    switch (alg) {
    case FCFS: {
      algo_name = "fcfs";
      if (!run_non_preemptive_algo(algo_name, args.output_dir, fcfs, procs,
                                   procs_len, args.ctx_time, &wt_avg, &rt_avg,
                                   &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case PS: {
      algo_name = "ps";
      if (!run_preemptive_algo(algo_name, args.output_dir, ps, procs, procs_len,
                               args.ctx_time, args.quant, &wt_avg, &rt_avg,
                               &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case SRJF: {
      algo_name = "srjf";
      if (!run_preemptive_algo(algo_name, args.output_dir, srjf, procs,
                               procs_len, args.ctx_time, args.quant, &wt_avg,
                               &rt_avg, &tt_avg, &totaltime,
                               &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case LRJF: {
      algo_name = "lrjf";
      if (!run_preemptive_algo(algo_name, args.output_dir, lrjf, procs,
                               procs_len, args.ctx_time, args.quant, &wt_avg,
                               &rt_avg, &tt_avg, &totaltime,
                               &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case RR: {
      algo_name = "rr";
      if (!run_preemptive_algo(algo_name, args.output_dir, rr, procs, procs_len,
                               args.ctx_time, args.quant, &wt_avg, &rt_avg,
                               &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case SJF: {
      algo_name = "sjf";
      if (!run_non_preemptive_algo(algo_name, args.output_dir, sjf, procs,
                                   procs_len, args.ctx_time, &wt_avg, &rt_avg,
                                   &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case LJF: {
      algo_name = "ljf";
      if (!run_non_preemptive_algo(algo_name, args.output_dir, ljf, procs,
                                   procs_len, args.ctx_time, &wt_avg, &rt_avg,
                                   &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }

    case HRRN: {
      algo_name = "hrrn";
      if (!run_non_preemptive_algo(algo_name, args.output_dir, hrrn, procs,
                                   procs_len, args.ctx_time, &wt_avg, &rt_avg,
                                   &tt_avg, &totaltime, &ctx_switch_count)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        return 1;
      }

      break;
    }
    }

    int second_add_char_res = 0;
    int expected_second_add_char_res = 0;

    char formatted_str[256];
    int formatted_str_len = 0;

    if (!append_str_to_str((char *)"   ", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (sprintf(formatted_str, "%s", algo_name) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (sprintf(formatted_str, "%.2f", wt_avg) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (sprintf(formatted_str, "%.2f", rt_avg) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (sprintf(formatted_str, "%.2f", tt_avg) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (sprintf(formatted_str, "%d", ctx_switch_count * args.ctx_time) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (sprintf(formatted_str, "%d", totaltime) < 0) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    if (!append_str_to_str(formatted_str, &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }

    formatted_str_len = strlen(formatted_str);
    expected_second_add_char_res += total_result_margin - formatted_str_len;
    for (int i = formatted_str_len; i < total_result_margin; i++) {
      if (!append_str_to_str((char *)" ", &total_result, &total_result_len,
                             &total_result_max)) {
        for (int i = 0; i < procs_len; i++) {
          if (procs[i] != NULL)
            free(procs[i]);
        }
        if (args.output_dir_is_default)
          free(args.output_dir);
        free(args.algorithms);
        free(total_result);
        fprintf(stderr,
                "Error: something went wrong in generating the total result\n");
        return 1;
      }
    }

    if (!append_str_to_str((char *)"\n\n", &total_result, &total_result_len,
                           &total_result_max)) {
      for (int i = 0; i < procs_len; i++) {
        if (procs[i] != NULL)
          free(procs[i]);
      }
      if (args.output_dir_is_default)
        free(args.output_dir);
      free(args.algorithms);
      free(total_result);
      fprintf(stderr,
              "Error: something went wrong in generating the total result\n");
      return 1;
    }
  }

  total_result[total_result_len] = '\0';

  char result_filename[1024];
  if (sprintf(result_filename, "%s/result.txt", args.output_dir) < 0) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  FILE *file = create_file(result_filename);
  if (file == NULL) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  if (!append_str_to_file(file, total_result, total_result_len)) {
    for (int i = 0; i < procs_len; i++) {
      if (procs[i] != NULL)
        free(procs[i]);
    }
    if (args.output_dir_is_default)
      free(args.output_dir);
    free(args.algorithms);
    free(total_result);
    fprintf(stderr,
            "Error: something went wrong in generating the total result\n");
    return 1;
  }

  printf("All algorithm results have been added in %s\n", args.output_dir);

  for (int i = 0; i < procs_len; i++) {
    if (procs[i] != NULL)
      free(procs[i]);
  }

  if (args.output_dir_is_default)
    free(args.output_dir);

  free(args.algorithms);
  free(total_result);

  return 0;
}
