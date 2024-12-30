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
      return 1;
    }
  } else {
    if (!read_procs_from_stdin(&procs, &procs_len, args.fill_random)) {
      return 1;
    }
  }

  for (int i = 0; i < args.algorithms_len; i++) {
    int alg = args.algorithms[i];

    int output_info_max = MAX_ALGO_INFO_FILESIZE;
    char *output_info = (char *)malloc(sizeof(char) * output_info_max);
    int output_info_len = 0;

    switch (alg) {
    case FCFS: {
      if (!fcfs(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
                &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case PS: {
      if (!ps(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
              &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case SRJF: {
      if (!srjf(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
                &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case LRJF: {
      if (!lrjf(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
                &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case RR: {
      if (!rr(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
              &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case SJF: {
      if (!sjf(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
               &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case LJF: {
      if (!ljf(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
               &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }

    case HRRN: {
      if (!hrrn(procs, procs_len, args.ctx_time, &output_info, &output_info_len,
                &output_info_max)) {
        free(output_info);
        return 1;
      }

      if (!append_str_to_file(args.output_file, output_info, i == 0)) {
        free(output_info);
        fprintf(stderr,
                "Error: something went wrong in creating the output file\n");
        return 1;
      }

      output_info_len = 0;

      break;
    }
    }
  }

  printf("All algorithm results have been added in %s file\n",
         args.output_file);

  return 0;
}
