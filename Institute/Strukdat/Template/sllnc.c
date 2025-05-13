#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;

bool isempty(LinkedList* list) {
    return list->head == NULL;
}

void pushback(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

void pushfront(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

bool insertat(LinkedList* list, int index, int data) {
    if (index < 0) return false;
    if (index == 0) {
        pushfront(list, data);
        return true;
    }
    Node* temp = list->head;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return false;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;
    return true;
}

bool getback(LinkedList* list, int* out) {
    if (list->head == NULL) return false;
    Node* temp = list->head;
    while (temp->next != NULL) temp = temp->next;
    *out = temp->data;
    return true;
}

bool getfront(LinkedList* list, int* out) {
    if (list->head == NULL) return false;
    *out = list->head->data;
    return true;
}

bool getat(LinkedList* list, int index, int* out) {
    if (index < 0) return false;
    Node* temp = list->head;
    for (int i = 0; temp != NULL && i < index; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return false;
    *out = temp->data;
    return true;
}

bool popback(LinkedList* list, int* out) {
    if (list->head == NULL) return false;
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (out) *out = temp->data;
    if (prev == NULL) {
        list->head = NULL;
    } else {
        prev->next = NULL;
    }
    free(temp);
    return true;
}

bool popfront(LinkedList* list, int* out) {
    if (list->head == NULL) return false;
    Node* temp = list->head;
    if (out) *out = temp->data;
    list->head = temp->next;
    free(temp);
    return true;
}

bool remove_node(LinkedList* list, int x) {
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != x) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return false;
    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    return true;
}

void display(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
}

int main() {
    return 0;
}