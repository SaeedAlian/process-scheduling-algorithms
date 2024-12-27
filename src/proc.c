#include "../include/proc.h"

proc *new_proc(int pid, int pri, int bt, int at) {
  proc *n = (proc *)malloc(sizeof(proc));
  if (n == NULL)
    return NULL;

  n->pid = pid;
  n->pri = pri;
  n->at = at;
  n->bt = bt;

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

void print_proc(proc *p) {
  if (p == NULL)
    return;

  printf(
      "Process -> ID = %d, PRIORITY = %d, BURST TIME = %d, ARRIVAL TIME = %d\n",
      p->pid, p->pri, p->bt, p->at);
}
