#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<ctype.h>

struct Queue{
    int front, size, capacity;
    int *array;
};

int find(struct Queue *q, int item){//ini nyari elemen
    for(int i=0; i<q->size; i++){
        if(q->array[(q->front + i) % q->capacity] == item){
            return i;
        }
    }
    return -1;
}

void edit(struct Queue *q, int num, int index){//ini ngubah eemen, pakenya index
    if(index < 0 || index >= q->size) return;
    q->array[(q->front + index) % q->capacity] = num;
}

int main(){

return 0;
}