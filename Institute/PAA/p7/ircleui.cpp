#include <cstdio>
#include <string>
typedef long long ll;
using namespace std;

ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1LL) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1LL;
    }
    return res;
}

ll modulo(string num, ll a) {
    ll res = 0;
    for (char c : num) res = (res * 10 + (c - '0')) % a;
    return res;
}

void solve(){
    char n[1002], k[1002];
    scanf("%s %s", n, k);

    ll ans, len = 0, mod = 1000000007LL;
    ll K = modulo(k, mod), N = modulo(n, mod-1);
    while (n[len]) len++;

    if (n[0]=='1' && len==1) ans = K;
    else {
        ll sign = ((n[len-1] - '0') & 1) ? -1 : 1, temp = (K - 1 + mod) % mod;
        ll nexp = mod_pow(temp, N, mod);
        ans = (nexp + sign*temp + mod)% mod;
    }
    printf("%lld\n", (ans==0 ? -1 : ans));
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}