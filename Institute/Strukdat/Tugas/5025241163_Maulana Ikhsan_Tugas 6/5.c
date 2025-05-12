#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

TreeNode* deleteadapenerus(TreeNode* root) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }

    if (root->right == NULL) {
        TreeNode* newRoot = root->left;
        free(root);
        return newRoot;
    }

    if (root->left == NULL) {
        TreeNode* newRoot = root->right;
        free(root);
        return newRoot;
    }

    TreeNode* parent = NULL;
    TreeNode* succ = root->right;
    while (succ->left != NULL) {
        parent = succ;
        succ = succ->left;
    }

    if (parent != NULL) {
        parent->left = succ->right;
    } else {
        root->right = succ->right;
    }

    succ->left = root->left;
    succ->right = root->right;
    free(root);
    return succ;
}

TreeNode* deleteadamoyang(TreeNode* root) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }

    if (root->right == NULL) {
        TreeNode* newRoot = root->left;
        free(root);
        return newRoot;
    }

    if (root->left == NULL) {
        TreeNode* newRoot = root->right;
        free(root);
        return newRoot;
    }

    TreeNode* parent = NULL;
    TreeNode* pred = root->left;
    while (pred->right != NULL) {
        parent = pred;
        pred = pred->right;
    }

    if (parent != NULL) {
        parent->right = pred->left;
    } else {
        root->left = pred->left;
    }

    pred->left = root->left;
    pred->right = root->right;
    free(root);
    return pred;
}

void urut(TreeNode* root) {
    if (root == NULL) return;
    urut(root->left);
    printf("%d ", root->val);
    urut(root->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    int n, x;
    scanf("%d", &n);
    int values[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        values[i] = x;
    }

    for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        root = insert(root, values[i]);
    }

    printf("Original tree in-order: ");
    urut(root);
    printf("\n");

    TreeNode* newRootSuccessor = deleteadapenerus(root);
    printf("After deleting root with successor: ");
    urut(newRootSuccessor);
    printf("\n");
    freeTree(newRootSuccessor);

    root = NULL;
    for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        root = insert(root, values[i]);
    }

    TreeNode* newRootPredecessor = deleteadamoyang(root);
    printf("After deleting root with predecessor: ");
    urut(newRootPredecessor);
    printf("\n");

    freeTree(newRootPredecessor);
    return 0;
}