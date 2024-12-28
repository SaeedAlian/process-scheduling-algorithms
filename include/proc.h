#ifndef _H_PROC
#define _H_PROC

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROC 1024

typedef struct proc {
  int pid;
  int pri;
  int bt;
  int at;
} proc;

proc *new_proc(int pid, int pri, int bt, int at);
proc *new_random_proc(int pid);
void print_proc(proc *p);

#endif
