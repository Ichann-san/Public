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

struct Node *makenode(int data) {
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

struct Node *reverse(struct Node *head) {
    struct Node *prev = NULL, *curr = head, *next;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

struct Node *trim0s(struct Node *head) {
    while (head->next != NULL && head->data == 0)
        head = head->next;
    return head;
}

struct Node *add2list(struct Node *num1, struct Node *num2) {
    struct Node *res = NULL, *curr = NULL;
    int carry = 0;
    num1 = trim0s(num1); num1 = reverse(num1);
    num2 = trim0s(num2); num2 = reverse(num2);

    while (num1 != NULL || num2 != NULL || carry != 0) {//ini cek buat carry
        int sum = carry;

        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }
        struct Node* newNode = makenode(sum%10);
        carry = sum/10;

        if (res == NULL) {
            res = newNode;
            curr = newNode;
        } else {
            curr->next = newNode;
            curr = curr->next;
        }
    }
    return reverse(res);
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
        printf("%d", node->data);
        node = node->next;
    }
}

int main(){
char num1[1000], num2[1000];
scanf("%s %s", num1, num2);
struct Node *head1 = NULL, *head2 = NULL;
for(int i = 0; i < fmax(strlen(num1), strlen(num2)); i++){
    if(i<strlen(num1)) head1 = append(head1, num1[i] - '0');
    if(i<strlen(num2)) head2 = append(head2, num2[i] - '0');
}

printf("Nomor1 : ");printlist(head1); printf("\n");
printf("Nomor2 : ");printlist(head2); printf("\n");
printf("Hasil : ");printlist(add2list(head1, head2)); printf("\n");
return 0;
}