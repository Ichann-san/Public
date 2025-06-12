#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> grid;
vector<vector<bool>> visited;
int tinggi, lebar;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    int size = 1;
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = cx+dx[d], ny = cy+dy[d];
            if (nx >= 0 && nx < tinggi && ny >= 0 && ny < lebar && !visited[nx][ny] && grid[nx][ny] == '+') {
                visited[nx][ny] = true;
                q.push({nx, ny});
                size++;
            }
        }
    }
    return size;
}

int main() {
    int koloni, maxkol, genap;
    koloni=maxkol=genap=0;
    cin >> tinggi >> lebar;
    grid.resize(tinggi, vector<char>(lebar));
    visited.resize(tinggi, vector<bool>(lebar, false));
    for (int i = 0; i < tinggi; ++i) {
        for (int j = 0; j < lebar; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < tinggi; ++i) {
        for (int j = 0; j < lebar; ++j) {
            if (!visited[i][j] && grid[i][j] == '+') {
                int sz = bfs(i, j);
                koloni++;
                maxkol = max(maxkol, sz);
                if (!(sz%2)) genap++;
            }
        }
    }
    cout << koloni << " " << maxkol << " " << genap << endl;
    return 0;
}