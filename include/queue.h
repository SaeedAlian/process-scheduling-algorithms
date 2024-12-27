#ifndef _H_QUEUE
#define _H_QUEUE

#include "./proc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
  int l;
  int max;
  proc **items;
} queue;

void swap_procs(proc *a, proc *b);

queue *new_queue(int max);
void heapify_down(queue *q, int index);
void heapify_up(queue *q, int index);
int enqueue(queue *q, proc *p);
int dequeue(queue *q, proc **out);
int peek_queue(queue *q, proc **out);
int queue_is_full(queue *q);
int queue_is_empty(queue *q);
void print_queue(queue *q);
void free_queue(queue *q);

#endif
