#include "../include/queue.h"

atqueue *new_atqueue(int max, enum qorder order) {
  atqueue *q = (atqueue *)malloc(sizeof(atqueue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->front = -1;
  q->rear = -1;
  q->order = order;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

btqueue *new_btqueue(int max, enum qorder order) {
  btqueue *q = (btqueue *)malloc(sizeof(btqueue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->front = -1;
  q->rear = -1;
  q->order = order;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

pqueue *new_pqueue(int max, enum qorder order) {
  pqueue *q = (pqueue *)malloc(sizeof(pqueue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->front = -1;
  q->rear = -1;
  q->order = order;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

rrqueue *new_rrqueue(int max, enum qorder order) {
  rrqueue *q = (rrqueue *)malloc(sizeof(rrqueue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->front = -1;
  q->rear = -1;
  q->order = order;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

queue *new_queue(int max) {
  queue *q = (queue *)malloc(sizeof(queue));
  if (q == NULL)
    return NULL;

  q->max = max;
  q->front = -1;
  q->rear = -1;
  q->items = (proc *)malloc(sizeof(proc) * q->max);
  if (q->items == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

atqueue *clone_atqueue(atqueue *q) {
  atqueue *clone = new_atqueue(q->max, q->order);

  if (clone == NULL)
    return NULL;

  clone->front = q->front;
  clone->rear = q->rear;

  if (atqueue_is_empty(q)) {
    return clone;
  }

  for (int i = q->front; i <= q->rear; i++) {
    proc p;
    p.pid = q->items[i].pid;
    p.at = q->items[i].at;
    p.bt = q->items[i].bt;
    p.pri = q->items[i].pri;

    p.wt = q->items[i].wt;
    p.rt = q->items[i].rt;
    p.tt = q->items[i].tt;
    p.sbt = q->items[i].sbt;

    clone->items[i] = p;
  }

  return clone;
}

btqueue *clone_btqueue(btqueue *q) {
  btqueue *clone = new_btqueue(q->max, q->order);

  if (clone == NULL)
    return NULL;

  clone->front = q->front;
  clone->rear = q->rear;

  if (btqueue_is_empty(q)) {
    return clone;
  }

  for (int i = q->front; i <= q->rear; i++) {
    proc p;
    p.pid = q->items[i].pid;
    p.at = q->items[i].at;
    p.bt = q->items[i].bt;
    p.pri = q->items[i].pri;

    p.wt = q->items[i].wt;
    p.rt = q->items[i].rt;
    p.tt = q->items[i].tt;
    p.sbt = q->items[i].sbt;

    clone->items[i] = p;
  }

  return clone;
}

pqueue *clone_pqueue(pqueue *q) {
  pqueue *clone = new_pqueue(q->max, q->order);

  if (clone == NULL)
    return NULL;

  clone->front = q->front;
  clone->rear = q->rear;

  if (pqueue_is_empty(q)) {
    return clone;
  }

  for (int i = q->front; i <= q->rear; i++) {
    proc p;
    p.pid = q->items[i].pid;
    p.at = q->items[i].at;
    p.bt = q->items[i].bt;
    p.pri = q->items[i].pri;

    p.wt = q->items[i].wt;
    p.rt = q->items[i].rt;
    p.tt = q->items[i].tt;
    p.sbt = q->items[i].sbt;

    clone->items[i] = p;
  }

  return clone;
}

rrqueue *clone_rrqueue(rrqueue *q) {
  rrqueue *clone = new_rrqueue(q->max, q->order);

  if (clone == NULL)
    return NULL;

  clone->front = q->front;
  clone->rear = q->rear;

  if (rrqueue_is_empty(q)) {
    return clone;
  }

  for (int i = q->front; i <= q->rear; i++) {
    proc p;
    p.pid = q->items[i].pid;
    p.at = q->items[i].at;
    p.bt = q->items[i].bt;
    p.pri = q->items[i].pri;

    p.wt = q->items[i].wt;
    p.rt = q->items[i].rt;
    p.tt = q->items[i].tt;
    p.sbt = q->items[i].sbt;

    clone->items[i] = p;
  }

  return clone;
}

queue *clone_queue(queue *q) {
  queue *clone = new_queue(q->max);

  if (clone == NULL)
    return NULL;

  clone->front = q->front;
  clone->rear = q->rear;

  if (q->front == -1 && q->rear == -1) {
    return clone;
  }

  for (int i = 0; i <= q->max; i++) {
    if (index_is_in_queue(q, i)) {
      proc p;
      p.pid = q->items[i].pid;
      p.at = q->items[i].at;
      p.bt = q->items[i].bt;
      p.pri = q->items[i].pri;

      p.wt = q->items[i].wt;
      p.rt = q->items[i].rt;
      p.tt = q->items[i].tt;
      p.sbt = q->items[i].sbt;

      clone->items[i] = p;
    }
  }

  return clone;
}

int at_enqueue(atqueue *q, proc p) {
  if (atqueue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return 0;
    }

    q->items = temp;
  }

  if (q->front == -1)
    q->front++;

  int new_rear = q->rear + 1;
  q->items[new_rear] = p;
  q->rear = new_rear;
  heapify_up_atqueue(q, q->rear);

  return 1;
}

int bt_enqueue(btqueue *q, proc p) {
  if (btqueue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return 0;
    }

    q->items = temp;
  }

  if (q->front == -1)
    q->front++;

  int new_rear = q->rear + 1;
  q->items[new_rear] = p;
  q->rear = new_rear;
  heapify_up_btqueue(q, q->rear);

  return 1;
}

int p_enqueue(pqueue *q, proc p) {
  if (pqueue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return 0;
    }

    q->items = temp;
  }

  if (q->front == -1)
    q->front++;

  int new_rear = q->rear + 1;
  q->items[new_rear] = p;
  q->rear = new_rear;
  heapify_up_pqueue(q, q->rear);

  return 1;
}

int rr_enqueue(rrqueue *q, proc p) {
  if (rrqueue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return 0;
    }

    q->items = temp;
  }

  if (q->front == -1)
    q->front++;

  int new_rear = q->rear + 1;
  q->items[new_rear] = p;
  q->rear = new_rear;
  heapify_up_rrqueue(q, q->rear);

  return 1;
}

int enqueue(queue *q, proc p) {
  if (queue_is_full(q)) {
    q->max *= 2;
    proc *temp = (proc *)realloc(q->items, sizeof(proc) * q->max);
    if (temp == NULL) {
      return 0;
    }

    q->items = temp;

    int overflow = q->front - q->rear;

    if (overflow > 0) {
      int end = q->max / 2;
      for (int i = 0; i <= overflow; i++) {
        q->items[end++] = q->items[i];
      }
      q->rear = end - 1;
    }
  }

  int new_rear = (q->rear + 1) % q->max;

  if (q->front == -1)
    q->front = (q->front + 1) % q->max;

  q->items[new_rear] = p;
  q->rear = new_rear;

  return 1;
}

int at_dequeue(atqueue *q, proc *out) {
  if (atqueue_is_empty(q)) {
    return 0;
  }

  proc top = q->items[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
    *out = top;
    return 1;
  }

  swap_procs(&q->items[q->rear], &q->items[q->front]);
  q->rear--;
  heapify_down_atqueue(q, q->front);

  *out = top;

  return 1;
}

int bt_dequeue(btqueue *q, proc *out) {
  if (btqueue_is_empty(q)) {
    return 0;
  }

  proc top = q->items[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
    *out = top;
    return 1;
  }

  swap_procs(&q->items[q->rear], &q->items[q->front]);
  q->rear--;
  heapify_down_btqueue(q, q->front);

  *out = top;

  return 1;
}

int p_dequeue(pqueue *q, proc *out) {
  if (pqueue_is_empty(q)) {
    return 0;
  }

  proc top = q->items[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
    *out = top;
    return 1;
  }

  swap_procs(&q->items[q->rear], &q->items[q->front]);
  q->rear--;
  heapify_down_pqueue(q, q->front);

  *out = top;

  return 1;
}

int rr_dequeue(rrqueue *q, proc *out) {
  if (rrqueue_is_empty(q)) {
    return 0;
  }

  proc top = q->items[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
    *out = top;
    return 1;
  }

  swap_procs(&q->items[q->rear], &q->items[q->front]);
  q->rear--;
  heapify_down_rrqueue(q, q->front);

  *out = top;

  return 1;
}

int dequeue(queue *q, proc *out) {
  if (queue_is_empty(q)) {
    return 0;
  }

  proc top = q->items[q->front];

  if (q->front == q->rear) {
    q->front = q->rear = -1;
  } else {
    q->front = (q->front + 1) % q->max;
  }

  *out = top;

  return 1;
}

int peek_atqueue(atqueue *q, proc *out) {
  if (atqueue_is_empty(q))
    return 0;

  *out = q->items[q->front];
  return 1;
}

int peek_btqueue(btqueue *q, proc *out) {
  if (btqueue_is_empty(q))
    return 0;

  *out = q->items[q->front];
  return 1;
}

int peek_pqueue(pqueue *q, proc *out) {
  if (pqueue_is_empty(q))
    return 0;

  *out = q->items[q->front];
  return 1;
}

int peek_rrqueue(rrqueue *q, proc *out) {
  if (rrqueue_is_empty(q))
    return 0;

  *out = q->items[q->front];
  return 1;
}

int peek_queue(queue *q, proc *out) {
  if (queue_is_empty(q))
    return 0;

  *out = q->items[q->front];
  return 1;
}

void heapify_down_atqueue(atqueue *q, int index) {
  if (index < 0)
    return;

  int largest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  if (q->order == ASC) {
    if (left <= q->rear && (q->items[left].at > q->items[largest].at ||
                            (q->items[left].at == q->items[largest].at &&
                             q->items[left].pri < q->items[largest].pri))) {
      largest = left;
    }

    if (right <= q->rear && (q->items[right].at > q->items[largest].at ||
                             (q->items[right].at == q->items[largest].at &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  } else {
    if (left <= q->rear && (q->items[left].at < q->items[largest].at ||
                            (q->items[left].at == q->items[largest].at &&
                             q->items[left].pri < q->items[largest].pri))) {
      largest = left;
    }

    if (right <= q->rear && (q->items[right].at < q->items[largest].at ||
                             (q->items[right].at == q->items[largest].at &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  }

  if (largest != index) {
    swap_procs(&q->items[largest], &q->items[index]);
    heapify_down_atqueue(q, largest);
  }
}

void heapify_down_btqueue(btqueue *q, int index) {
  if (index < 0)
    return;

  int largest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  int largest_bt_remaining = q->items[largest].bt - q->items[largest].sbt;
  int left_bt_remaining = q->items[left].bt - q->items[left].sbt;
  int right_bt_remaining = q->items[right].bt - q->items[right].sbt;

  if (q->order == ASC) {
    if (left <= q->rear && (left_bt_remaining > largest_bt_remaining ||
                            (left_bt_remaining == largest_bt_remaining &&
                             q->items[left].pri < q->items[largest].pri))) {
      largest = left;
      largest_bt_remaining = q->items[largest].bt - q->items[largest].sbt;
    }

    if (right <= q->rear && (right_bt_remaining > largest_bt_remaining ||
                             (right_bt_remaining == largest_bt_remaining &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  } else {
    if (left <= q->rear && (left_bt_remaining < largest_bt_remaining ||
                            (left_bt_remaining == largest_bt_remaining &&
                             q->items[left].pri < q->items[largest].pri))) {
      largest = left;
      largest_bt_remaining = q->items[largest].bt - q->items[largest].sbt;
    }

    if (right <= q->rear && (right_bt_remaining < largest_bt_remaining ||
                             (right_bt_remaining == largest_bt_remaining &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  }

  if (largest != index) {
    swap_procs(&q->items[largest], &q->items[index]);
    heapify_down_btqueue(q, largest);
  }
}

void heapify_down_pqueue(pqueue *q, int index) {
  int largest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  if (q->order == ASC) {
    if (left <= q->rear && (q->items[left].pri < q->items[largest].pri ||
                            (q->items[left].pri == q->items[largest].pri &&
                             q->items[left].at < q->items[largest].at))) {
      largest = left;
    }

    if (right <= q->rear && (q->items[right].pri < q->items[largest].pri ||
                             (q->items[right].pri == q->items[largest].pri &&
                              q->items[right].at < q->items[largest].at))) {
      largest = right;
    }
  } else {
    if (left <= q->rear && (q->items[left].pri > q->items[largest].pri ||
                            (q->items[left].pri == q->items[largest].pri &&
                             q->items[left].at < q->items[largest].at))) {
      largest = left;
    }

    if (right <= q->rear && (q->items[right].pri > q->items[largest].pri ||
                             (q->items[right].pri == q->items[largest].pri &&
                              q->items[right].at < q->items[largest].at))) {
      largest = right;
    }
  }

  if (largest != index) {
    swap_procs(&q->items[largest], &q->items[index]);
    heapify_down_pqueue(q, largest);
  }
}

void heapify_down_rrqueue(rrqueue *q, int index) {
  int largest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  int largest_rr = q->items[largest].wt / q->items[largest].bt;
  int left_rr = q->items[left].wt / q->items[left].bt;
  int right_rr = q->items[right].wt / q->items[right].bt;

  if (q->order == ASC) {
    if (left <= q->rear &&
        (left_rr > largest_rr ||
         (left_rr == largest_rr && q->items[left].at < q->items[largest].at) ||
         (left_rr == largest_rr && q->items[left].at == q->items[largest].at &&
          q->items[left].pri < q->items[largest].pri))) {
      largest = left;
      largest_rr = q->items[largest].wt / q->items[largest].bt;
    }

    if (right <= q->rear && (right_rr > largest_rr ||
                             (right_rr == largest_rr &&
                              q->items[right].at < q->items[largest].at) ||
                             (right_rr == largest_rr &&
                              q->items[right].at == q->items[largest].at &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  } else {
    if (left <= q->rear &&
        (left_rr < largest_rr ||
         (left_rr == largest_rr && q->items[left].at < q->items[largest].at) ||
         (left_rr == largest_rr && q->items[left].at == q->items[largest].at &&
          q->items[left].pri < q->items[largest].pri))) {
      largest = left;
      largest_rr = q->items[largest].wt / q->items[largest].bt;
    }

    if (right <= q->rear && (right_rr < largest_rr ||
                             (right_rr == largest_rr &&
                              q->items[right].at < q->items[largest].at) ||
                             (right_rr == largest_rr &&
                              q->items[right].at == q->items[largest].at &&
                              q->items[right].pri < q->items[largest].pri))) {
      largest = right;
    }
  }

  if (largest != index) {
    swap_procs(&q->items[largest], &q->items[index]);
    heapify_down_rrqueue(q, largest);
  }
}

void heapify_up_atqueue(atqueue *q, int index) {
  if (index < 0)
    return;

  int parent = (index - 1) / 2;

  if (parent < 0 || index == parent)
    return;

  int swap = 0;

  if (q->order == ASC) {
    if ((q->items[index].at > q->items[parent].at ||
         (q->items[index].at == q->items[parent].at &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  } else {
    if ((q->items[index].at < q->items[parent].at ||
         (q->items[index].at == q->items[parent].at &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  }

  if (!swap)
    return;

  swap_procs(&q->items[parent], &q->items[index]);
  heapify_up_atqueue(q, parent);
}

void heapify_up_btqueue(btqueue *q, int index) {
  if (index < 0)
    return;

  int parent = (index - 1) / 2;

  if (parent < 0 || parent == index)
    return;

  int swap = 0;

  int index_bt_remaining = q->items[index].bt - q->items[index].sbt;
  int parent_bt_remaining = q->items[parent].bt - q->items[parent].sbt;

  if (q->order == ASC) {
    if ((index_bt_remaining > parent_bt_remaining ||
         (index_bt_remaining == parent_bt_remaining &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  } else {
    if ((index_bt_remaining < parent_bt_remaining ||
         (index_bt_remaining == parent_bt_remaining &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  }

  if (!swap)
    return;

  swap_procs(&q->items[parent], &q->items[index]);
  heapify_up_btqueue(q, parent);
}

void heapify_up_pqueue(pqueue *q, int index) {
  if (index < 0)
    return;

  int parent = (index - 1) / 2;

  if (parent < 0 || parent == index)
    return;

  int swap = 0;

  if (q->order == ASC) {
    if ((q->items[index].pri < q->items[parent].pri ||
         (q->items[index].pri == q->items[parent].pri &&
          q->items[index].at < q->items[parent].at))) {
      swap = 1;
    }
  } else {
    if ((q->items[index].pri > q->items[parent].pri ||
         (q->items[index].pri == q->items[parent].pri &&
          q->items[index].at < q->items[parent].at))) {
      swap = 1;
    }
  }

  if (!swap)
    return;

  swap_procs(&q->items[parent], &q->items[index]);
  heapify_up_pqueue(q, parent);
}

void heapify_up_rrqueue(rrqueue *q, int index) {
  if (index < 0)
    return;

  int parent = (index - 1) / 2;

  if (parent < 0 || parent == index)
    return;

  int swap = 0;

  int index_rr = q->items[index].wt / q->items[index].bt;
  int parent_rr = q->items[parent].wt / q->items[parent].bt;

  if (q->order == ASC) {
    if ((index_rr > parent_rr ||
         (index_rr == parent_rr && q->items[index].at < q->items[parent].at) ||
         (index_rr == parent_rr && q->items[index].at == q->items[parent].at &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  } else {
    if ((index_rr < parent_rr ||
         (index_rr == parent_rr && q->items[index].at < q->items[parent].at) ||
         (index_rr == parent_rr && q->items[index].at == q->items[parent].at &&
          q->items[index].pri < q->items[parent].pri))) {
      swap = 1;
    }
  }

  if (!swap)
    return;

  swap_procs(&q->items[parent], &q->items[index]);
  heapify_up_rrqueue(q, parent);
}

int atqueue_length(atqueue *q) {
  if (atqueue_is_empty(q))
    return 0;

  return q->rear - q->front + 1;
}

int btqueue_length(btqueue *q) {
  if (btqueue_is_empty(q))
    return 0;

  return q->rear - q->front + 1;
}

int pqueue_length(pqueue *q) {
  if (pqueue_is_empty(q))
    return 0;

  return q->rear - q->front + 1;
}

int rrqueue_length(rrqueue *q) {
  if (rrqueue_is_empty(q))
    return 0;

  return q->rear - q->front + 1;
}

int queue_length(queue *q) {
  if (queue_is_empty(q))
    return 0;

  int gap = q->front - q->rear;

  int len;
  if (gap > 0) {
    len = (q->max - q->front) + q->rear + 1;
  } else {
    len = q->front - q->rear + 1;
  }

  if (len < 0)
    return -len;

  return len;
}

int index_is_in_queue(queue *q, int index) {
  if (queue_is_empty(q))
    return 0;

  int gap = q->front - q->rear;

  if (gap > 0) {
    return (index >= q->front && index <= q->rear + q->max) ||
           (index >= q->front - q->max && index <= q->rear);
  } else {
    return index >= q->front && index <= q->rear;
  }
}

proc *get_sorted_atqueue_elements(atqueue *q, int *len) {
  *len = atqueue_length(q);
  if ((*len) == 0)
    return NULL;

  proc *s = (proc *)malloc(sizeof(proc) * (*len));
  if (s == NULL) {
    *len = -1;
    return NULL;
  }

  atqueue *clone = clone_atqueue(q);
  if (clone == NULL) {
    free(s);
    *len = -1;
    return NULL;
  }

  int i = 0;
  while (!atqueue_is_empty(clone)) {
    proc p;
    if (!at_dequeue(clone, &p)) {
      free(s);
      free_atqueue(clone);
      *len = -1;
      return NULL;
    }
    s[i++] = p;
  }

  free_atqueue(clone);
  return s;
}

proc *get_sorted_btqueue_elements(btqueue *q, int *len) {
  *len = btqueue_length(q);
  if ((*len) == 0)
    return NULL;

  proc *s = (proc *)malloc(sizeof(proc) * (*len));
  if (s == NULL) {
    *len = -1;
    return NULL;
  }

  btqueue *clone = clone_btqueue(q);
  if (clone == NULL) {
    free(s);
    *len = -1;
    return NULL;
  }

  int i = 0;
  while (!btqueue_is_empty(clone)) {
    proc p;
    if (!bt_dequeue(clone, &p)) {
      free(s);
      free_btqueue(clone);
      *len = -1;
      return NULL;
    }
    s[i++] = p;
  }

  free_btqueue(clone);
  return s;
}

proc *get_sorted_pqueue_elements(pqueue *q, int *len) {
  *len = pqueue_length(q);
  if ((*len) == 0)
    return NULL;

  proc *s = (proc *)malloc(sizeof(proc) * (*len));
  if (s == NULL) {
    *len = -1;
    return NULL;
  }

  pqueue *clone = clone_pqueue(q);
  if (clone == NULL) {
    free(s);
    *len = -1;
    return NULL;
  }

  int i = 0;
  while (!pqueue_is_empty(clone)) {
    proc p;
    if (!p_dequeue(clone, &p)) {
      free(s);
      free_pqueue(clone);
      *len = -1;
      return NULL;
    }
    s[i++] = p;
  }

  free_pqueue(clone);
  return s;
}

proc *get_sorted_rrqueue_elements(rrqueue *q, int *len) {
  *len = rrqueue_length(q);
  if ((*len) == 0)
    return NULL;

  proc *s = (proc *)malloc(sizeof(proc) * (*len));
  if (s == NULL) {
    *len = -1;
    return NULL;
  }

  rrqueue *clone = clone_rrqueue(q);
  if (clone == NULL) {
    free(s);
    *len = -1;
    return NULL;
  }

  int i = 0;
  while (!rrqueue_is_empty(clone)) {
    proc p;
    if (!rr_dequeue(clone, &p)) {
      free(s);
      free_rrqueue(clone);
      *len = -1;
      return NULL;
    }
    s[i++] = p;
  }

  free_rrqueue(clone);
  return s;
}

int atqueue_is_full(atqueue *q) { return q->rear == q->max - 1; }

int btqueue_is_full(btqueue *q) { return q->rear == q->max - 1; }

int pqueue_is_full(pqueue *q) { return q->rear == q->max - 1; }

int rrqueue_is_full(rrqueue *q) { return q->rear == q->max - 1; }

int queue_is_full(queue *q) { return (q->rear + 1) % q->max == q->front; }

int atqueue_is_empty(atqueue *q) { return q->front == -1; }

int btqueue_is_empty(btqueue *q) { return q->front == -1; }

int pqueue_is_empty(pqueue *q) { return q->front == -1; }

int rrqueue_is_empty(rrqueue *q) { return q->front == -1; }

int queue_is_empty(queue *q) { return q->front == -1; }

void print_atqueue(atqueue *q) {
  printf("Priority Queue: (Arrival time based) ");

  if (q->order == ASC) {
    printf("Ascending order\n");
  } else {
    printf("Descending order\n");
  }

  printf("   ");

  int len;
  proc *sorted = get_sorted_atqueue_elements(q, &len);

  if (len < 0 && sorted == NULL) {
    fprintf(stderr, "Error: cannot print queue");
    return;
  }

  if (sorted == NULL || len == 0) {
    printf("Empty Queue");
    return;
  }

  for (int i = 0; i < len; i++) {
    print_proc(&sorted[i]);
    printf("   ");
  }
  printf("\n");

  free(sorted);
}

void print_btqueue(btqueue *q) {
  printf("Priority Queue: (Burst time based) ");

  if (q->order == ASC) {
    printf("Ascending order\n");
  } else {
    printf("Descending order\n");
  }

  printf("   ");

  int len;
  proc *sorted = get_sorted_btqueue_elements(q, &len);

  if (len < 0 && sorted == NULL) {
    fprintf(stderr, "Error: cannot print queue");
    return;
  }

  if (sorted == NULL || len == 0) {
    printf("Empty Queue");
    return;
  }

  for (int i = 0; i < len; i++) {
    print_proc(&sorted[i]);
    printf("   ");
  }
  printf("\n");

  free(sorted);
}

void print_pqueue(pqueue *q) {
  printf("Priority Queue: (Priority based) ");

  if (q->order == ASC) {
    printf("Ascending order\n");
  } else {
    printf("Descending order\n");
  }

  printf("   ");

  int len;
  proc *sorted = get_sorted_pqueue_elements(q, &len);

  if (len < 0 && sorted == NULL) {
    fprintf(stderr, "Error: cannot print queue");
    return;
  }

  if (sorted == NULL || len == 0) {
    printf("Empty Queue");
    return;
  }

  for (int i = 0; i < len; i++) {
    print_proc(&sorted[i]);
    printf("   ");
  }
  printf("\n");

  free(sorted);
}

void print_rrqueue(rrqueue *q) {
  printf("Priority Queue: (Response ratio based) ");

  if (q->order == ASC) {
    printf("Ascending order\n");
  } else {
    printf("Descending order\n");
  }

  printf("   ");

  int len;
  proc *sorted = get_sorted_rrqueue_elements(q, &len);

  if (len < 0 && sorted == NULL) {
    fprintf(stderr, "Error: cannot print queue");
    return;
  }

  if (sorted == NULL || len == 0) {
    printf("Empty Queue");
    return;
  }

  for (int i = 0; i < len; i++) {
    print_proc(&sorted[i]);
    printf("   ");
  }
  printf("\n");

  free(sorted);
}

void print_queue(queue *q) {
  printf("Queue: ");
  printf("   ");

  if (queue_is_empty(q)) {
    printf("Empty Queue");
    return;
  }

  queue *clone = clone_queue(q);
  if (clone == NULL) {
    fprintf(stderr, "Error: cannot print queue");
    return;
  }

  proc c;
  while (!queue_is_empty(clone)) {
    if (!dequeue(q, &c)) {
      fprintf(stderr, "Error: cannot print queue");
      return;
    }

    print_proc(&c);
    printf("   ");
  }

  printf("\n");
  free_queue(clone);
}

void free_atqueue(atqueue *q) {
  free(q->items);
  free(q);
}

void free_btqueue(btqueue *q) {
  free(q->items);
  free(q);
}

void free_pqueue(pqueue *q) {
  free(q->items);
  free(q);
}

void free_rrqueue(rrqueue *q) {
  free(q->items);
  free(q);
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
  a->wt = b->wt;
  a->rt = b->rt;
  a->tt = b->tt;
  a->sbt = b->sbt;

  b->pid = temp.pid;
  b->at = temp.at;
  b->bt = temp.bt;
  b->pri = temp.pri;
  b->wt = temp.wt;
  b->rt = temp.rt;
  b->tt = temp.tt;
  b->sbt = temp.sbt;
}
