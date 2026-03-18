#include <cstdio>
using namespace std;
typedef long long ll;
typedef __int128 int128;
ll dp[255];

void print(int128 n) {
    if (n == 0) {
        printf("0\n");
        return;
    } 
    
    char s[45];
    int len = 0;
    while (n > 0) {
        s[len++] = (char)('0' + (n % 10));
        n /= 10;
    }
    
    for (int i = len-1; i >= 0; i--) putchar(s[i]);
    putchar('\n');
}

void solve() {
    int n;
    while (scanf("%d", &n) == 1) {
        ll r = n%50;
        int128 q = n/50, ans = 0;
        
        ans += 1 * dp[r]     *     (q-1) * (q-2) * (q-3) * (q-4);
        ans -= 4 * dp[r+50]  * q *         (q-2) * (q-3) * (q-4);
        ans += 6 * dp[r+100] * q * (q-1) *         (q-3) * (q-4);
        ans -= 4 * dp[r+150] * q * (q-1) * (q-2) *         (q-4);
        ans += 1 * dp[r+200] * q * (q-1) * (q-2) * (q-3);
        print(ans/24);
    }
}

int main() {
    dp[0] = 1;
    int coins[] = {1, 5, 10, 25, 50};
    for (int i = 0; i<5; i++) {
        for (int j = coins[i]; j <= 250; j++) dp[j] += dp[j-coins[i]];
    }
    solve();
    return 0;
}