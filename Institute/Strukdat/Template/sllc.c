#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularList {
    Node* head;
    Node* tail;
} CircularList;

void initList(CircularList* list) {
    list->head = NULL;
    list->tail = NULL;
}

bool isempty(CircularList* list) {
    return list->head == NULL;
}

void pushback(CircularList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (isempty(list)) {
        newNode->next = newNode;
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void pushfront(CircularList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (isempty(list)) {
        newNode->next = newNode;
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->head = newNode;
    }
}

bool insertat(CircularList* list, int index, int data) {
    if (index < 0) return false;
    if (index == 0) {
        pushfront(list, data);
        return true;
    }
    if (isempty(list)) return false;
    Node* temp = list->head;
    for (int i = 0; i < index - 1 && temp->next != list->head; i++) {
        temp = temp->next;
    }
    if (temp == list->tail && index > 1) return false;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;
    if (temp == list->tail) list->tail = newNode;
    return true;
}

bool getback(CircularList* list, int* out) {
    if (isempty(list)) return false;
    *out = list->tail->data;
    return true;
}

bool getfront(CircularList* list, int* out) {
    if (isempty(list)) return false;
    *out = list->head->data;
    return true;
}

bool getat(CircularList* list, int index, int* out) {
    if (isempty(list) || index < 0) return false;
    Node* temp = list->head;
    int i = 0;
    do {
        if (i == index) {
            *out = temp->data;
            return true;
        }
        temp = temp->next;
        i++;
    } while (temp != list->head);
    return false;
}

bool popback(CircularList* list, int* out) {
    if (isempty(list)) return false;
    Node* temp = list->head;
    if (list->head == list->tail) {
        if (out) *out = temp->data;
        free(temp);
        list->head = list->tail = NULL;
        return true;
    }
    while (temp->next != list->tail) temp = temp->next;
    if (out) *out = list->tail->data;
    free(list->tail);
    temp->next = list->head;
    list->tail = temp;
    return true;
}

bool popfront(CircularList* list, int* out) {
    if (isempty(list)) return false;
    Node* temp = list->head;
    if (list->head == list->tail) {
        if (out) *out = temp->data;
        free(temp);
        list->head = list->tail = NULL;
        return true;
    }
    if (out) *out = temp->data;
    list->head = temp->next;
    list->tail->next = list->head;
    free(temp);
    return true;
}

bool remove_node(CircularList* list, int x) {
    if (isempty(list)) return false;
    Node* curr = list->head;
    Node* prev = list->tail;
    do {
        if (curr->data == x) {
            if (curr == list->head) {
                popfront(list, NULL);
            } else if (curr == list->tail) {
                popback(list, NULL);
            } else {
                prev->next = curr->next;
                free(curr);
            }
            return true;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != list->head);
    return false;
}

void display(CircularList* list) {
    if (isempty(list)) {
        printf("List is empty\n");
        return;
    }
    Node* temp = list->head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != list->head);
    printf("(head)\n");
}

void freeList(CircularList* list) {
    if (isempty(list)) return;
    Node* curr = list->head;
    Node* next;
    do {
        next = curr->next;
        free(curr);
        curr = next;
    } while (curr != list->head);
    list->head = list->tail = NULL;
}

int main() {
    return 0;
}