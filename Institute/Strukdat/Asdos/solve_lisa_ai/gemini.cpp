#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O for competitive programming/practicum environments
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0; // Read number of regions

    // Database to map "Person Name" -> {Region Index, Person Index}
    unordered_map<string, pair<int, int>> db;
    // Array to keep track of the total number of people in each region
    vector<int> reg_size(N);

    // 1. Build the Database
    for (int i = 0; i < N; ++i) {
        string region_name;
        cin >> region_name;

        string person;
        int idx = 0;
        // Read vision holders until "end" keyword is encountered
        while (cin >> person && person != "end") {
            db[person] = {i, idx};
            idx++;
        }
        reg_size[i] = idx; // Store total size of this circular ring
    }

    // 2. Process Queries
    int T;
    cin >> T;
    while (T--) {
        string origin, destination;
        int K;
        cin >> origin >> destination >> K;

        // Check if either person is missing from the database
        if (db.find(origin) == db.end() || db.find(destination) == db.end()) {
            cout << "Signal lost\n";
            continue;
        }

        // Fetch coordinates
        int r1 = db[origin].first, p1 = db[origin].second;
        int r2 = db[destination].first, p2 = db[destination].second;

        int total_distance = 0;

        if (r1 == r2) {
            // Case A: Both users are in the same region
            int M = reg_size[r1];
            total_distance = min(abs(p1 - p2), M - abs(p1 - p2));
        } else {
            // Case B: Users are in different regions, must route through Irminsul (Trees of Life)
            int M1 = reg_size[r1];
            int M2 = reg_size[r2];
            
            // Distance to reach the local tree (head is at index 0, adding 1 hop for tree connection)
            int dist_tree1 = min(p1, M1 - p1) + 1;
            int dist_tree2 = min(p2, M2 - p2) + 1;
            
            // Shortest path between the two region trees on the global ring
            int dist_global = min(abs(r1 - r2), N - abs(r1 - r2));
            
            total_distance = dist_tree1 + dist_global + dist_tree2;
        }

        // 3. Output Result
        if (total_distance <= K) {
            cout << "Connected on " << total_distance << " second\n";
        } else {
            cout << "Signal lost\n";
        }
    }

    return 0;
}