#include<stdio.h>

typedef struct {
  int val;
  list_t *next;
} list_t;

typedef struct {
  list_t *head;
  list_t *tail;
} queue_t;

queue_t *create_queue(list_t *head, list_t *tail) {
  queue_t *queue = malloc(sizeof(queue_t));
  queue->head = head;
  queue->tail = tail;
  return queue;
}

queue_t *create_queue_from_list(list_t *data) {
  list_t *head = data;
  list_t *tail = head;
  // tailの次がNULLになるまでtailを更新しながらたどる
  while(1) {
    if (tail->next == NULL) break;
    else tail = tail->next;
  }
  return create_queue(head, tail);
}

list_t *create_list(int val, list_t *next) {
  list_t *list = malloc(sizeof(list_t));
  list->val  = val;
  list->next = next;
  return list;
}

// 副作用がないほう
queue_t *enqueue(queue_t *queue, int x) {
  list_t *head = queue->head;
  
  list_t *new_tail = create_list(x, NULL);
  queue->tail  = new_tail;
  return create_queue(head, tail);
}

// 副作用があるほう
void enqueue(queue_t *queue, int x) {
  queue->tail = create_list(queue->tail, x, NULL);
}

// 副作用があるほう
int dequeue(queue_t *queue) {
  int val = queue->head->val;
  queue->head = queue->head->next;
  return val;
}

// 副作用がないほう
int get_queue(queue_t *queue) {
  return queue->head->val;
}

int pop_queue(queue_t *queue) {
  return create_queue(queue->head->next, queue->tail);
}

void print_queue(queue_t *queue) {
  list_t *head = queue->head;

  printf("HEAD -> ");
  while(1) {
    printf("%d ", head->val);
    if (head->next == NULL || head == tail) break;
    head = head->next;
  }
  printf("<- TAIL");
}
