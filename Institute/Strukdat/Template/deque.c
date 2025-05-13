#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DequeNode {
    int data;
    struct DequeNode* next;
    struct DequeNode* prev;
} DequeNode;

typedef struct Deque {
    DequeNode* front;
    DequeNode* back;
    int count;
} Deque;

void initDeque(Deque* dq) {
    dq->front = NULL;
    dq->back = NULL;
    dq->count = 0;
}

bool isEmpty(Deque* dq) {
    return dq->front == NULL;
}

void pushFront(Deque* dq, int data) {
    DequeNode* newNode = (DequeNode*)malloc(sizeof(DequeNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = dq->front;
    if (isEmpty(dq)) {
        dq->front = dq->back = newNode;
    } else {
        dq->front->prev = newNode;
        dq->front = newNode;
    }
    dq->count++;
}

void pushBack(Deque* dq, int data) {
    DequeNode* newNode = (DequeNode*)malloc(sizeof(DequeNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = dq->back;
    if (isEmpty(dq)) {
        dq->front = dq->back = newNode;
    } else {
        dq->back->next = newNode;
        dq->back = newNode;
    }
    dq->count++;
}

bool front(Deque* dq, int* out) {
    if (isEmpty(dq)) return false;
    *out = dq->front->data;
    return true;
}

bool back(Deque* dq, int* out) {
    if (isEmpty(dq)) return false;
    *out = dq->back->data;
    return true;
}

bool popFront(Deque* dq, int* out) {
    if (isEmpty(dq)) return false;
    DequeNode* temp = dq->front;
    if (out) *out = temp->data;
    dq->front = temp->next;
    if (dq->front) dq->front->prev = NULL;
    else dq->back = NULL;
    free(temp);
    dq->count--;
    return true;
}

bool popBack(Deque* dq, int* out) {
    if (isEmpty(dq)) return false;
    DequeNode* temp = dq->back;
    if (out) *out = temp->data;
    dq->back = temp->prev;
    if (dq->back) dq->back->next = NULL;
    else dq->front = NULL;
    free(temp);
    dq->count--;
    return true;
}

void freeDeque(Deque* dq) {
    while (!isEmpty(dq)) {
        DequeNode* temp = dq->front;
        dq->front = temp->next;
        free(temp);
    }
    dq->back = NULL;
    dq->count = 0;
}

int main() {
    return 0;
}