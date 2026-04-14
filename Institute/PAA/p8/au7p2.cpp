#include<cstdio>
using namespace std;
const int mod=5000011, maxn=100001;
int dp[maxn]={0};

void solve(){
    int n, k;
    scanf("%d %d", &n, &k);
    dp[1]=2;
    for(int i=2; i<=n; i++){
        if(i-k-1 > 0) dp[i] = (dp[i-1]+dp[i-k-1])%mod;
        else dp[i] = i+1;
    }
    printf("%d\n", dp[n]%mod);
}

//f(n) = f(n-1)+f(n-k-1)
int main(){
    int t;
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}
