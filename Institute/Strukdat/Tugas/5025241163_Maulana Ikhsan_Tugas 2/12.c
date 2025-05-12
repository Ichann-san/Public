#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>

struct Node{
    int data;
    struct Node *next;
};

void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void hapusdipos(struct Node** head_ref, int position) {
    if (*head_ref == NULL) return;
    struct Node* temp = *head_ref;
    if (position == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) return;
    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

int ukuran(struct Node* head) {
    int count = 0;
    struct Node* current = head;
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
int n, m;
scanf("%d %d", &n, &m);
struct Node* head = NULL;
for(int i = 0; i < n; i++){//ini masukin nilai i
    append(&head, i+1);
}
int size = ukuran(head);
int posisi = (m-1) % size;

while(head != NULL && head->next != NULL){//ini hapus di m
    hapusdipos(&head, posisi);
    posisi+= m-1;//ini biar maju gitu
    posisi %= size;
    size--;
    // printlist(head);
    // printf("\n");
}

printlist(head);
free(head);
return 0;
}