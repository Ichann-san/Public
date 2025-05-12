#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node {
    int data;
    struct node* next;
};

struct q {
    struct node* front;
    struct node* rear;
    int size;
};

bool isEmpty(struct q* queue) {
    return queue->size == 0;
}

void init(struct q* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void push(struct q* queue, int item) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = item;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front =  queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

void pop(struct q* queue) {
    if (isEmpty(queue)) return;
    struct node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
}

int peek(struct q* queue) {
    if (isEmpty(queue)) return -1;
    return queue->front->data;
}

int main(){
    int x, y, z, n, a, b;
    struct q queue;
    init(&queue);
    scanf("%d%d%d", &x, &y, &z);
    for(int i=0; i<x; i++){
        scanf("%d", &n);
        push(&queue, n);
    }
    struct node* cur = queue.front;
    while(cur != NULL) {
        if(y > cur->data) {
            a++;
            y -= cur->data;
        }
        if(y >= z) {
            b++;
        }
        cur = cur->next;
    }
    printf("%d ", b-(b==x));
    if(a == x) printf("Yes Dapat burger gratis!!!\n");
    else printf("NOO tidak Dapat :(\n");
    return 0;
}