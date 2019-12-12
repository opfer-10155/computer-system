#include<stdio.h>
typedef struct {
  list_t *prev;
  int val;
} list_t;

typedef struct {
  list_t *body;
  int head;
} queue_t;

list_t *create_list(int val, list_t *prev) {
  list_t *list = malloc(sizeof(list_t));
  list->val = val;
  list->prev = prev;
  return list;
}


list_t *create_list_from_array(int data[], int n) {
  if (n <= 0) return NULL;
  list_t *list = malloc(sizeof(list_t));
  list->val = data[n-1];
  list->prev = create_list(data, n-1);
  return list;
}

void print_list(list_t *list) {
  if (list != NULL) {
    print_list(list->prev);
    printf("%d ", list->val);
  }
}

queue_t *create_queue(int head, list_t *body) {
  queue_t *queue = malloc(sizeof(queue_t));
  queue->head = head;
  queue->body = body;
  return queue;
}

void print_queue(queue_t *queue) {
  printf("head -> ");
  printf("%d", queue->head);
  list_t *body = queue->body;
  print_list(body);
  printf("<- tail");
}

queue_t *enqueue(int x) {

}

int dequeue() {

}



int main() {

}
