#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1); // karena node dari 1..N
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    int maxDeliveryTime(int start) {
        vector<int> dist(V + 1, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;

            for (auto &[v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        int maxTime = 0;
        for (int i = 1; i <= V; ++i) {
            if (i == start) continue;
            if (dist[i] == numeric_limits<int>::max())
                return -1;
            maxTime = max(maxTime, dist[i]);
        }
        return maxTime;
    }
};

int main() {
    int N, K;
    cin >> N >> K;

    Graph g(N);
    while (true) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == 0 && v == 0 && w == 0) break;
        g.addEdge(u, v, w);
    }

    int result = g.maxDeliveryTime(K);
    cout << result << endl;

    return 0;
}
