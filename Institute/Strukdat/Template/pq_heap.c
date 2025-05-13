#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE 1000

typedef struct {
    int data;
    int priority;
} HeapNode;

typedef struct {
    HeapNode arr[MAX_HEAP_SIZE];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue* pq) {
    pq->size = 0;
}

bool isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int idx) {(max pq, ganti tanda kalo mau min)
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (pq->arr[parent].priority < pq->arr[idx].priority) {
            swap(&pq->arr[parent], &pq->arr[idx]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(PriorityQueue* pq, int idx) {
    int left, right, largest;
    while (1) {
        left = 2 * idx + 1;
        right = 2 * idx + 2;
        largest = idx;

        if (left < pq->size && pq->arr[left].priority > pq->arr[largest].priority)
            largest = left;
        if (right < pq->size && pq->arr[right].priority > pq->arr[largest].priority)
            largest = right;

        if (largest != idx) {
            swap(&pq->arr[idx], &pq->arr[largest]);
            idx = largest;
        } else {
            break;
        }
    }
}

void push(PriorityQueue* pq, int data, int priority) {
    if (pq->size >= MAX_HEAP_SIZE) return;
    pq->arr[pq->size].data = data;
    pq->arr[pq->size].priority = priority;
    heapifyUp(pq, pq->size);
    pq->size++;
}

bool pop(PriorityQueue* pq, int* out) {
    if (isEmpty(pq)) return false;
    if (out) *out = pq->arr[0].data;
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return true;
}

bool top(PriorityQueue* pq, int* out) {
    if (isEmpty(pq)) return false;
    *out = pq->arr[0].data;
    return true;
}

int main() {
    return 0;
}