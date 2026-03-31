
#include <cstdio>
typedef long long ll;
using namespace std;
//1 same    2 diff

int n, k;
ll memo1[20], memo2[20];
bool visited1[20], visited2[20];

ll diff_color(int i);
ll same_color(int i);

int main() {
    scanf("%d %d", &n, &k);

    ll ans;
    if (n == 1) {
        ans = k;
    } else {
        ans = (ll)k * diff_color(n);
    }

    cout << (ans == 0 ? -1 : ans) << endl;
    return 0;
}

ll same_color(int i) {
    if (i == 2) return 0;
    if (visited1[i]) return memo1[i];
    visited1[i] = true;
    return memo1[i] = diff_color(i - 1);
}

ll diff_color(int i) {
    if (i == 2) return k - 1;
    if (visited2[i]) return memo2[i];
    visited2[i] = true;
    return memo2[i] = same_color(i - 1) * (k - 1) + diff_color(i - 1) * (k - 2);
}