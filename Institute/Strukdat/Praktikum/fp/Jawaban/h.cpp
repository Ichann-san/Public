#include <bits/stdc++.h>
using namespace std;

void solve(string s) {
    vector<pair<char, int>> v(26, {'a', 0});
    int n = s.size();

    for (int i=0; i<26; i++) {
        v[i].first = 'a' + i;
    }

    for (int i=0; i<s.length(); i++) {
        v[s[i] - 'a'].second++;
    }

    for (int i = 0; i < s.size(); i++) {
        if (v[s[i] - 'a'].second == 1) {
            cout << i << endl;
            return;
        }
    }
    cout << -1;
}

int main() {
    string s;
    cin >> s;
    solve(s);
return 0;
}