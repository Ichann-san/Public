#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll dp[1000001];


void solve(ll n){
    for(int i=1; i<=n; i++){
        dp[i] = 1;
    }
    dp[1] = 0;
    for(int i=2; i<=n; i++){
        for(int j=2*i; j<=n; j+=i){
            dp[j] += i;
        }
    }
}

int main(){
    ll a, b;
    bool out=false;
    cin >> a >> b;
    solve(b);
    for(ll i=a; i<=b; i++){
        if(dp[i] > i && dp[i] <= b && dp[dp[i]] == i) {
            cout << i << ' ' << dp[i] << endl;
            out = true;
        }
    }
    if(!out) cout << "Absent";
return 0;
}