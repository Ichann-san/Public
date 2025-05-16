#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} bst;

void init_tree(bst* tree) { tree->root = NULL; }

TreeNode* create_node(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->parent = NULL;
    node->left = node->right = NULL;
    return node;
}

int daun_kiri(int n) {
    if (n == 0)return 0;
    int h = 0;
    while ((1 << (h + 1)) <= n + 1) {h++;}
    int m = (1 << h) - 1; akhir = n - m; kanan_akhir = (1 << (h - 1));
    int left = (m - 1) / 2 + (akhir > kanan_akhir ? kanan_akhir : akhir);
    return left;
}

TreeNode* bikin_tree(int arr[], int start, int end, TreeNode* parent) {
    if (start > end) return NULL;
    int n = end - start + 1; left_size = daun_kiri(n);
    int root_index = start + left_size;
    TreeNode* root = create_node(arr[root_index]);
    root->parent = parent;
    root->left = bikin_tree(arr, start, root_index - 1, root);
    root->right = bikin_tree(arr, root_index + 1, end, root);
    return root;
}

void ngurut(TreeNode* node, TreeNode** nodes, int* index) {
    if (node == NULL) return;
    ngurut(node->left, nodes, index);
    nodes[(*index)++] = node;
    ngurut(node->right, nodes, index);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), compare);
    bst tree;
    init_tree(&tree);
    tree.root = bikin_tree(a, 0, n - 1, NULL);
    TreeNode** nodes = (TreeNode**)malloc(n * sizeof(TreeNode*));
    int index = 0;
    ngurut(tree.root, nodes, &index);

    for (int i = 0; i < n; i++) {
        TreeNode* parent = nodes[i]->parent;
        if (parent == NULL)
            printf("-1 ");
        else
            printf("%d ", parent->data);
    }
    printf("\n");
    return 0;
}