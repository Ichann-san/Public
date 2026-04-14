#include<cstdio>
using namespace std;
const int mod=5000011, maxn=100001;
int dp[maxn][2];

void solve(){
    int n, k;
    scanf("%d %d", &n, &k);
    dp[1][0] = dp[1][1] = 1;
    for(int i=2; i<=n; i++){
        dp[i][0] = (dp[i-1][1]+dp[i-1][0])%mod;//girls
        if(i-k-1 > 0) dp[i][1] = (dp[i-k-1][0]+dp[i-k-1][1])%mod;//boys
        else dp[i][1] = 1;
    }
    printf("%d\n", (dp[n][0]+dp[n][1])%mod);
}

//f(n) = f(n-1)+f(n-k-1)
int main(){
    int t, n, k;
    scanf("%d", &t);
    while(t--) solve();
return 0;
}