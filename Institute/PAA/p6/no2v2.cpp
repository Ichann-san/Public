#include <cstdio>
typedef long long ll;
using namespace std;

ll binexp(ll base, int exp) {
    if (exp == 0) return 1;
    ll half = binexp(base, exp/2);
    ll res = half*half;
    if (exp%2) res *= base;
    return res;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    ll ans;
    if (n==1) ans = k;
    else {
        ll sign = (!(n%2)) ? 1 : -1;
        ans = binexp(k-1, n) + sign*(k-1);
    }
    printf("%lld", (ans==0 ? -1 : ans));
    return 0;
}