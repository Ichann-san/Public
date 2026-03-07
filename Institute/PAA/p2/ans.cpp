#include <cstdio>
using namespace std;
typedef long long ll;
ll tc, n, ans, mod=1000000007;

ll modexp(ll b, ll e, ll m) {
    ll r=1;
    while(e>0) {
        if(e&1) r=(r*b) % m;
        e >>= 1;
        b=(b*b) % m;
    } 
    return (ll) r;
}

int main() {
    scanf("%lld", &tc);

    while(tc--) {
        scanf("%lld", &n);
        
        ans=(4+(n-1)*6);
        ll tmp=(((((n-1) * (n-2)) % mod) *2) % mod);
        ans = ans+tmp;
        ll inv6=modexp(6,mod-2, mod);
        tmp=((((n-1) * (n-2) % mod) * (n-3) % mod) *inv6%mod);

        ans=ans+tmp;
        printf("%lld\n", ans%mod);
    }
}