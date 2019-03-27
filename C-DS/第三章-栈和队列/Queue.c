#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef struct Node
{
  int value;
  struct Node* next;
}Node;
typedef struct Queue
{
  Node* head;
  Node* last;
}Queue;
void QInit(Queue* q)
{
  assert(q != NULL);
  q->head = NULL;
  q->last = NULL;
}
void QPush(Queue* q, int v)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = v;
  node->next = NULL;
  if(q->head == NULL)
  {
    q->head = node;
  }
  else
  {
    q->last->next = node;
    q->last = node;
  }
}
void QPop(Queue* q)
{
  assert(q != NULL);
  assert(q->head != NULL);
  Node* head = q->head;
  q->head = q->head->next;
  free(head);
}
int QFront(Queue* q)
{
  assert(q != null);
  return q->head->value;
}
int QSize(Queue* q)
{
  Node* node = q->head;
  int size = 0;
  while(node != NULL)
  {
    size++;
    node = node->next;
  }
  return size;
}
int QEmpty(Queue* q)
{
  if(q->head == NULL)
  {
    return 1;
  }
  return 0;
}
