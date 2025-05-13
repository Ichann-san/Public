#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
    int count;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
    stack->count = 0;
}

bool isempty(Stack* stack) {
    return stack->top == NULL;
}

int size(Stack* stack) {
    return stack->count;
}

void push(Stack* stack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

bool pop(Stack* stack, int* out) {
    if (isempty(stack)) return false;
    StackNode* temp = stack->top;
    if (out) *out = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->count--;
    return true;
}

bool peek(Stack* stack, int* out) {
    if (isempty(stack)) return false;
    *out = stack->top->data;
    return true;
}

void freeStack(Stack* stack) {
    while (!isempty(stack)) {
        StackNode* temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    stack->count = 0;
}

int main() {
    return 0;
}