#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node* next;
};

struct Pq{
    struct Node *top;
    unsigned capacity;
};

void init(struct Pq* pq, unsigned capacity){
    pq->capacity = capacity;
    pq->top = NULL;
}


bool isEmpty(struct Pq* pq){
    return pq->top == NULL;
}

struct Node *createnode(int data) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(struct Pq* pq, int item){//pq push acending, liat tanda kalo mau ubah ke desc
    struct Node *temp = pq->top;
    struct Node *new_node = createnode(item);
    if(isEmpty(pq)){
        pq->top = new_node;
        return;
    }
    if(item > pq->top->data){//ini
        new_node->next = pq->top;
        pq->top = new_node;
        return;
    } else {
        while(temp->next != NULL && temp->next->data > item){//ama ini
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

void pop(struct Pq* pq){
    if(isEmpty(pq)){
        return;
    }
    struct Node *temp = pq->top;
    pq->top = pq->top->next;
    free(temp);
}

void print(struct Pq* pq){
    for(struct Node *temp = pq->top; temp != NULL; temp = temp->next){
        printf("%d ", temp->data);
    }
}

int convert(char berat[]){
    int x = 0, y;
    for(int i=0; berat[i] != '\0'; i++){
        switch(berat[i]){
            case ')':
                y = 0;
                break;
            case '!':
                y = 1;
                break;
            case '@':   
                y = 2;
                break;
            case '#':
                y = 3;
                break;
            case '$':
                y = 4;
                break;
            case '%':
                y = 5;
                break;
            case '^':
                y = 6;
                break;
            case '&':   
                y = 7;
                break;
            case '*':
                y = 8;
                break;
            case '(':
                y = 9;
                break;
        }
        x = x * 10 + y;
    }
    return x;
}

int main(){
int n, m;
char berat[6];
scanf("%d%d", &n, &m);
struct Pq pq;
init(&pq, n);
for(int i=0; i<n; i++){
    scanf("%s", berat);
    int x = convert(berat);
    if(x>m) {printf("\n"); continue;}
    push(&pq, x);
    if(!isEmpty(&pq) && pq.top->data == m){
        while(!isEmpty(&pq) && pq.top->data == m){
            printf("%d ", pq.top->data);
            m--;
            pop(&pq);
        }
    }
    printf("\n");
}
// while(!isEmpty(&pq)){
//     printf("%d ", pq.top->data);
//     pop(&pq);
// }
return 0;
}