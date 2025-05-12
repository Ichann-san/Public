#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int id;
    char name[31];
    int inheritance, received;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int id, const char* name, int inheritance) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->id = id;
    strncpy(node->name, name, 30);
    node->name[30] = '\0';
    node->inheritance = inheritance;
    node->received = 0;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insertNode(TreeNode* root, int id, const char* name, int inheritance) {
    if (root == NULL) {
        return createNode(id, name, inheritance);
    }
    if (id < root->id) {
        root->left = insertNode(root->left, id, name, inheritance);
    } else if (id > root->id) {
        root->right = insertNode(root->right, id, name, inheritance);
    } else {
        printf("ID %d sudah ada, skip insert.\n", id);
    }
    return root;
}

TreeNode* findNode(TreeNode* root, int id) {
    if (root == NULL) return NULL;
    if (id == root->id) return root;
    if (id < root->id) return findNode(root->left, id);
    return findNode(root->right, id);
}

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    printf("ID: %d, Name: %s, Inheritance: %d, Received: %d\n",
           root->id, root->name, root->inheritance, root->received);
    printInorder(root->right);
}

void distributeInheritance(TreeNode* node) {
    if (!node) return;
    if (!node->left && !node->right) {
        node->inheritance = 0;
        return;
    }
    int amount = node->inheritance;
    if (node->left) {
        int leftAmt = (amount * 60) / 100;
        node->left->inheritance += leftAmt;
        node->left->received += leftAmt;
    }
    if (node->right) {
        int rightAmt = (amount * 40) / 100;
        node->right->inheritance += rightAmt;
        node->right->received += rightAmt;
    }
    node->inheritance = 0;
    if (node->left) distributeInheritance(node->left);
    if (node->right) distributeInheritance(node->right);
}

int main() {
    TreeNode* root = NULL;
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Tambah anggota keluarga\n");
        printf("2. Tampilkan pohon (inorder)\n");
        printf("3. Simulasi kematian dan bagi warisan\n");
        printf("4. Keluar\n");
        printf("Pilih: "); scanf("%d", &choice);
        if (choice == 1) {
            int id, inh;
            char name[31];
            printf("Masukkan ID: "); scanf("%d", &id);
            printf("Masukkan Nama: ");
            getchar(); fgets(name, 31, stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("Masukkan nilai warisan (juta): "); scanf("%d", &inh);
            root = insertNode(root, id, name, inh);
        } else if (choice == 2) {
            printf("\nStruktur pohon (inorder):\n");
            printInorder(root);
        } else if (choice == 3) {
            int id;
            printf("Masukkan ID anggota yang meninggal: "); scanf("%d", &id);
            TreeNode* target = findNode(root, id);
            if (!target) {
                printf("Anggota dengan ID %d tidak ditemukan.\n", id);
            } else {
                distributeInheritance(target);
                printf("Distribusi warisan dari ID %d selesai.\n", id);
            }
        } else if (choice == 4) {
            printf("Keluar program.\n");
        } else {
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 4);
    return 0;
}
