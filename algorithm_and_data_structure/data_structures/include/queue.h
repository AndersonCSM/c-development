#ifndef QUEUE_H
#define QUEUE_H

// Typedef para função callback
typedef void (*QueueCallback)(int data);

typedef struct Node
{
    int data;
    struct Node *sucessor;
} Node;

typedef struct Queue
{
    Node *front;
    Node *tail;
} Queue;

// Protótipos
void queue_init(Queue *queue);
int queue_is_empty(Queue *queue);

void queue_enqueue(Queue *queue, int value);
int queue_dequeue(Queue *queue);

int queue_front(Queue *queue);
void queue_display(Queue *queue);

void queue_apply(Queue *queue, QueueCallback callback);
int queue_find(Queue *queue, int value);
void queue_destroy(Queue *queue);

#endif