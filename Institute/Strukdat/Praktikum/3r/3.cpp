#include <bits/stdc++.h>
using namespace std;

class graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void dijkstra(int s) {
        if (s<0 || s >= V) {
            cout << "Invalid starting point" << endl;
            return;
        }

        vector<long long> dist(V, numeric_limits<long long>::max());
        vector<int> prev(V, -1);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;

            for (auto &[v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }

        for (int i=0; i < V; ++i) {
            if (i==s) continue;
            cout << "---From " << s << " to " << i << "---" << endl;
            if (dist[i] == numeric_limits<long long>::max()) continue;

            vector<int> path;
            for (int v = i; v != -1; v = prev[v]) { path.push_back(v); }
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i];
                if (i != 0) cout << " - ";
            }
            cout << endl;
        }
    }
};

int main() {
    int a, b, u, v, n, s;
    cin >> a >> b;

    graph g(a);
    for (int i = 0; i < b; ++i) {
        long long w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    cin >> n;
    while (n--) {
        cin >> s;
        g.dijkstra(s);
    }

    return 0;
}
