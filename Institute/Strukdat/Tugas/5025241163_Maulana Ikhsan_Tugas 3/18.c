#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct Stack{
    int top;
    unsigned capacity;
    int* array;
};

void init(struct Stack* stack, unsigned capacity){
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
}

bool isFull(struct Stack* stack){
    return stack->top == stack->capacity - 1;
}

bool isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, int item){
    if(isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

int peek(struct Stack* stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top];
}

void sort(struct Stack* stack1, struct Stack* stack2){
    int temp;
    while(!isEmpty(stack1)){
        temp = pop(stack1);
        while(!isEmpty(stack2) && peek(stack2) < temp){
            push(stack1, pop(stack2));
        }
        push(stack2, temp);
    }
    while(!isEmpty(stack2)){
        push(stack1, pop(stack2));
    }
}

void print(struct Stack* stack){
    for(int i=0; i<=stack->top; i++){
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main(){
int n, inp;
printf("How much number : "); scanf("%d", &n);
struct Stack stack1, stack2;
init(&stack1, n); init(&stack2, n);
for(int i=0; i<n; i++){
    scanf("%d", &inp);
    push(&stack1, inp);
}
sort(&stack1, &stack2);
printf("Sorted : "); print(&stack1);
return 0;
}