#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ATHLETES 100

typedef struct {
    char name[50];
    float distance;
} Athlete;

int compare(const void *a, const void *b) {
    float diff = ((Athlete*)b)->distance - ((Athlete*)a)->distance;
    return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}

int main() {
    Athlete athletes[MAX_ATHLETES];
    int count = 0;
    char name[50];
    float distance;
    while (scanf("%s %f", name, &distance) != EOF) {
        strcpy(athletes[count].name, name);
        athletes[count].distance = distance;
        count++;
    }
    qsort(athletes, count, sizeof(Athlete), compare);
    printf("\nAthlete Rankings (Sorted by Distance):\n");
    for (int i = 0; i < count; i++) {
        printf("%s %.2f\n", athletes[i].name, athletes[i].distance);
    }
    return 0;
}
