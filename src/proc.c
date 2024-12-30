#include "../include/proc.h"

proc *new_proc(int pid, int pri, int bt, int at) {
  proc *n = (proc *)malloc(sizeof(proc));
  if (n == NULL)
    return NULL;

  n->pid = pid;
  n->pri = pri;
  n->at = at;
  n->bt = bt;

  n->wt = -1;
  n->rt = -1;
  n->tt = -1;

  n->sbt = 0;

  return n;
}

proc *new_random_proc(int pid) {
  int pri = (rand() % 10) + 1;
  int at = (rand() % 25) + 1;
  int bt = (rand() % 25) + 1;

  proc *n = new_proc(pid, pri, bt, at);
  if (n == NULL)
    return NULL;

  return n;
}

int add_proc_wt(proc *p, int wt) {
  if (wt < 0)
    return 0;

  if (p == NULL)
    return 0;

  p->wt = wt;
  return 1;
}

int add_proc_tt(proc *p, int tt) {
  if (tt < 0)
    return 0;

  if (p == NULL)
    return 0;

  p->tt = tt;
  return 1;
}

int add_proc_rt(proc *p, int rt) {
  if (rt < 0)
    return 0;

  if (p == NULL)
    return 0;

  p->rt = rt;
  return 1;
}

int increment_sbt(proc *p, int s) {
  if (p == NULL)
    return 0;

  int n = p->sbt + s;
  if (n > p->bt)
    n = p->bt;

  p->sbt = n;
  return 1;
}

void print_proc(proc *p) {
  if (p == NULL)
    return;

  printf(
      "Process -> ID = %d, PRIORITY = %d, BURST TIME = %d, ARRIVAL TIME = %d\n",
      p->pid, p->pri, p->bt, p->at);
}
