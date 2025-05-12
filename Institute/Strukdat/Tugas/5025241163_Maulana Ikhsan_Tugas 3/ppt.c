#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct Stack{
    int top;
    unsigned capacity;
    int* array;
};

int search(struct Stack* stack, int item){//ini nyari
    for(int i=0; i<=stack->top; i++){
        if(stack->array[i] == item) return i;
    }
    return -1;
}

void edit_elemen(struct Stack* stack, int index, int new_elemen){//ini ngedit elemen
    stack->array[index] = new_elemen;
}