#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STALLS 100

typedef struct {
    char name[50];
    float income;
    float expenses;
    float net_income;
} Stall;

int compare(const void *a, const void *b) {
    return ((Stall*)b)->net_income - ((Stall*)a)->net_income;
}

int main() {
    Stall stalls[MAX_STALLS];
    int count = 0;
    float total_profit = 0;
    char name[50];
    float income, expenses;
    while (1) {
        scanf("%s", name);
        if (strcmp(name, "xxxxxx") == 0) break;
        scanf("%f %f", &income, &expenses);
        
        strcpy(stalls[count].name, name);
        stalls[count].income = income;
        stalls[count].expenses = expenses;
        stalls[count].net_income = income - expenses;
        total_profit += stalls[count].net_income;
        count++;
    }

    qsort(stalls, count, sizeof(Stall), compare);
    printf("\nStall Report (Sorted by Net Income):\n");
    for (int i = 0; i < count; i++) {
        printf("%s %.2f\n", stalls[i].name, stalls[i].net_income);
    }
    printf("\nTotal stalls: %d\n", count);
    printf("Total profit/loss: %.2f\n", total_profit);
    float max_profit = stalls[0].net_income;
    printf("Stall(s) with highest profit:\n");
    for (int i = 0; i < count; i++) {
        if (stalls[i].net_income == max_profit) {
            printf("%s\n", stalls[i].name);
        }
    }
    return 0;
}