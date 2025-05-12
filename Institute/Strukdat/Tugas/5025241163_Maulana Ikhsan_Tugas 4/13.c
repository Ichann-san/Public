#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<ctype.h>
#define swapstruct(a,b) {struct Job t=a;a=b;b=t;}

struct Job {
    int id, priority;
};

struct Pq {
    struct Job *data;
    int size, capacity;
};

void init(struct Pq *pq, int capacity) {
    pq->data = (struct Job *)malloc(capacity * sizeof(struct Job));
    pq->size = 0;
    pq->capacity = capacity;
}

void heapup(struct Pq *pq, int index){//max value pq
    while(index > 0){
        int head = (index-1)/2;
        if(pq->data[index].priority > pq->data[head].priority){//ini buat min max
            swapstruct(pq->data[index], pq->data[head]);
            index = head;
        } else {
            break;
        }
    }
}

void heapdown(struct Pq *pq, int index){//max value pq
    while(index < pq->size){
        int left  = index*2+1;
        int right = index*2+2;
        int temp = index;
        if(left < pq->size && pq->data[left].priority > pq->data[temp].priority) temp=left;//min max kiri
        if(right < pq->size && pq->data[right].priority > pq->data[temp].priority) temp=right;//min max kanan
        if(temp != index){//full swap sampe sama
            swapstruct(pq->data[index], pq->data[temp]);
            index=temp;
        } else {
            break;
        }
    }
}


void enqueue(struct Pq *pq, int job, int prio) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = (struct Job *)realloc(pq->data, pq->capacity * sizeof(struct Job));
    }
    pq->data[pq->size].id = job;
    pq->data[pq->size].priority = prio;
    heapup(pq, pq->size);
    pq->size++;
}

void dequeue(struct Pq *pq) {
    if (pq->size == 0) return;
    pq->data[0] = pq->data[--pq->size];
    heapdown(pq, 0);
}

void top(struct Pq *pq) {
    printf("%d %d\n", pq->data[0].id, pq->data[0].priority);
}

void removejob(struct Pq *pq, int job) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->data[i].id == job) {
            printf("%d %d ", pq->data[i].id, pq->data[i].priority);
            pq->data[i] = pq->data[--pq->size];
            heapdown(pq, i);
            break;
        }
    }
}

int main(){
struct Pq pq;
int n, id, prio, target;
printf("size : "); scanf("%d", &n);
init(&pq, n);
printf("Job  Prio\n");
for(int i=0; i<n; i++){
    scanf("%d %d", &id, &prio);
    enqueue(&pq, id, prio);
}
printf("\npq ordered(ini index nya ga kesusun tapi tree nya udah kesusun\n");
for(int i=0; i<pq.size; i++){
    printf("%d %d\n", pq.data[i].id, pq.data[i].priority);
}

printf("\ntarget : "); scanf("%d", &target);
removejob(&pq, target);

printf("\nsisa pq\n");
while(pq.size > 0){
    top(&pq);
    dequeue(&pq);
}
free(pq.data);
printf("\n");
return 0;
}