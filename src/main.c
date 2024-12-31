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

  if (!ensure_directory_exists(args.output_dir)) {
    fprintf(stderr,
            "Error: something went wrong in creating the output directory\n");
    return 1;
  }

  for (int i = 0; i < args.algorithms_len; i++) {
    int alg = args.algorithms[i];

    switch (alg) {
    case FCFS: {
      if (!run_alog("fcfs", args.output_dir, fcfs, procs, procs_len,
                    args.ctx_time)) {
        return 1;
      }

      break;
    }

    case PS: {
      if (!run_alog("ps", args.output_dir, ps, procs, procs_len, args.ctx_time,
                    args.quant)) {
        return 1;
      }

      break;
    }

    case SRJF: {
      if (!run_alog("srjf", args.output_dir, srjf, procs, procs_len,
                    args.ctx_time, args.quant)) {
        return 1;
      }

      break;
    }

    case LRJF: {
      if (!run_alog("lrjf", args.output_dir, lrjf, procs, procs_len,
                    args.ctx_time, args.quant)) {
        return 1;
      }

      break;
    }

    case RR: {
      if (!run_alog("rr", args.output_dir, rr, procs, procs_len, args.ctx_time,
                    args.quant)) {
        return 1;
      }

      break;
    }

    case SJF: {
      if (!run_alog("sjf", args.output_dir, sjf, procs, procs_len,
                    args.ctx_time)) {
        return 1;
      }

      break;
    }

    case LJF: {
      if (!run_alog("ljf", args.output_dir, ljf, procs, procs_len,
                    args.ctx_time)) {
        return 1;
      }

      break;
    }

    case HRRN: {
      if (!run_alog("hrrn", args.output_dir, hrrn, procs, procs_len,
                    args.ctx_time)) {
        return 1;
      }

      break;
    }
    }
  }

  printf("All algorithm results have been added in %s\n", args.output_dir);

  return 0;
}
