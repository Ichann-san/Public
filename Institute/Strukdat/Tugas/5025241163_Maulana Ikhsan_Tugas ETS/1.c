#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int dx;
    int dy;
} Point;

struct Stack {
    int top;
    unsigned capacity;
    Point* array;
};

void init(struct Stack* stack, unsigned capacity) {
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Point*)malloc(stack->capacity * sizeof(Point));
}

bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, Point item) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = item;
}

Point pop(struct Stack* stack) {
    Point empty = {0, 0};
    if (isEmpty(stack)) return empty;
    return stack->array[stack->top--];
}

int main() {
    char command[1000];
    printf("Input gerakan: ");
    scanf("%s", command);

    struct Stack stack;
    init(&stack, 1000); 
    
    int x = 0, y = 0;
    Point delta;

    for (int i = 0; command[i] != '\0'; i++) {
        char c = command[i];
        if (c == 'U') {
            y += 1;
            delta.dx = 0;
            delta.dy = -1;
            push(&stack, delta);
        } else if (c == 'D') {
            y -= 1;
            delta.dx = 0;
            delta.dy = 1;
            push(&stack, delta);
        } else if (c == 'L') {
            x -= 1;
            delta.dx = 1;
            delta.dy = 0;
            push(&stack, delta);
        } else if (c == 'R') {
            x += 1;
            delta.dx = -1;
            delta.dy = 0;
            push(&stack, delta);
        } else if (c == 'B') {
            if (!isEmpty(&stack)) {
                Point undo = pop(&stack);
                x += undo.dx;
                y += undo.dy;
            }
        }
    }

    printf("Posisi akhir robot: (%d, %d)\n", x, y);
    free(stack.array);
    return 0;
}