#include<stdio.h>
#include<stdlib.h>

typedef struct list_t{
  int val;
  struct list_t *next;
} list_t;

typedef struct {
  list_t *head;
  list_t *tail;
} queue_t;


queue_t *create_queue(list_t *head, list_t *tail);
queue_t *create_empty_queue();
void destroy_queue(queue_t *queue);
void print_queue(queue_t *queue);
void enqueue(queue_t *queue, int x);
int dequeue(queue_t *queue);


int main() {
  int n;
  scanf("%d", &n);
  // int *array = malloc(sizeof(int) * n);
  queue_t *queue = create_empty_queue();
  for (int i=0; i < n; i++) {
    int x;
    scanf("%d", &x);
    enqueue(queue, x);
  }

  puts("initial queue");
  print_queue(queue); puts("\n");

  enqueue(queue, 100);
  printf("[enqueue] %d -> queue\n", 100);
  print_queue(queue); puts("\n");

  printf("[dequeue] %d <- queue\n", dequeue(queue));
  print_queue(queue); puts("");


  destroy_queue(queue);

  return 0;
}


list_t *create_list(int val, list_t *next) {
  list_t *list = malloc(sizeof(list_t));
  list->val = val;
  list->next = next;
  return list;
}

list_t *add_list(list_t *list, int x) {
  return create_list(x, list);
}


list_t *create_list_from_array(int *data, int n) {
  if (n <= 0) return NULL;
  list_t *list = malloc(sizeof(list_t));
  list->val = data[0];
  list->next = create_list_from_array(data+1, n-1);
  return list;
}

void print_list(list_t *list) {
  if (list != NULL) {
    print_list(list->next);
    printf("%d ", list->val);
  }
}

queue_t *create_queue(list_t *head, list_t *tail) {
  queue_t *queue = malloc(sizeof(queue_t));
  queue->head = head;
  queue->tail = tail;
  return queue;
}

queue_t *create_empty_queue() {
  return create_queue(NULL, NULL);
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

void print_queue(queue_t *queue) {
  printf("HEAD -> ");
  if (queue != NULL && queue->head != NULL) {
    list_t *head = queue->head;
    list_t *tail = queue->tail;
    while(1) {
      printf("%d ", head->val);
      if (head->next == NULL || head == tail) break;
      head = head->next;
    }
  }
  else {
    printf("empty!");
  }
  printf("<- TAIL");
}

void enqueue(queue_t *queue, int x) {
  if (queue == NULL) {
    *queue = *create_empty_queue();
  }
  list_t *new_tail = create_list(x, NULL);
  if (queue->head == NULL) {
    queue->head = new_tail;
  }
  if (queue->tail == NULL) {
    queue->tail = new_tail;
  }
  else {
    queue->tail->next = new_tail;
    queue->tail = new_tail;
  }
}


int dequeue(queue_t *queue) {
  if (queue == NULL || queue->head == NULL) {
    fprintf(stderr, "[ERROR] you can't dequeue empty queue.\n");
    exit(1);
  }
  int val = queue->head->val;
  queue->head = queue->head->next;
  return val;
}

void destroy_queue(queue_t *queue) {
  list_t *head = queue->head;
  list_t *tail = queue->tail;
  if (queue != NULL) {
    while(1) {
      if (head == NULL) break;
      free(head);
      if (head == tail) break;
      head = head->next;
    }
  }
}
