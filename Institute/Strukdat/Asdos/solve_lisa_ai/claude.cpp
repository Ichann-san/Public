#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Store each region's list of vision holders
    vector<vector<string>> regions(n);
    // Map: character name -> {region index, position in that region}
    unordered_map<string, pair<int,int>> lookup;

    for (int i = 0; i < n; i++) {
        string region_name;
        cin >> region_name;

        string name;
        while (cin >> name && name != "end")
            regions[i].push_back(name);

        // Register each vision holder with their region index and position (1-based, 0 = Tree)
        for (int j = 0; j < (int)regions[i].size(); j++)
            lookup[regions[i][j]] = {i, j + 1};
    }

    int q;
    cin >> q;

    while (q--) {
        string a, b;
        int k;
        cin >> a >> b >> k;

        // If either person doesn't exist
        if (lookup.find(a) == lookup.end() || lookup.find(b) == lookup.end()) {
            cout << "Signal lost\n";
            continue;
        }

        auto [ra, pa] = lookup[a];
        auto [rb, pb] = lookup[b];
        int hops;

        if (ra == rb) {
            // Same region: circular ring of vision holders only (no Tree node)
            int sz = regions[ra].size();
            int diff = abs(pa - pb);
            hops = min(diff, sz - diff);
        } else {
            // Cross-region: A -> Tree(A) -> Irminsul -> Tree(B) -> B
            int local_a = regions[ra].size() + 1; // local ring size (visions + Tree)
            int local_b = regions[rb].size() + 1;

            int to_tree   = min(pa, local_a - pa);           // A to its Tree
            int irminsul  = min(abs(ra - rb), n - abs(ra - rb)); // Tree to Tree
            int from_tree = min(pb, local_b - pb);            // Tree to B

            hops = to_tree + irminsul + from_tree;
        }

        if (hops <= k)
            cout << "Connected on " << hops << " second\n";
        else
            cout << "Signal lost\n";
    }

    return 0;
}