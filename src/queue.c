#include "../include/queue.h"

queue *new_queue(int max) {
  queue *q = (queue *)malloc(sizeof(queue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->l = 0;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

void heapify_down(queue *q, int index) {
  int largest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  if (left < q->max && q->items[left].pri > q->items[index].pri) {
    largest = left;
  }

  if (right < q->max && q->items[right].pri > q->items[index].pri) {
    largest = right;
  }

  if (largest != index) {
    swap_procs(&q->items[largest], &q->items[index]);
    heapify_down(q, largest);
  }
}

void heapify_up(queue *q, int index) {
  int parent = (index - 1) / 2;

  while (index > 0 && q->items[index].pri > q->items[parent].pri) {
    swap_procs(&q->items[parent], &q->items[index]);

    index = parent;
    parent = (index - 1) / 2;
  }
}

int enqueue(queue *q, proc p) {
  if (queue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return -1;
    }

    q->items = temp;
  }

  q->items[q->l++] = p;
  heapify_up(q, q->l - 1);
  return 0;
}

int dequeue(queue *q, proc *out) {
  if (queue_is_empty(q)) {
    return -1;
  }

  proc top = q->items[0];
  q->items[0] = q->items[q->l - 1];
  q->l--;

  heapify_down(q, 0);
  *out = top;
  return 0;
}

int peek_queue(queue *q, proc *out) {
  if (queue_is_empty(q))
    return -1;

  *out = q->items[0];
  return 0;
}

int queue_is_full(queue *q) { return q->l == q->max - 1; }

int queue_is_empty(queue *q) { return q->l == 0; }

void print_queue(queue *q) {
  printf("Priority Queue:\n");
  printf("   ");

  for (int i = 0; i < q->l; i++) {
    print_proc(&q->items[i]);
    printf("   ");
  }
}

void free_queue(queue *q) {
  free(q->items);
  free(q);
}

void swap_procs(proc *a, proc *b) {
  if (a == NULL || b == NULL)
    return;

  proc temp = *a;

  a->pid = b->pid;
  a->at = b->at;
  a->bt = b->bt;
  a->pri = b->pri;

  b->pid = temp.pid;
  b->at = temp.at;
  b->bt = temp.bt;
  b->pri = temp.pri;
}
