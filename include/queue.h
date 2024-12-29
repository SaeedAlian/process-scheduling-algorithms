#ifndef _H_QUEUE
#define _H_QUEUE

#include "./proc.h"
#include <stdio.h>
#include <stdlib.h>

enum qorder { ASC, DESC };

typedef struct atqueue {
  int max;
  int front;
  int rear;
  proc *items;
  enum qorder order;
} atqueue;

typedef struct btqueue {
  int max;
  int front;
  int rear;
  proc *items;
  enum qorder order;
} btqueue;

typedef struct pqueue {
  int max;
  int front;
  int rear;
  proc *items;
  enum qorder order;
} pqueue;

typedef struct queue {
  int max;
  int front;
  int rear;
  proc *items;
} queue;

void swap_procs(proc *a, proc *b);

atqueue *new_atqueue(int max, enum qorder order);
btqueue *new_btqueue(int max, enum qorder order);
pqueue *new_pqueue(int max, enum qorder order);
queue *new_queue(int max);

atqueue *clone_atqueue(atqueue *q);
btqueue *clone_btqueue(btqueue *q);
pqueue *clone_pqueue(pqueue *q);
queue *clone_queue(queue *q);

void heapify_up_atqueue(atqueue *q, int index);
void heapify_up_btqueue(btqueue *q, int index);
void heapify_up_pqueue(pqueue *q, int index);

void heapify_down_atqueue(atqueue *q, int index);
void heapify_down_btqueue(btqueue *q, int index);
void heapify_down_pqueue(pqueue *q, int index);

int index_is_in_queue(queue *q, int index);

int at_enqueue(atqueue *q, proc p);
int bt_enqueue(btqueue *q, proc p);
int p_enqueue(pqueue *q, proc p);
int enqueue(queue *q, proc p);

int at_dequeue(atqueue *q, proc *out);
int bt_dequeue(btqueue *q, proc *out);
int p_dequeue(pqueue *q, proc *out);
int dequeue(queue *q, proc *out);

int peek_atqueue(atqueue *q, proc *out);
int peek_btqueue(btqueue *q, proc *out);
int peek_pqueue(pqueue *q, proc *out);
int peek_queue(queue *q, proc *out);

proc *get_sorted_atqueue_elements(atqueue *q, int *len);
proc *get_sorted_btqueue_elements(btqueue *q, int *len);
proc *get_sorted_pqueue_elements(pqueue *q, int *len);

int atqueue_length(atqueue *q);
int btqueue_length(btqueue *q);
int pqueue_length(pqueue *q);
int queue_length(queue *q);

int atqueue_is_full(atqueue *q);
int btqueue_is_full(btqueue *q);
int pqueue_is_full(pqueue *q);
int queue_is_full(queue *q);

int atqueue_is_empty(atqueue *q);
int btqueue_is_empty(btqueue *q);
int pqueue_is_empty(pqueue *q);
int queue_is_empty(queue *q);

void print_atqueue(atqueue *q);
void print_btqueue(btqueue *q);
void print_pqueue(pqueue *q);
void print_queue(queue *q);

void free_atqueue(atqueue *q);
void free_btqueue(btqueue *q);
void free_pqueue(pqueue *q);
void free_queue(queue *q);

#endif
