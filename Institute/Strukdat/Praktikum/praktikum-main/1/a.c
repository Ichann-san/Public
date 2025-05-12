#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct node{
    char data;
    struct node* next;
};

struct Stack{
    int top;
    unsigned capacity;
    char* array;
};

void init(struct Stack* stack, unsigned capacity){
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
}

bool isFull(struct Stack* stack){
    return stack->top == stack->capacity - 1;
}

bool isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, char item){
    if(isFull(stack)) return;
    stack->array[++stack->top] = item;//array di bagian top = item, gini maksudnya
}

char pop(struct Stack* stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top--];//return array di bagian top, lalu top di decrement
}

char peek(struct Stack* stack){
    if(isEmpty(stack)) return -1;
    return stack->array[stack->top];//return array di bagian top
}

void print(struct Stack* stack){
    for(int i=0; i<=stack->top; i++){
        printf("%c ", stack->array[i]);
    }
    printf("\n");
}

int main(){
char n[101];
int len=0;
scanf("%s", &n);
for(int i=0; i<strlen(n); i++){
    if(n[i]=='a' || n[i]=='i' || n[i]=='u' || n[i]=='e' || n[i]=='o' || n[i]=='A' || n[i]=='I' || n[i]=='U' || n[i]=='E' || n[i]=='O'){
        len++;
    }
}
struct Stack* kata = (struct Stack*)malloc(sizeof(struct Stack));
init(kata, strlen(n)+len);
for(int i=0; i<strlen(n); i++){
    push(kata, n[i]);
    if(n[i]=='a' || n[i]=='i' || n[i]=='u' || n[i]=='e' || n[i]=='o' || n[i]=='A' || n[i]=='I' || n[i]=='U' || n[i]=='E' || n[i]=='O'){
        push(kata, n[i]);
    }
}
while(!isEmpty(kata)){
    printf("%c", pop(kata));
}
printf("\n");
return 0;
}