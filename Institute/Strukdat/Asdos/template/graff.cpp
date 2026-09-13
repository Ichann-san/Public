// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
vector<int> path_graph;

class grapf {
private:
    //vector<vector<int>> graph;
    vector<vector<pair<int, int>>> graph; //weighted
    vector<int> path_graph;

public:
    grapf() {}

    grapf(int n){
        graph.resize(n);
    }

    void add_edge(int u, int v, bool dir){
        graph[u].push_back(v);
        if(!dir) graph[v].push_back(u);
    }

    void remove_edge(int u, int v, bool dir){
        auto it = find(graph[u].begin(), graph[u].end(), v);
        if(it != graph[u].end()) graph[u].erase(it);
        if(!dir){
            it = find(graph[v].begin(), graph[v].end(), u);
            if(it != graph[v].end()) graph[v].erase(it);
        }
    }
    
    int bfs(int start, int target){
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

    int dfs(int start, int target){
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
        path_graph.clear();
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
        //for(auto node : path_graph) cout << node << ' ';
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
                } else if (neighbor != parent) return true; // cycle
            }
        }
        return false;
    }

    void print(){
        for (int i = 0; i < graph.size(); i++) {
            cout << i << ": ";
            for (int j : graph[i]) cout << j << " ";
            cout << endl;
        }
    }
};


int main() {
    int n, m, u, v;
    bool dir = false;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    grapf graph1;
    graph1;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph1.add_edge(u, v, dir);
    }

    cout << "\nBFS (input: start | target): "; cin >> u >> v;
    cout << u << " to " << v << " (BFS): " << graph1.bfs(u, v) << endl;

    cout << "\nDFS (input: start | target): "; cin >> u >> v;
    cout << u << " to " << v << " (DFS): " << graph1.dfs(u, v) << endl;

    cout << "\nDijkstra (input: start | target): "; cin >> u >> v;
    cout << u << " to " << v << " (Dijkstra): " << graph1.dijkstra(u, v) << endl;

    cout << "\nFind path (input: start | target): "; cin >> u >> v;
    cout << "Path from " << u << " to " << v << ": "; graph1.path(u, v);
    cout << endl;

    cout << "\nCycle (input: start): "; cin >> u;
    cout << "Cycle from " << u << "? " << (graph1.cycle(u) ? "Yes" : "No") << endl;

    cout << "\nRemove edge (input: start | target): "; cin >> u >> v;
    graph1.remove_edge(u, v, dir);

    cout << "Print graph";
    graph1.print();

    return 0;
}