#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *push(struct Node *head, int new_data) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = head;
    head = new_node;
    return head;
}

struct Node *createnode(int data) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

struct Node *append(struct Node *head, int new_data) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    struct Node *last = head;
    new_node->data = new_data;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
        return head;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    return head;
}

struct Node *insert(struct Node *head, int new_data, int position) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->data = new_data;

    if (position == 0) {
        new_node->next = head;
        head = new_node;
        return head;
    }

    struct Node *temp = head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Keluar batas\n");
        free(new_node);
        return head;
    }

    new_node->next = temp->next;
    temp->next = new_node;
    return head;
}

struct Node *reverse(struct Node *head) {
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

struct Node *pop(struct Node *head) {
    if (head == NULL) {
        return head;
    }
    struct Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node *deletepos(struct Node *head, int position) {
    if (head == NULL) {
        return head;
    }
    struct Node *temp = head;
    if (position == 0) {
        head = temp->next;
        free(temp);
        return head;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        return head;
    }
    struct Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
    return head;
}

struct Node *deletekey(struct Node *head, char key) {
    struct Node *temp = head, *prev = NULL;
    if (temp != NULL && temp->data == key) {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head;
    prev->next = temp->next;
    free(temp);

    return head;
}

struct Node *delete_all(struct Node *head) {
    struct Node *current = head;
    struct Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    return head;
}

struct Node *trim0s(struct Node *head) {
    while (head->next != NULL && head->data == 0)
        head = head->next;
    return head;
}

int search(struct Node *head, int key) {
    struct Node *current = head;
    int index = 0;
    while (current != NULL) {
        if (current->data == key) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int ukuran(struct Node *head) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void printlist(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main(){
    int n, x=0, y=0;
    scanf("%d", &n);
    struct Node *head = NULL;
    if(n%2){
        for(int i = 0; i < n-1; i+=2){
            scanf("%d%d", &x, &y);
            head = append(head, y);
            head = append(head, x);
        }
        scanf("%d", &x);
        head = append(head, x);
    } else {
        for(int i = 0; i < n; i+=2){
            scanf("%d%d", &x, &y);
            head = append(head, y);
            head = append(head, x);
        }
    }
    printlist(head);


return 0;
}