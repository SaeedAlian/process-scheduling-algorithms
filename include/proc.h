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

  // props
  int wt;
  int tt;
  int rt;
} proc;

proc *new_proc(int pid, int pri, int bt, int at);
proc *new_random_proc(int pid);

int add_proc_wt(proc *p, int wt);
int add_proc_tt(proc *p, int tt);
int add_proc_rt(proc *p, int rt);

void print_proc(proc *p);

#endif
