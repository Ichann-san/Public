#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int baris, kolom, total, fcount, rcount, maxscore = -1;
char nama[20][15];
int status[20], kursi[5][5];
pair<int, int> teman[200];
pair<int, int> rival[200];
bool possible = false;
bool rivalMap[20][20], temanMap[20][20];

int findid(char* target) {
    for (int i = 0; i < total; i++) {
        int same = 1;
        for (int j = 0; nama[i][j] || target[j]; j++) {
            if (nama[i][j] != target[j]) {
                same = 0;
                break;
            }
        }
        if (same) return i;
    }
    return -1;
}

bool isValidPlacement(int r, int c, int id) {
    const int dr[] = {-1, 0, 1, 0};
    const int dc[] = {0, 1, 0, -1};
    
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < baris && nc >= 0 && nc < kolom && kursi[nr][nc] != -1) {
            int neighborId = kursi[nr][nc];
            if (status[id] == 1 && status[neighborId] == 1) return false;
            if (rivalMap[id][neighborId]) return false;
        }
    }
    return true;
}

int countFriendships() {
    int count = 0;
    
    for (int r = 0; r < baris; r++) {
        for (int c = 0; c < kolom; c++) {
            if (kursi[r][c] == -1) continue;
            int id = kursi[r][c];
            if (c + 1 < kolom && kursi[r][c+1] != -1) {
                int neighborId = kursi[r][c+1];
                if (temanMap[id][neighborId]) count++;
            }
            
            if (r + 1 < baris && kursi[r+1][c] != -1) {
                int neighborId = kursi[r+1][c];
                if (temanMap[id][neighborId]) count++;
            }
        }
    }
    return count;
}

void dfs(int pos, int used[], int currentScore) {
    if (pos == baris * kolom) {
        possible = true;
        maxscore = max(maxscore, currentScore);
        return;
    }
    int r = pos / kolom, c = pos % kolom;
    kursi[r][c] = -1;
    dfs(pos + 1, used, currentScore);
    
    for (int i = 0; i < total; i++) {
        if (used[i]) continue;
        if (isValidPlacement(r, c, i)) {
            int additionalScore = 0;
            kursi[r][c] = i; used[i] = 1;
            if (r > 0 && kursi[r-1][c] != -1 && temanMap[i][kursi[r-1][c]]) additionalScore++;
            if (c > 0 && kursi[r][c-1] != -1 && temanMap[i][kursi[r][c-1]]) additionalScore++;
            dfs(pos + 1, used, currentScore + additionalScore);
            used[i] = 0; kursi[r][c] = -1;
        }
    }
}

int main() {
    scanf("%d %d %d", &baris, &kolom, &total);
    for (int i = 0; i < total; i++) {
        char ststr[15];
        scanf("%s %s", nama[i], ststr);
        status[i] = (ststr[0] == 'D') ? 1 : 0;
    }
    
    memset(rivalMap, 0, sizeof(rivalMap));
    memset(temanMap, 0, sizeof(temanMap));
    scanf("%d", &fcount);

    for (int i = 0; i < fcount; i++) {
        char n1[15], n2[15];
        scanf("%s %s", n1, n2);
        int id1 = findid(n1), id2 = findid(n2);
        teman[i] = make_pair(id1, id2);
        temanMap[id1][id2] = temanMap[id2][id1] = true;
    }
    
    scanf("%d", &rcount);
    for (int i = 0; i < rcount; i++) {
        char n1[15], n2[15];
        scanf("%s %s", n1, n2);
        int id1 = findid(n1), id2 = findid(n2);
        rival[i] = make_pair(id1, id2);
        
        rivalMap[id1][id2] = rivalMap[id2][id1] = true;
    }
    
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) kursi[i][j] = -1;
    }
    
    int used[20] = {0};
    dfs(0, used, 0);
    
    if (!possible) printf("Impossible\n");
    else printf("%d\n", maxscore);
    return 0;
}