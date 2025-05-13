#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PQNode {
    int data;
    int priority;
    struct PQNode* next;
} PQNode;

typedef struct PriorityQueue {
    PQNode* head;
} PriorityQueue;

void initPQ(PriorityQueue* pq) {
    pq->head = NULL;
}

bool isEmpty(PriorityQueue* pq) {
    return pq->head == NULL;
}

void push(PriorityQueue* pq, int data, int priority) {(max pq, ganti tanda kalo mau min)
    PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (isEmpty(pq) || pq->head->priority < priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        PQNode* temp = pq->head;
        while (temp->next && temp->next->priority >= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

bool pop(PriorityQueue* pq, int* out) {
    if (isEmpty(pq)) return false;
    PQNode* temp = pq->head;
    if (out) *out = temp->data;
    pq->head = temp->next;
    free(temp);
    return true;
}

bool top(PriorityQueue* pq, int* out) {
    if (isEmpty(pq)) return false;
    *out = pq->head->data;
    return true;
}

void freePQ(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        PQNode* temp = pq->head;
        pq->head = temp->next;
        free(temp);
    }
}

int main() {
    return 0;
}