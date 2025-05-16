#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    int occur;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BinaryTree;

int max(int a, int b) { return a > b ? a : b; }
int height(TreeNode* node) { return node ? node->height : 0; }
int get_balance_factor(TreeNode* node) { return node ? height(node->left) - height(node->right) : 0; }
void init_tree(BinaryTree* tree) { tree->root = NULL; }

TreeNode* create_node(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->height = 1;
    node->occur = 0;
    node->left = node->right = NULL;
    return node;
}

TreeNode* rotate_right(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

TreeNode* rotate_left(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

TreeNode* rotate_left_right(TreeNode* node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

TreeNode* rotate_right_left(TreeNode* node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

void update_height(TreeNode* node) {
    if (node) node->height = max(height(node->left), height(node->right)) + 1;
}

TreeNode* balance_tree(TreeNode* node) {
    if (!node) return node;
    update_height(node);
    int balance = get_balance_factor(node);

    if (balance > 1) {// Left Left
        if (get_balance_factor(node->left) >= 0)
            return rotate_right(node);
        else
            return rotate_left_right(node);
    }
    if (balance < -1) {// Right Right
        if (get_balance_factor(node->right) <= 0)
            return rotate_left(node);
        else
            return rotate_right_left(node);
    }
    return node;
}

TreeNode* insert_node(TreeNode* node, int data) {//bst ga avl
    if (!node) return create_node(data);
    if (data < node->data)
        node->left = insert_node(node->left, data);
    else if (data > node->data)
        node->right = insert_node(node->right, data);
    return node;
}

TreeNode* find_min(TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

TreeNode* find_max(TreeNode* node) {
    while (node && node->right) node = node->right;
    return node;
}

TreeNode* delete_node(TreeNode* node, int data) {
    if (!node) return NULL;
    if (data < node->data)
        node->left = delete_node(node->left, data);
    else if (data > node->data)
        node->right = delete_node(node->right, data);
    else {
        if (node->occur > 0) {
            node->occur--;
            return node;
        }
        if (!node->left || !node->right) {
            TreeNode* temp = node->left ? node->left : node->right;
            free(node);
            return temp;
        } else {
            TreeNode* temp = find_min(node->right);
            node->data = temp->data;
            node->occur = temp->occur;
            temp->occur = 0;
            node->right = delete_node(node->right, temp->data);
        }
    }
    return node;
}

TreeNode* search_node(TreeNode* node, int data, char* key) {
    if (!node || node->data == data){
        if(strcmp(key, "insert") == 0) {
            node->occur++;
        } else if(strcmp(key, "remove") == 0 && node->occur > 0) {
            node->occur--;
        }
        return node;
    }
    if (data < node->data) return search_node(node->left, data, key);
    return search_node(node->right, data, key);
}

void inorder_traversal(TreeNode* node) {
    if (!node) return;
    inorder_traversal(node->left);
    if(node->occur > 0 ) printf("%d(%d) ", node->data, node->occur);
    inorder_traversal(node->right);
}

void preorder_traversal(TreeNode* node) {
    if (!node) return;
    if(node->occur > 0 ) printf("%d(%d) ", node->data, node->occur);
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void postorder_traversal(TreeNode* node) {
    if (!node) return;
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    if(node->occur > 0 ) printf("%d(%d) ", node->data, node->occur);
}

TreeNode* find_inorder_successor(TreeNode* node) {
    return find_min(node->right);
}

TreeNode* find_inorder_predecessor(TreeNode* node) {
    return find_max(node->left);
}

bool is_tree_empty(BinaryTree* tree) {
    return tree->root == NULL;
}

void destroy_tree(TreeNode* node) {
    if (!node) return;
    destroy_tree(node->left);
    destroy_tree(node->right);
    free(node);
}

int count_nodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

int tree_height(TreeNode* node) {
    return node ? node->height : 0;
}

bool is_balanced(TreeNode* node) {
    if (!node) return true;
    int bf = get_balance_factor(node);
    if (bf < -1 || bf > 1) return false;
    return is_balanced(node->left) && is_balanced(node->right);
}

void print_level(TreeNode* node, int level) {
    if (!node) return;
    if (level == 1) printf("%d ", node->data);
    else {
        print_level(node->left, level - 1);
        print_level(node->right, level - 1);
    }
}

void level_order_traversal(TreeNode* root) {
    if (!root) return;
    int h = tree_height(root);
    for (int i = 1; i <= h; i++) {
        print_level(root, i);
    }
}

void print_tree(TreeNode* node, int space) {
    if (!node) return;
    space += 5;
    print_tree(node->right, space);
    for (int i = 5; i < space; i++) printf(" ");
    printf("%d\n", node->data);
    print_tree(node->left, space);
}

int main() {
    BinaryTree tree;
    init_tree(&tree);
    int n, x;
    char s[100];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", s);
        if(strcmp(s, "insert") == 0) {
            scanf("%d", &x);
            TreeNode* found = search_node(tree.root, x, "");
            if(found == NULL) {
                tree.root = insert_node(tree.root, x);
                TreeNode* inserted = search_node(tree.root, x, "");
                if(inserted) inserted->occur = 1;
            } else {
                found->occur++;
            }
        } else if(strcmp(s, "remove") == 0) {
            scanf("%d", &x);
            TreeNode* found = search_node(tree.root, x, "");
            if(found != NULL) {
                if(found->occur > 0) {
                    found->occur--;
                } else {
                    tree.root = delete_node(tree.root, x);
                }
            }
        } else if(strcmp(s, "inorder") == 0) {
            inorder_traversal(tree.root);
            printf("\n");
        } else if(strcmp(s, "preorder") == 0) {
            preorder_traversal(tree.root);
            printf("\n");
        } else if(strcmp(s, "postorder") == 0) {
            postorder_traversal(tree.root);
            printf("\n");
        }
    }

    return 0;
}