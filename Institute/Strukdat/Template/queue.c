#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int count;
} Queue;

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
}

bool isempty(Queue* queue) {
    return queue->front == NULL;
}

int size(Queue* queue) {
    return queue->count;
}

void enqueue(Queue* queue, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (isempty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->count++;
}

bool dequeue(Queue* queue, int* out) {
    if (isempty(queue)) return false;
    QueueNode* temp = queue->front;
    if (out) *out = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    queue->count--;
    return true;
}

bool peek(Queue* queue, int* out) {
    if (isempty(queue)) return false;
    *out = queue->front->data;
    return true;
}

void freeQueue(Queue* queue) {
    while (!isempty(queue)) {
        QueueNode* temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
    queue->rear = NULL;
    queue->count = 0;
}

int main() {
    return 0;
}