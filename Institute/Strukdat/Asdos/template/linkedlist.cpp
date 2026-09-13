#include <bits/stdc++.h>
using namespace std;

class node {
public:
    int data;
    node* next;
    node(int data) : data(data), next(nullptr) {}
};

class dllnode {
public:
    int data;
    dllnode* next;
    dllnode* prev;
    dllnode(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class sllnc {
private:
    node* head;

public:
    sllnc() : head(nullptr) {}

    bool isempty() const {
        return head == nullptr;
    }

    void pushback(int data) {
        node* newnode = new node(data);
        if (!head) {
            head = newnode;
            return;
        }
        node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newnode;
    }

    void pushfront(int data) {
        node* newnode = new node(data);
        newnode->next = head;
        head = newnode;
    }

    bool insertat(int index, int data) {
        if (index < 0) return false;
        if (index == 0) {
            pushfront(data);
            return true;
        }
        node* temp = head;
        for (int i = 0; i < index - 1 && temp; ++i) temp = temp->next;
        if (!temp) return false;
        node* newnode = new node(data);
        newnode->next = temp->next;
        temp->next = newnode;
        return true;
    }

    bool deletenode(int data) {
        if (!head) return false;
        if (head->data == data) {
            node* del = head;
            head = head->next;
            delete del;
            return true;
        }
        node* temp = head;
        while (temp->next && temp->next->data != data) temp = temp->next;
        if (!temp->next) return false;
        node* del = temp->next;
        temp->next = temp->next->next;
        delete del;
        return true;
    }

    bool search(int data) const {
        node* temp = head;
        while (temp) {
            if (temp->data == data) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() const {
        node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void traverse() const {
        print();
    }

    ~sllnc() {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class sllc {
private:
    node* head;
    node* tail;

public:
    sllc() : head(nullptr), tail(nullptr) {}

    bool isempty() const {
        return head == nullptr;
    }

    void pushback(int data) {
        node* newnode = new node(data);
        if (isempty()) {
            head = tail = newnode;
            tail->next = head;
        } else {
            newnode->next = head;
            tail->next = newnode;
            tail = newnode;
        }
    }

    void pushfront(int data) {
        node* newnode = new node(data);
        if (isempty()) {
            head = tail = newnode;
            tail->next = head;
        } else {
            newnode->next = head;
            head = newnode;
            tail->next = head;
        }
    }

    bool deletenode(int data) {
        if (isempty()) return false;
        node *curr = head, *prev = tail;
        do {
            if (curr->data == data) {
                if (curr == head) head = head->next;
                if (curr == tail) tail = prev;
                prev->next = curr->next;
                delete curr;
                tail->next = head;
                return true;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);
        return false;
    }

    bool search(int data) const {
        if (isempty()) return false;
        node* temp = head;
        do {
            if (temp->data == data) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    void print(int limit = 20) const {
        if (isempty()) return;
        node* temp = head;
        int count = 0;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head && ++count < limit);
        cout << endl;
    }

    void traverse(int limit = 20) const {
        print(limit);
    }

    ~sllc() {
        if (!head) return;
        node* temp = head;
        tail->next = nullptr;
        while (temp) {
            node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

class dllc {
private:
    dllnode* head;

public:
    dllc() : head(nullptr) {}

    bool isempty() const {
        return head == nullptr;
    }

    void pushback(int data) {
        dllnode* newnode = new dllnode(data);
        if (!head) {
            head = newnode;
            head->next = head;
            head->prev = head;
        } else {
            dllnode* tail = head->prev;
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = head;
            head->prev = newnode;
        }
    }

    void pushfront(int data) {
        pushback(data);
        head = head->prev;
    }

    bool deletenode(int data) {
        if (!head) return false;
        dllnode* curr = head;
        do {
            if (curr->data == data) {
                if (curr->next == curr) {
                    delete curr;
                    head = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    if (curr == head) head = curr->next;
                    delete curr;
                }
                return true;
            }
            curr = curr->next;
        } while (curr != head);
        return false;
    }

    bool search(int data) const {
        if (!head) return false;
        dllnode* temp = head;
        do {
            if (temp->data == data) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    void printfwd(int limit = 20) const {
        if (!head) return;
        dllnode* temp = head;
        int count = 0;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head && ++count < limit);
        cout << endl;
    }

    void printbwd(int limit = 20) const {
        if (!head) return;
        dllnode* temp = head->prev;
        int count = 0;
        do {
            cout << temp->data << " ";
            temp = temp->prev;
        } while (temp != head->prev && ++count < limit);
        cout << endl;
    }

    void traverse() const {
        printfwd();
        printbwd();
    }

    ~dllc() {
        if (!head) return;
        dllnode* temp = head;
        head->prev->next = nullptr;
        while (temp) {
            dllnode* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    sllnc list1;
    list1.pushback(1);
    list1.pushback(2);
    list1.pushfront(0);
    list1.insertat(2, 10);
    list1.traverse();
    list1.deletenode(10);
    cout << "cari 2: " << list1.search(2) << endl;

    sllc list2;
    list2.pushback(10);
    list2.pushback(20);
    list2.pushfront(5);
    list2.traverse();
    list2.deletenode(10);
    cout << "cari 20: " << list2.search(20) << endl;

    dllc list3;
    list3.pushback(100);
    list3.pushfront(50);
    list3.pushback(150);
    list3.traverse();
    list3.deletenode(100);
    cout << "cari 150: " << list3.search(150) << endl;

    return 0;
}
