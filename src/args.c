#include "../include/args.h"

int parse_arguments(int argc, char *argv[], arguments *args) {
  memset(args, 0, sizeof(arguments));

  int opt;
  int long_index = 0;
  static struct option long_options[] = {
      {"algorithms", required_argument, 0, 'a'},
      {"ctx-time", required_argument, 0, 'c'},
      {"output", required_argument, 0, 'o'},
      {"input", required_argument, 0, 'i'},
      {"random", no_argument, 0, 'r'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}};

  char algorithms_str[MAX_ALGORITHMS];
  args->ctx_time = 0;
  args->fill_random = 0;
  args->algorithms_len = 0;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char *buf = (char *)malloc(sizeof(char) * 50);
  if (buf == NULL) {
    fprintf(stderr,
            "Error: there was an error in determining the output filename\n");
    return 0;
  }

  if (sprintf(buf, "%d-%02d-%02d-%02d:%02d:%02d.txt", tm.tm_year + 1900,
              tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
              tm.tm_sec) >= 0) {
    args->output_file = buf;
  } else {
    fprintf(stderr,
            "Error: there was an error in determining the output filename\n");
    return 0;
  }

  while ((opt = getopt_long(argc, argv, "a:o:c:i:hr", long_options,
                            &long_index)) != -1) {
    switch (opt) {
    case 'a':
      if (strlen(optarg) >= MAX_ALGORITHMS) {
        fprintf(stderr,
                "Error: algorithms string is too long (max %d characters)\n",
                MAX_ALGORITHMS - 1);
        return 0;
      }

      strncpy(algorithms_str, optarg, MAX_ALGORITHMS - 1);
      algorithms_str[MAX_ALGORITHMS - 1] = '\0';
      break;
    case 'c': {
      char *endptr;
      errno = 0;
      float ctx = strtof(optarg, &endptr);
      if (errno != 0 || *endptr != '\0' || endptr == optarg) {
        fprintf(stderr, "Error: invalid context time format.\n");
        return 0;
      }
      args->ctx_time = ctx;
      break;
    }
    case 'o':
      free(args->output_file);
      args->output_file = optarg;
      break;
    case 'i':
      args->input_file = optarg;
      break;
    case 'r':
      args->fill_random = 1;
      break;
    case 'h':
      printf("Usage: %s [OPTIONS]\n", argv[0]);
      printf("Options:\n");
      printf("  -a, --algorithms <algorithms>  Comma-separated list of "
             "algorithms (fcfs, ps, srjf, lrjf, sjf, ljf, hrrn, rr)\n");
      printf("  -ct, --ctx-time <ctx_time>    Context switch time (float "
             "between 0 and 5)\n");
      printf("  -o, --output <output>        Output file name\n");
      printf("  -r, --random                 Set all process stats randomly\n");
      printf("  -h, --help                   Show this help message\n");
      exit(0);
      break;
    default:
      fprintf(stderr, "Usage: %s [OPTIONS]\n", argv[0]);
      fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
      return 0;
    }
  }

  int length;
  int *tokenized_algorithms = tokenize_algorithms(algorithms_str, &length);
  if (tokenized_algorithms == NULL) {
    return 0;
  }

  args->algorithms = tokenized_algorithms;
  args->algorithms_len = length;

  if (!validate_ctx_time(args->ctx_time)) {
    return 0;
  }

  if (args->output_file == NULL || strlen(args->output_file) == 0) {
    fprintf(stderr, "Error: output file argument is required\n");
    return 0;
  }

  return 1;
}

int *tokenize_algorithms(char *algorithms, int *length) {
  int len = strlen(algorithms);

  int max = 5;
  int k = 0;
  int *tokenized = (int *)malloc(sizeof(int) * max);
  if (tokenized == NULL)
    return NULL;

  char alg[256];
  int l = 0;

  for (int i = 0; i < len + 1; i++) {
    char c = algorithms[i];

    if (c == ',' || c == '\0') {
      alg[l++] = '\0';

      if (k >= max - 1) {
        max *= 2;
        int *temp = (int *)realloc(tokenized, sizeof(int) * max);
        if (temp == NULL) {
          free(tokenized);
          return NULL;
        }

        tokenized = temp;
      }

      if (strcmp(alg, "fcfs") == 0) {
        tokenized[k++] = FCFS;
      } else if (strcmp(alg, "sjf") == 0) {
        tokenized[k++] = SJF;
      } else if (strcmp(alg, "hrrn") == 0) {
        tokenized[k++] = HRRN;
      } else if (strcmp(alg, "ps") == 0) {
        tokenized[k++] = PS;
      } else if (strcmp(alg, "srjf") == 0) {
        tokenized[k++] = SRJF;
      } else if (strcmp(alg, "lrjf") == 0) {
        tokenized[k++] = LRJF;
      } else if (strcmp(alg, "rr") == 0) {
        tokenized[k++] = RR;
      } else if (strcmp(alg, "ljf") == 0) {
        tokenized[k++] = LJF;
      } else {
        fprintf(stderr, "Error: invalid algorithm %s\n", alg);
        free(tokenized);
        return NULL;
      }

      l = 0;
    } else if (c >= 'A' && c <= 'Z') {
      if (l >= 254) {
        fprintf(stderr, "Error: invalid algorithm %s\n", alg);
        free(tokenized);
        return NULL;
      }

      alg[l++] = c + 32;
    } else if (c >= 'a' && c <= 'z') {
      if (l >= 255) {
        fprintf(stderr, "Error: invalid algorithm %s\n", alg);
        free(tokenized);
        return NULL;
      }

      alg[l++] = c;
    } else {
      fprintf(stderr, "Error: invalid algorithm provided\n");
      free(tokenized);
      return NULL;
    }
  }

  *length = k;
  return tokenized;
}

int validate_ctx_time(float ctx_time) {
  if (ctx_time < 0.0 || ctx_time > 5.0) {
    fprintf(stderr, "Error: context switch time must be between 0 and 5\n");
    return 0;
  }
  return 1;
}
