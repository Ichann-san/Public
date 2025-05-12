#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* searchPreOrder(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->val == key) {
        return root;
    }
    TreeNode* leftResult = searchPreOrder(root->left, key);
    if (leftResult != NULL) {
        return leftResult;
    }
    return searchPreOrder(root->right, key);
}

TreeNode* searchInOrder(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* leftResult = searchInOrder(root->left, key);
    if (leftResult != NULL) {
        return leftResult;
    }
    if (root->val == key) {
        return root;
    }
    return searchInOrder(root->right, key);
}

TreeNode* searchPostOrder(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* leftResult = searchPostOrder(root->left, key);
    if (leftResult != NULL) {
        return leftResult;
    }
    TreeNode* rightResult = searchPostOrder(root->right, key);
    if (rightResult != NULL) {
        return rightResult;
    }
    if (root->val == key) {
        return root;
    }
    return NULL;
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int key;
    scanf("%d", &key);
    TreeNode* root = createNode(1);     //              1
    root->left = createNode(2);         //            2    3
    root->right = createNode(3);        //           4 5  6 7
    root->left->left = createNode(4);   // ini buat bentuknya kira kira begini
    root->left->right = createNode(5);  // tree nya jelek sih, tapi contoh doang
    root->right->left = createNode(6);  // kalo mau bikin bisa pake insert insert biar bagus tree nya
    root->right->right = createNode(7); //

    TreeNode* resultPreOrder = searchPreOrder(root, key);
    printf("Pre-order search: %s\n", resultPreOrder ? "Found" : "Not Found");

    TreeNode* resultInOrder = searchInOrder(root, key);
    printf("In-order search: %s\n", resultInOrder ? "Found" : "Not Found");

    TreeNode* resultPostOrder = searchPostOrder(root, key);
    printf("Post-order search: %s\n", resultPostOrder ? "Found" : "Not Found");

    freeTree(root);
    return 0;
}