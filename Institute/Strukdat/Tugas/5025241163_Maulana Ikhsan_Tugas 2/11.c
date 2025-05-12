#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>

struct Node{
    char data;
    struct Node *next;
};

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

void printlist(struct Node *node) {
    while (node != NULL) {
        printf("%c", node->data);
        node = node->next;
    }
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

bool anagram(struct Node *word1, struct Node *word2){
    if(ukuran(word1) != ukuran(word2)) return false;
    struct Node *temp1 = word1, *temp2 = word2;

    while(temp1 != NULL){
        temp2 = word2;
        bool found = false;
        while(temp2 != NULL){
            if(temp1->data == temp2->data){
                word2 = deletekey(word2, temp2->data);
                found = true;
                break;
            }
            temp2 = temp2->next;
        }
        if(!found) return false;
        temp1 = temp1->next;
    }
    return true;
}

int main(){
char kata1[1000], kata2[1000];
scanf("%s" "%s", kata1, kata2);
struct Node *word1 = NULL, *word2 = NULL;
for(int i=0; i<fmax(strlen(kata1), strlen(kata2)); i++){
    if(i<strlen(kata1)) word1 = append(word1, kata1[i]);
    if(i<strlen(kata2)) word2 = append(word2, kata2[i]);
}

if(anagram(word1, word2)) printf("Anagram\n");
else printf("Bukan Anagram\n");
return 0;
}