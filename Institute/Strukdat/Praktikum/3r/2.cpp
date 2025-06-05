#include <bits/stdc++.h>
using namespace std;

class graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int bfs(int start, int target) {
        queue<int> q;
        vector<bool> visited(V, false);
        vector<int> distance(V, -1);
        
        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        return distance[target];
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    int result = g.bfs(s, t);
    cout << result << endl;
    return 0;
}
