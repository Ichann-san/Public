#include <bits/stdc++.h>
using namespace std;

const int MAXV = 3e5 + 5;
int spf[MAXV]; // smallest prime factor sieve

void buildSPF() {
    for (int i = 0; i < MAXV; i++) spf[i] = i;
    for (int i = 2; (long long)i * i < MAXV; i++)
        if (spf[i] == i)
            for (int j = i * i; j < MAXV; j += i)
                if (spf[j] == j) spf[j] = i;
}

map<int,int> factorize(int v) {
    map<int,int> f;
    while (v > 1) { f[spf[v]]++; v /= spf[v]; }
    return f;
}

// Generate all divisors of v^2 given factorization of v
vector<long long> getDivisorsOfSquare(int v) {
    auto f = factorize(v);
    vector<long long> divs = {1};
    for (auto& [p, e] : f) {
        int sz = divs.size();
        long long pe = 1;
        for (int i = 0; i < 2 * e; i++) {
            pe *= p;
            for (int j = 0; j < sz; j++)
                divs.push_back(divs[j] * pe);
        }
    }
    return divs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    buildSPF();

    int n;
    cin >> n;
    vector<int> a(n);
    unordered_set<long long> inSet;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        inSet.insert(a[i]);
    }

    long long ans = 0;

    for (int k = 0; k < n; k++) {
        long long v  = a[k];
        long long v2 = v * v;

        vector<long long> divs = getDivisorsOfSquare(a[k]);

        for (long long d : divs) {
            // Only consider d < v  =>  d != v  and  v2/d > v (so also != v)
            if (d >= v) continue;

            long long other = v2 / d;

            if (inSet.count(d) && inSet.count(other))
                ans += 2; // ordered pairs: (d, other) and (other, d)
        }
    }

    cout << ans << "\n";
    return 0;
}