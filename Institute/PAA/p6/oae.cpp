#include <cstdio>
using namespace std;
typedef long long ll;
ll mod = 314159;

ll binexp(ll b, ll e, ll m){
    ll r = 1;
    while(e > 0){
        if (e&1) r = (r*b)%m;
        e >>=1;
        b = (b*b)%m;
    }
    return(ll)r;
}

int main(){
    ll t, n, res, inv2 = binexp(2, mod-2, mod);
    scanf("%lld", &t);
    while(t--){
        scanf("%lld", &n);
        res = ((binexp(8, n, mod) +binexp(10,n,mod))*inv2)%mod;
        printf("%lld\n", res);
    }
}
