#include <cstdio>

const int mod = 1000000007;
const int mx_k = 100;
const int mx_m = 10000;

int dp[mx_k + 1][mx_m];

int main() {
    int t;
    scanf("%d", &t);

    for (int k = 1; k <= mx_k; ++k) {
        long long win = 1;
        dp[k][0] = 1;

        for (int m = 1; m < mx_m; ++m) {
            if (m < k) dp[k][m] = (int)((2LL * dp[k][m - 1]) % mod);
            else dp[k][m] = (int)win;

            if (m < k) {
                win += dp[k][m];
                if (win >= mod) win %= mod;
            } else {
                win += dp[k][m];
                win -= dp[k][m - k];
                win %= mod;
                if (win < 0) win += mod;
            }
        }
    }

    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        printf("%d\n", dp[k][n - 1]);
    }

    return 0;
}