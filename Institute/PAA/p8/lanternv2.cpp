#include <cstdio>
using namespace std;
int dp[1000001];

int main(){
    int n, k, mod=1000000007;
    scanf("%d %d", &n, &k);
    dp[0]=1;
    for (int i=1; i<=k; i++) dp[i]=((dp[i-1]<<1) < mod) ? (dp[i-1]<<1) : (dp[i-1]<<1)-mod;
    dp[k] = dp[k]-1 <0 ? dp[k]-1+mod : dp[k]-1;
    for (int i=k+1; i<=n; i++){
        dp[i] = dp[i-1]<<1; if(dp[i] >= mod) dp[i] -= mod;
        dp[i] -= dp[i-k-1]; if(dp[i] < 0) dp[i] += mod;
    }
    printf("%d\n", dp[n]);
return 0;
}