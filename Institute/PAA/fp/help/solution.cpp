#include <cstdio>
#include <cstring>
const int MID = 2*105*105 + 2 *105;

int X, Y, par[MID], rnk[MID], cl[MID];
int top_l[105], bot_l[105], lft_l[105], rgt_l[105];
char grid[105][105];

int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }
int hid(int r, int c) { return r * Y + c; }
int vid(int r, int c) { return (X + 1) * Y + r * (Y + 1) + c; }

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return true;
    if (cl[a] != -1 && cl[b] != -1 && cl[a] != cl[b]) return false;
    if (rnk[a] < rnk[b]) { int t = a; a = b; b = t; }
    par[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
    if (cl[a] == -1) cl[a] = cl[b];
    return true;
}

bool can_merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return true;
    return cl[a] == -1 || cl[b] == -1 || cl[a] == cl[b];
}

int main() {
    scanf("%d%d", &X, &Y);
    for (int j = 0; j < Y; j++) scanf("%d", &top_l[j]);
    for (int i = 0; i < X; i++) scanf("%d%d", &lft_l[i], &rgt_l[i]);
    for (int j = 0; j < Y; j++) scanf("%d", &bot_l[j]);

    int n = (X + 1) * Y + X * (Y + 1);
    for (int i = 0; i < n; i++) { par[i] = i; rnk[i] = 0; cl[i] = -1; }

    for (int j = 0; j < Y; j++) cl[hid(0, j)] = top_l[j];
    for (int j = 0; j < Y; j++) cl[hid(X, j)] = bot_l[j];
    for (int i = 0; i < X; i++) cl[vid(i, 0)] = lft_l[i];
    for (int i = 0; i < X; i++) cl[vid(i, Y)] = rgt_l[i];

    bool ok = true;
    for (int i = 0; i < X && ok; i++) {
        for (int j = 0; j < Y && ok; j++) {
            int t = hid(i, j), b = hid(i + 1, j);
            int l = vid(i, j), r = vid(i, j + 1);

            if (can_merge(t, l) && can_merge(b, r)) {
                grid[i][j] = '/';
                unite(t, l); unite(b, r);
            } else if (can_merge(t, r) && can_merge(b, l)) {
                grid[i][j] = '\\';
                unite(t, r); unite(b, l);
            } else {
                ok = false;
            }
        }
    }

    if (!ok) {
        puts("-1");
    } else {
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) putchar(grid[i][j]);
            putchar('\n');
        }
    }
    return 0;
}
