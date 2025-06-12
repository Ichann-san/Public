#include <bits/stdc++.h>
using namespace std;

class treenode {
public:
    int data;
    int height;
    treenode* left;
    treenode* right;

    treenode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class tree {
private:
    treenode* root;

    int max(int a, int b) { return a > b ? a : b; }
    int height(treenode* node) { return node ? node->height : 0; }
    int getbalance(treenode* node) { return node ? height(node->left) - height(node->right) : 0; }

    void updateheight(treenode* node) {
        if (node) node->height = max(height(node->left), height(node->right)) + 1;
    }

    treenode* rotateright(treenode* y) {
        treenode* x = y->left;
        treenode* t2 = x->right;
        x->right = y;
        y->left = t2;
        updateheight(y);
        updateheight(x);
        return x;
    }

    treenode* rotateleft(treenode* x) {
        treenode* y = x->right;
        treenode* t2 = y->left;
        y->left = x;
        x->right = t2;
        updateheight(x);
        updateheight(y);
        return y;
    }

    treenode* rotateleftright(treenode* node) {
        node->left = rotateleft(node->left);
        return rotateright(node);
    }

    treenode* rotaterightleft(treenode* node) {
        node->right = rotateright(node->right);
        return rotateleft(node);
    }

    treenode* balance(treenode* node) {
        if (!node) return node;
        updateheight(node);
        int balance = getbalance(node);

        if (balance > 1) {
            if (getbalance(node->left) >= 0)
                return rotateright(node);
            else
                return rotateleftright(node);
        }
        if (balance < -1) {
            if (getbalance(node->right) <= 0)
                return rotateleft(node);
            else
                return rotaterightleft(node);
        }
        return node;
    }

    treenode* insert(treenode* node, int val) {
        if (!node) return new treenode(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        updateheight(node);
        return node;
        //return balance(node);
    }

    treenode* findmin(treenode* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    treenode* findmax(treenode* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    treenode* del(treenode* node, int val) {
        if (!node) return nullptr;
        if (val < node->data)
            node->left = del(node->left, val);
        else if (val > node->data)
            node->right = del(node->right, val);
        else {
            if (!node->left || !node->right) {
                treenode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                treenode* temp = findmin(node->right);
                node->data = temp->data;
                node->right = del(node->right, temp->data);
            }
        }
        updateheight(node);
        return node;
        //return balance(node);
    }

    treenode* search(treenode* node, int val) {
        if (!node || node->data == val) return node;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    bool rootexists() {
        return root != nullptr;
    }

    void inorder(treenode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(treenode* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(treenode* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void level(treenode* root) {
        if (!root) return;
        queue<treenode*> q;
        q.push(root);
        while (!q.empty()) {
            treenode* cur = q.front(); q.pop();
            cout << cur->data << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    void destroy(treenode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    int count(treenode* node) {
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }

    int treeheight(treenode* node) {
        return node ? node->height : 0;
    }

    int nodeheight(treenode* node, int val) {
        if (!node) return -1;
        if (node->data == val) return node->height;
        if (val < node->data) return nodeheight(node->left, val);
        return nodeheight(node->right, val);
    }

    int nodedepth(treenode* node, int val, int depth) {
        if (!node) return -1;
        if (node->data == val) return depth;
        if (val < node->data) return nodedepth(node->left, val, depth + 1);
        return nodedepth(node->right, val, depth + 1);
    }

    bool balanced(treenode* node) {
        if (!node) return true;
        int bf = getbalance(node);
        if (bf < -1 || bf > 1) return false;
        return balanced(node->left) && balanced(node->right);
    }

public:
    tree() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    void remove(int val) { root = del(root, val); }
    bool search(int val) { return search(root, val) != nullptr; }
    void printinorder() { inorder(root); cout << endl; }
    void printpreorder() { preorder(root); cout << endl; }
    void printpostorder() { postorder(root); cout << endl; }
    void printlevelorder() { level(root); cout << endl; }
    int getmin() { treenode* n = findmin(root); return n ? n->data : -1; }
    int getmax() { treenode* n = findmax(root); return n ? n->data : -1; }
    int getcount() { return count(root); }
    int getheight() { return treeheight(root); }
    bool isbalanced() { return balanced(root); }
    bool exists() { return rootexists(); }
    void clear() { destroy(root); root = nullptr; }
    int nodeheight(int val) { return nodeheight(root, val); }
    int nodedepth(int val) { return nodedepth(root, val, 0); }
};

void solve(vector<int>& pohon) {
    stack<int> s;
    int root = INT_MIN;
    for(int i=0; i<pohon.size(); i++) {
        if (pohon[i] < root) {
            cout << "Ini bukan pohon" << endl;
            return;
        }
        while (!s.empty() && s.top() < pohon[i]) {
            root = s.top();
            s.pop();
        }
        s.push(pohon[i]);
    }
    cout << "Ini pohon" << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> pohon(n);
    for (int i = 0; i < n; i++) {
        cin >> pohon[i];
    }
    solve(pohon);
    return 0;
}
