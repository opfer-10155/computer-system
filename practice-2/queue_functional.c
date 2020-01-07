// 副作用がないほう
queue_t *enqueue(queue_t *queue, int x) {
  list_t *head = queue->head;

  list_t *new_tail = create_list(x, NULL);
  queue->tail  = new_tail;
  return create_queue(head, new_tail);
}

// 副作用がないほう
int get_queue(queue_t *queue) {
  return queue->head->val;
}

int pop_queue(queue_t *queue) {
  return create_queue(queue->head->next, queue->tail);
}