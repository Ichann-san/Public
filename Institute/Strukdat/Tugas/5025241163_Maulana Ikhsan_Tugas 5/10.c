#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void postOrder(int num[], int index, int size) {
    if (index > size) return;
    postOrder(num, 2*index, size);
    postOrder(num, 2*index + 1, size);
    printf("%d ", num[index]);
}

int main(){

return 0;
}