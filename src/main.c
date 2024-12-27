#include "../include/proc.h"
#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  proc *p1 = new_proc(1, 1, 4, 1);
  proc *p2 = new_proc(2, 2, 8, 5);
  proc *p3 = new_random_proc(3);
  proc *p4 = new_proc(4, 3, 2, 3);

  print_proc(p1);
  print_proc(p2);
  print_proc(p3);
  print_proc(p4);

  queue *q = new_queue(5);
  enqueue(q, p1);
  enqueue(q, p3);
  enqueue(q, p2);
  enqueue(q, p4);
  print_queue(q);

  return 0;
}
