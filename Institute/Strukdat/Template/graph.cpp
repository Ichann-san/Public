#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> graph;
//vector<vector<pair<int, int>>> graph; //ini weighted, nnti fungsinya ubah ikut ini
vector<int> path_graph;

void make_graph(int n) {
    graph.resize(n);
}

void add_edge(int u, int v, bool dir) {
    graph[u].push_back(v);
    if (!dir) graph[v].push_back(u);
}

void remove_edge(int u, int v, bool dir) {
    auto it = find(graph[u].begin(), graph[u].end(), v);
    if (it != graph[u].end()) graph[u].erase(it);
    if (!dir) {
        it = find(graph[v].begin(), graph[v].end(), u);
        if (it != graph[v].end()) graph[v].erase(it);
    }
}

int get_degree(int u) {
    return graph[u].size();
}

bool adjacent(int u, int v) {
    return find(graph[u].begin(), graph[u].end(), v) != graph[u].end();
}

int bfs(int start, int target) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), -1);
    
    q.push(start);
    visited[start] = true;
    distance[start] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == target) return distance[node];
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
            }
        }
    }
    return -1;
}

int dfs(int start, int target) {
    stack<int> s;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), -1);
    
    s.push(start);
    visited[start] = true;
    distance[start] = 0;

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (node == target) return distance[node];
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
                distance[neighbor] = distance[node] + 1;
            }
        }
    }
    return -1;
}

int dijkstra(int start, int target) {
    vector<int> distance(graph.size(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [dist, node] = pq.top();
        pq.pop();

        if (node == target) return dist;
        for (int neighbor : graph[node]) {
            if (dist + 1 < distance[neighbor]) { // weight 1
                distance[neighbor] = dist + 1;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }
    return -1;
}

void path(int start, int target) {
    vector<bool> visited(graph.size(), false);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    path_graph.push_back(start);

    while (!s.empty()) {
        int node = s.top();
        if (node == target) break;
        bool found = false;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
                path_graph.push_back(neighbor);
                found = true;
                break;
            }
        }
        if (!found) {
            path_graph.pop_back();
            s.pop();
        }
    }
}

bool cycle(int start) {
    vector<bool> visited(graph.size(), false);
    stack<pair<int, int>> s;
    s.push({start, -1});
    visited[start] = true;

    while (!s.empty()) {
        auto [node, parent] = s.top();
        s.pop();
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push({neighbor, node});
            } else if (neighbor != parent) {
                return true; // cycle
            }
        }
    }
    return false;
}

void print_graph() {
    for (int i = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (int j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    make_graph(n);

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v, false); // false for undirected
    }

    cout << "\nAdjacency List:" << endl;
    print_graph();

    int u, v;
    cout << "\nCheck degree of vertex (input vertex): ";
    cin >> u;
    cout << "Degree of vertex " << u << ": " << get_degree(u) << endl;

    cout << "\nCheck adjacency (input u v): ";
    cin >> u >> v;
    cout << "Are " << u << " and " << v << " adjacent? " << (adjacent(u, v) ? "Yes" : "No") << endl;

    cout << "\nBFS shortest path (input start target): ";
    cin >> u >> v;
    cout << "Shortest path from " << u << " to " << v << " (BFS): " << bfs(u, v) << endl;

    cout << "\nDFS path length (input start target): ";
    cin >> u >> v;
    cout << "Path length from " << u << " to " << v << " (DFS): " << dfs(u, v) << endl;

    cout << "\nDijkstra shortest path (input start target): ";
    cin >> u >> v;
    cout << "Shortest path from " << u << " to " << v << " (Dijkstra): " << dijkstra(u, v) << endl;

    cout << "\nFind path (input start target): ";
    cin >> u >> v;
    path_graph.clear();
    path(u, v);
    cout << "Path from " << u << " to " << v << ": ";
    for (int node : path_graph) cout << node << " ";
    cout << endl;

    cout << "\nCycle detection (input start): ";
    cin >> u;
    cout << "Does the graph have a cycle starting from " << u << "? " << (cycle(u) ? "Yes" : "No") << endl;

    cout << "\nRemove edge (input u v): ";
    cin >> u >> v;
    remove_edge(u, v, false);
    cout << "Adjacency List after removing edge (" << u << "," << v << "):" << endl;
    print_graph();

    return 0;
}