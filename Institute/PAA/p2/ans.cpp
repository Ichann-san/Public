#include <cstdio>
using namespace std;
typedef long long ll;
ll tc, n, ans, mod=1000000007;

int main() {
    scanf("%lld", &tc);

    while(tc--) {
        scanf("%lld", &n);
        ll inv6 = 166666668;
        ans=(4+(n-1)*6);
        ll tmp=(((((n-1) * (n-2)) % mod) *2) % mod);
        ans = ans+tmp;
        tmp=((((n-1) * (n-2) % mod) * (n-3) % mod) *inv6%mod);

        ans=ans+tmp;
        printf("%lld\n", ans%mod);
    }
}