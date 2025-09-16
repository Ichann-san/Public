#include <cstdio>
#include <queue>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

struct IdTeam { int id, team; };
static inline int get_team(const vector<IdTeam>& mapv, int x) {
    int m, l = 0, r = (int)mapv.size();
    while (l < r) {
        m = (l + r) >> 1;
        if (mapv[m].id < x) l = m + 1; else r = m;
    }
    if (l < (int)mapv.size() && mapv[l].id == x) return mapv[l].team;
    return -1;
}

int main() {
    int t, n, x, id, tid;
    char cmd[16];
    if (scanf("%d", &t) != 1) return 0;
    vector<IdTeam> idmap; idmap.reserve(4096);
    vector<int> team_sizes(t, 0);
    for (int i = 0; i < t; ++i) {
        scanf("%d", &n);
        team_sizes[i] = n;
        for (int j = 0; j < n; ++j) {
            scanf("%d", &id);
            idmap.push_back({id, i});
        }
    }
    sort(idmap.begin(), idmap.end(), [](const IdTeam& a, const IdTeam& b){ return a.id < b.id; });
    vector<std::deque<int>> teamq(t); vector<unsigned char> inq(t, 0);
    queue<int> mainq;

    while (scanf("%15s", cmd) == 1) {
        if (cmd[0] == 'E') {
            if (scanf("%d", &x) != 1) break;
            tid = get_team(idmap, x);
            if (tid < 0) continue;
            if (!inq[tid]) {
                mainq.push(tid);
                inq[tid] = 1;
            }
            teamq[tid].push_back(x);
        } else if (cmd[0] == 'D') {
            if (mainq.empty()) continue;
            tid = mainq.front();
            x = teamq[tid].front();
            teamq[tid].pop_front();
            printf("%d\n", x);
            if (teamq[tid].empty()) {
                inq[tid] = 0;
                mainq.pop();
            }
        }
    }
    return 0;
}