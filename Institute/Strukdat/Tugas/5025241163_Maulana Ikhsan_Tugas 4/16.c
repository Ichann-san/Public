#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

struct Stack{
    int top, size;
    int *arr;
};

struct Queue{
    struct Stack s1, s2;
};

void initStack(struct Stack *s, int size){
    s->top = -1;
    s->size = size;
    s->arr = (int *)malloc(size * sizeof(int));
}

bool isFull(struct Stack *s){
    return s->top == s->size - 1;
}

bool isEmpty(struct Stack *s){
    return s->top == -1;
}

void push(struct Stack *s, int data){
    if(isFull(s)) return;
    s->arr[++s->top] = data;
}

int pop(struct Stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top--];
}

void initq(struct Queue *q, int size){
    initStack(&q->s1, size);
    initStack(&q->s2, size);
}

void enqueue(struct Queue *q, int data){
    push(&q->s1, data);
}

int dequeue(struct Queue *q){
    int x;
    if(isEmpty(&q->s2)){
        while(!isEmpty(&q->s1)){
            push(&q->s2, pop(&q->s1));
        }
    }
    x = pop(&q->s2);
    while(!isEmpty(&q->s2)){
        push(&q->s1, pop(&q->s2));
    }
    return x;
}

void display(struct Queue *q){
    for(int i = 0; i <= q->s1.top; i++){
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}

int main(){
struct Queue q;
int n, x, opt;
printf("Size : "); scanf("%d", &n);
initq(&q, n);
for(int i = 0; i < n; i++){
    scanf("%d", &x);
    enqueue(&q, x);
}
do {
    printf("\n1. Dequeue\n2. Display\n3. Exit\nOption : ");
    scanf("%d", &opt);
    switch(opt){
        case 1:
            x = dequeue(&q);
            if(x == -1) printf("Queue empty\n");
            else printf("Dequeued : %d\n", x);
            break;
        case 2:
            display(&q);
            break;
        case 3:
            break;
        default:
            printf("Invalid option\n");
    }
} while (opt != 3);
printf("\nExiting...\n");
return 0;
}