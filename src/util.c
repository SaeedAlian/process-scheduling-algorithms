#include "../include/util.h"

int read_procs_from_input_file(char *input_file, proc *(*procs)[1024],
                               int *procs_len) {
  if (access(input_file, F_OK) == 0) {
    FILE *fptr = NULL;
    fptr = fopen(input_file, "r");

    if (fptr == NULL) {
      fprintf(stderr, "Error: unable to open the input file\n");
    }

    int header_len = 14;
    char header[header_len];
    int i = 0;
    char ch;

    while ((ch = fgetc(fptr)) != '\n' && i < header_len) {
      if (ch == ' ')
        continue;
      if (ch == EOF) {
        fclose(fptr);
        fprintf(stderr,
                "Error: invalid input received, please check the input "
                "file to be correct\nThe first line of the input file must "
                "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
        return 0;
      }

      header[i++] = ch;
    }

    header[i++] = '\0';

    if (i != header_len || ch != '\n') {
      fclose(fptr);
      fprintf(stderr,
              "Error: invalid input received, please check the input "
              "file to be correct\nThe first line of the input file must "
              "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
      return 0;
    }

    int pid_index, at_index, bt_index, pri_index;

    int max_label_len = 4;
    char label[max_label_len];
    int label_count = 0;
    int max_label_count = 4;
    int l = 0;

    for (int j = 0; j < i; j++) {
      char c = header[j];

      if (c == ',' || c == '\0') {
        if (label_count >= max_label_count) {
          fclose(fptr);
          fprintf(stderr,
                  "Error: invalid input received, please check the input "
                  "file to be correct\nThe first line of the input file must "
                  "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
          return 0;
        }

        label[l++] = '\0';

        if (strcmp(label, "PID") == 0) {
          pid_index = label_count;
        } else if (strcmp(label, "AT") == 0) {
          at_index = label_count;
        } else if (strcmp(label, "BT") == 0) {
          bt_index = label_count;
        } else if (strcmp(label, "PRI") == 0) {
          pri_index = label_count;
        } else {
          fclose(fptr);
          fprintf(stderr,
                  "Error: invalid input received, please check the input "
                  "file to be correct\nThe first line of the input file must "
                  "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
          return 0;
        }

        label_count++;
        l = 0;
      } else if (c <= 'Z' && c >= 'A') {
        if (l >= max_label_len - 1) {
          fclose(fptr);
          fprintf(stderr,
                  "Error: invalid input received, please check the input "
                  "file to be correct\nThe first line of the input file must "
                  "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
          return 0;
        }

        label[l++] = c;
      } else {
        fclose(fptr);
        fprintf(stderr,
                "Error: invalid input received, please check the input "
                "file to be correct\nThe first line of the input file must "
                "contain: 'PID,PRI,AT,BT' (you can change the order too)\n");
        return 0;
      }
    }

    int max_line_len = 36;
    char line[max_line_len];
    i = 0;

    while ((ch = fgetc(fptr)) != EOF) {
      if (ch == ' ')
        continue;
      if (ch == '\n') {
        line[i++] = '\0';
        int pid = -1, at = -1, bt = -1, pri = -1;

        int num;
        int num_count = 0;
        int max_num_count = 4;
        l = 0;

        if (*procs_len >= MAX_PROC - 1) {
          fclose(fptr);
          fprintf(stderr, "Error: you cannot add more than %d processes\n",
                  MAX_PROC);
          return 0;
        }

        for (int j = 0; j < i; j++) {
          char c = line[j];

          if (c == ',' || c == '\0') {
            if (num_count >= max_num_count) {
              fclose(fptr);
              fprintf(
                  stderr,
                  "Error: you cannot have more than %d numbers in each line\n",
                  max_num_count);
              return 0;
            }

            if (num_count == pid_index) {
              pid = num;
            } else if (num_count == at_index) {
              at = num;
            } else if (num_count == pri_index) {
              pri = num;
            } else if (num_count == bt_index) {
              bt = num;
            } else {
              fclose(fptr);
              fprintf(stderr,
                      "Error: each line in the input file cannot be more "
                      "than %d characters (each number must be at most %d "
                      "digits)\n",
                      max_line_len - 1, (max_line_len - 4) / 4);
              return 0;
            }

            num_count++;
            num = 0;
            l = 0;
          } else if (c <= '9' && c >= '0') {
            if (l >= (max_line_len - 4) / 4) {
              fclose(fptr);
              fprintf(stderr,
                      "Error: each line in the input file cannot be more "
                      "than %d characters (each number must be at most %d "
                      "digits)\n",
                      max_line_len - 1, (max_line_len - 4) / 4);
              return 0;
            }

            num *= 10;
            num += c - '0';
            l++;
          } else {
            fclose(fptr);
            fprintf(stderr,
                    "Error: each line must contain only numbers and ','\n");
            return 0;
          }
        }

        if (pid < 0 || pri < 0 || bt <= 0 || at < 0) {
          fclose(fptr);
          fprintf(stderr, "Error: each line must contain only numbers and ',' "
                          "and also the numbers must be greater than or equal "
                          "to zero and 'BT' cannot be zero\n");
          return 0;
        }

        proc *np = new_proc(pid, pri, bt, at);
        (*procs)[(*procs_len)++] = np;
        i = 0;
        continue;
      }

      if (i >= max_line_len - 1) {
        fclose(fptr);
        fprintf(stderr,
                "Error: each line in the input file cannot be more "
                "than %d characters (each number must be at most %d digits)\n",
                max_line_len - 1, (max_line_len - 4) / 4);
        return 0;
      }

      line[i++] = ch;
    }

    fclose(fptr);
    return 1;
  } else {
    fprintf(stderr, "Error: input file doesn't exist\n");
    return 0;
  }
}

int read_procs_from_stdin(proc *(*procs)[1024], int *procs_len,
                          int fill_random) {
  char np[NUM_PROC_INPUT_MAX_DEFAULT];
  if (get_input("Enter the number of processes: (1 to 1023) ", np,
                NUM_PROC_INPUT_MAX_DEFAULT) != OK) {
    fprintf(stderr, "Error: invalid input\n");
    return 0;
  }

  char *endptr;
  errno = 0;
  int number_of_processes = strtol(np, &endptr, 10);

  if (errno != 0 || *endptr != '\0' || endptr == np) {
    fprintf(stderr, "Error: invalid input\n");
    return 0;
  }

  if (number_of_processes >= MAX_PROC) {
    fprintf(stderr, "Error: invalid input\n");
    return 0;
  }

  char pri_buf[PROC_INPUT_MAX_DEFAULT];
  char at_buf[PROC_INPUT_MAX_DEFAULT];
  char bt_buf[PROC_INPUT_MAX_DEFAULT];

  char rand_buf[PROC_INPUT_MAX_DEFAULT];

  for (int i = 0; i < number_of_processes; i++) {
    if (fill_random) {
      proc *np = new_random_proc(i + 1);
      (*procs)[(*procs_len)++] = np;
      continue;
    }

    char pri_prmpt[PROMPT_MAX_DEFAULT];
    char at_prmpt[PROMPT_MAX_DEFAULT];
    char bt_prmpt[PROMPT_MAX_DEFAULT];

    char rand_prmpt[PROMPT_MAX_DEFAULT];

    if (sprintf(rand_prmpt,
                "Do you want the process number %d to be random? (y/N) ",
                i + 1) < 0) {
      fprintf(stderr, "Error: some error occurred\n");
      return 0;
    }

    int rand_res = get_input(rand_prmpt, rand_buf, PROC_INPUT_MAX_DEFAULT);
    if ((rand_res != NO_INPUT && rand_res != EMPTY_INPUT) &&
        (strcmp(rand_buf, "y") == 0 || strcmp(rand_buf, "Y") == 0)) {
      if (rand_res != OK) {
        fprintf(stderr, "Error: invalid input\n");
        return 0;
      }

      proc *np = new_random_proc(i + 1);
      (*procs)[(*procs_len)++] = np;
      continue;
    }

    if (sprintf(pri_prmpt,
                "Enter the priority for process number %d: (enter nothing "
                "for default value 1) ",
                i + 1) < 0) {
      fprintf(stderr, "Error: some error occurred\n");
      return 0;
    }
    if (sprintf(at_prmpt,
                "Enter the arrival time for process number %d: ", i + 1) < 0) {
      fprintf(stderr, "Error: some error occurred\n");
      return 0;
    }
    if (sprintf(bt_prmpt,
                "Enter the burst time for process number %d: ", i + 1) < 0) {
      fprintf(stderr, "Error: some error occurred\n");
      return 0;
    }

    if (get_input(at_prmpt, at_buf, PROC_INPUT_MAX_DEFAULT) != OK) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    if (get_input(bt_prmpt, bt_buf, PROC_INPUT_MAX_DEFAULT) != OK) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    endptr = NULL;
    errno = 0;
    int at = strtol(at_buf, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == np) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    if (at < 0) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    endptr = NULL;
    errno = 0;
    int bt = strtol(bt_buf, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == np) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    if (bt <= 0) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    }

    int pri_res = get_input(pri_prmpt, pri_buf, PROC_INPUT_MAX_DEFAULT);
    int pri;

    if (pri_res == NO_INPUT || pri_res == EMPTY_INPUT) {
      pri = 1;
    } else if (pri_res != OK) {
      fprintf(stderr, "Error: invalid input\n");
      return 0;
    } else {
      endptr = NULL;
      errno = 0;
      pri = strtol(pri_buf, &endptr, 10);

      if (errno != 0 || *endptr != '\0' || endptr == np) {
        fprintf(stderr, "Error: invalid input\n");
        return 0;
      }

      if (pri <= 0) {
        fprintf(stderr, "Error: invalid input\n");
        return 0;
      }
    }

    proc *np = new_proc(i + 1, pri, bt, at);
    (*procs)[(*procs_len)++] = np;
  }

  return 1;
}

void create_file(char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "w");
  fclose(fptr);
}

int append_str_to_file(char *f, char *s, int clear_file) {
  if (clear_file)
    create_file(f);

  FILE *fptr = fopen(f, "ab");
  if (fptr != NULL) {
    fputs(s, fptr);
    fclose(fptr);
    return 1;
  } else {
    return 0;
  }
}

int get_input(const char *prmpt, char *buff, size_t size) {
  if (prmpt != NULL) {
    printf("%s", prmpt);
  }

  if (fgets(buff, size, stdin) == NULL)
    return NO_INPUT;

  int l = strlen(buff);

  if (l == 0 || buff[0] == 10)
    return EMPTY_INPUT;

  if (buff[l - 1] != '\n') {
    int c;

    while ((c = getchar() != '\n') && (c != EOF))
      return TOO_LONG;
  }

  buff[l - 1] = '\0';

  return OK;
}
