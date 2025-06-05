#include <bits/stdc++.h>
using namespace std;

class graph {
private:
    int V;
    vector<tuple<int, int, int>> edges; // {weight, u, v}
    vector<int> parent;

    int find(int u) {
        if (parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) parent[v] = u;
    }

public:
    graph(int V) {
        this->V = V;
        parent.resize(V+1);
        for (int i=0; i<V; ++i) parent[i+1] = i+1;
    }

    void add_edge(int u, int v, int w) {
        edges.emplace_back(w, u, v);
    }

    int kruskal() {
        sort(edges.begin(), edges.end());
        int cost = 0, visited = 0;
        for (auto& [w, u, v] : edges) {
            if (find(u) != find(v)) {
                unite(u, v);
                cost += w;
                visited++;
                if (visited == V-1) break;
            }
        }
        return cost;
    }
};

int main() {
    int v, e, budget;
    cin >> v >> e;
    graph g(v);
    for (int i = 0; i<e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g.add_edge(a, b, w);
    }
    cin >> budget;

    int cost = g.kruskal();
    if (budget >= cost) {
        cout << "Budgetnya cukup Bos! Ada sisa " << abs(budget-cost) << endl;
    } else {
        cout << "Waduh budgetnya kurang bos" << endl;
    }

    return 0;
}
