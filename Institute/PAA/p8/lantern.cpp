#include <cstdio>
#define ll long long
using namespace std;
ll dp[1000001];

void solve(){
    int n, k, mod=1000000007;
    scanf("%d %d", &n, &k);
    dp[0] = 1LL;
    for (int i=1; i<k; i++) dp[i] = (dp[i-1]<<1) % mod;
    dp[k] = ((dp[k-1]<<1)%mod - 1+mod) % mod;
    for (ll i = k+1; i<=n; i++) dp[i] = ((dp[i-1]<<1)%mod - dp[i-k-1]+mod) % mod;
    printf("%lld\n", dp[n]);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--) solve();
return 0;
}
