#include <bits/stdc++.h>
using namespace std;

void reverse(queue<int> &q) {
    stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

void solve(int n, queue<int> &q) {
    string s;
    int x;
    while(n--) {
        cin >> s;
        if(s == "depan") {
            if(!q.empty()) {
                cout << q.front();
                q.pop();
            }
            cout << endl;
        }
        if(s == "belakang") {
            if(!q.empty()) {
                cout << q.back();
                reverse(q);
                q.pop();
                reverse(q);
            }
            cout << endl;
        }
        if(s == "tambahDepan") {
            cin >> x;
            reverse(q);
            q.push(x);
            reverse(q);
        }
        if(s == "tambahBelakang") {
            cin >> x;
            q.push(x);
        }
        if(s == "balik") {
            reverse(q);
        }
    }

}

int main(){
    int n;
    queue<int> q;
    cin >> n;
    solve(n, q);

return 0;
}