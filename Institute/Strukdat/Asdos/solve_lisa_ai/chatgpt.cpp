#include <bits/stdc++.h>
using namespace std;

int circular_min_dist(int a, int b, int n) {
    int d = abs(a - b);
    return min(d, n - d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    string dummy;
    getline(cin, dummy); // consume endline

    vector<string> regions(N);
    vector<vector<string>> holders(N);
    unordered_map<string, pair<int,int>> pos; // name -> (region_id, index)

    for (int i = 0; i < N; ++i) {
        // read region name (skip possible empty lines)
        string region;
        while (true) {
            if (!getline(cin, region)) break;
            if (!region.empty()) break;
        }
        regions[i] = region;

        // read the line with vision holders (tokens ending with "end")
        string line;
        while (true) {
            if (!getline(cin, line)) break;
            if (!line.empty()) break;
        }
        stringstream ss(line);
        string name;
        int idx = 0;
        while (ss >> name) {
            if (name == "end") break;
            holders[i].push_back(name);
            pos[name] = {i, idx};
            ++idx;
        }
    }

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 0; tc < T; ++tc) {
        string origin, dest;
        int K;
        cin >> origin >> dest >> K;

        // check existence
        if (pos.find(origin) == pos.end() || pos.find(dest) == pos.end()) {
            cout << "Signal lost\n";
            continue;
        }

        auto [r1, idx1] = pos[origin];
        auto [r2, idx2] = pos[dest];

        long long hops = 0;
        if (r1 == r2) {
            int sz = (int)holders[r1].size();
            if (sz == 0) { // defensive; but if names exist, sz>0
                cout << "Signal lost\n";
                continue;
            }
            hops = circular_min_dist(idx1, idx2, sz);
        } else {
            int sz1 = (int)holders[r1].size();
            int sz2 = (int)holders[r2].size();
            if (sz1 == 0 || sz2 == 0) { // if any region has zero holders, (but name existence prevents this)
                cout << "Signal lost\n";
                continue;
            }
            int dist_origin_to_head = min(idx1, sz1 - idx1);
            int dist_dest_to_head   = min(idx2, sz2 - idx2);
            int tree_dist = circular_min_dist(r1, r2, N);
            // add: origin->head (dist_origin_to_head), head->tree (1), tree ring (tree_dist),
            // tree->head_dest (1), head_dest->dest (dist_dest_to_head)
            hops = dist_origin_to_head + 1 + tree_dist + 1 + dist_dest_to_head;
        }

        if (hops <= K) {
            cout << "Connected on " << hops << " second\n";
        } else {
            cout << "Signal lost\n";
        }
    }
    return 0;
}