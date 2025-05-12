#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int id;
    char nama[31];
    int prioritas;
    int timestamp;
    struct Node* next;
} Node;

Node* head = NULL;
static int global_timestamp = 1;

Node* createNode(int id, const char* nama, int prioritas) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->nama, nama);
    newNode->prioritas = prioritas;
    newNode->timestamp = global_timestamp++;
    newNode->next = NULL;
    return newNode;
}

bool isIdUnique(int id) {
    Node* current = head;
    while (current != NULL) {
        if (current->id == id) return false;
        current = current->next;
    }
    return true;
}

void tambahLaporan() {
    int id, prioritas;
    char nama[31];
    
    printf("Masukkan ID: ");
    scanf("%d", &id);
    if (!isIdUnique(id)) {
        printf("ID sudah ada!\n");
        return;
    }
    
    printf("Masukkan nama: ");
    scanf(" %[^\n]%*c", nama);
    
    do {
        printf("Masukkan prioritas (1-5): ");
        scanf("%d", &prioritas);
    } while (prioritas < 1 || prioritas > 5);

    Node* newNode = createNode(id, nama, prioritas);
    if (head == NULL || 
        (newNode->prioritas < head->prioritas) || 
        (newNode->prioritas == head->prioritas && newNode->timestamp < head->timestamp)) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL && 
               (current->next->prioritas < newNode->prioritas ||
               (current->next->prioritas == newNode->prioritas && 
                current->next->timestamp < newNode->timestamp))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    printf("Laporan ditambahkan!\n");
}

void prosesLaporan() {
    if (head == NULL) {
        printf("Antrian kosong!\n");
        return;
    }
    
    Node* temp = head;
    printf("Proses: ID=%d, Nama=%s, Prioritas=%d\n", 
           temp->id, temp->nama, temp->prioritas);
    head = head->next;
    free(temp);
}

void tampilkanLaporan() {
    if (head == NULL) {
        printf("Antrian kosong!\n");
        return;
    }
    
    Node* current = head;
    printf("Daftar Laporan:\n");
    while (current != NULL) {
        printf("ID: %d, Nama: %s, Prioritas: %d\n",
               current->id, current->nama, current->prioritas);
        current = current->next;
    }
}

int main() {
    int pilihan;
    
    do {
        printf("\nMenu:\n");
        printf("1. Tambah laporan baru\n");
        printf("2. Proses laporan\n");
        printf("3. Tampilkan semua laporan\n");
        printf("4. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1: tambahLaporan(); break;
            case 2: prosesLaporan(); break;
            case 3: tampilkanLaporan(); break;
            case 4: printf("Keluar...\n"); break;
            default: printf("Input salah!\n");
        }
    } while (pilihan != 4);
    
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
