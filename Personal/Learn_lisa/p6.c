#include<stdio.h>

int main(){
    int x, j=0, i=0;
    scanf("%d", &x);

      while(i<x){
        j=0;
         while(j<=i){
            printf("*");
            j++;
        }
        printf("\n");
        i++;
    }
return 0;
}