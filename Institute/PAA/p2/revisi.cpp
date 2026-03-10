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
        
    ll inv6=modexp(6,mod-2, mod);
    printf("%lld\n", inv6);
return 0;
}