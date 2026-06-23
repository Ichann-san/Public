#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, n, q, hops;
    cin >> n;
    vector<vector<string>> regions(n);
    unordered_map<string, pair<int,int>> lookup; //character di genshin nya
    for (int i = 0; i < n; i++) {
        string region_name;
        cin >> region_name;
        string name;
        while (cin >> name && name != "end") regions[i].push_back(name);
        for (int j = 0; j < (int)regions[i].size(); j++) lookup[regions[i][j]] = {i, j + 1};
    }
    cin >> q;
    while (q--) {
        string a, b;
        cin >> a >> b >> k;
        if (lookup.find(a) == lookup.end() || lookup.find(b) == lookup.end()) {
            cout << "Signal lost\n";
            continue;
        }
        auto [ra, pa] = lookup[a], [rb, pb] = lookup[b];
        if (ra == rb) {
            int sz = regions[ra].size(), diff = abs(pa - pb);
            hops = min(diff, sz - diff);
        } else {
            int local_a = regions[ra].size() + 1, local_b = regions[rb].size() + 1;
            int to_tree   = min(pa, local_a - pa), from_tree = min(pb, local_b - pb);
            int irminsul  = min(abs(ra - rb), n - abs(ra - rb));
            hops = to_tree + irminsul + from_tree;
        }
        if (hops <= k) cout << "Connected on " << hops << " second\n";
        else cout << "Signal lost\n";
    }
    return 0;
}