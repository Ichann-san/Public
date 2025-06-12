#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll solve(ll n, vector<pair<ll, ll>>& tps) {
    vector<ll> prefix(n), kiri(n), kanan(n);
    stack<ll> st;
    ll ans=0;
    prefix[0] = tps[0].second;
    for (ll i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + tps[i].second;
    }

    for (ll i = 0; i < n; i++) {
        while (!st.empty() && tps[st.top()].first >= tps[i].first)
            st.pop();
        kiri[i] = st.empty() ? 0 : st.top() + 1;
        st.push(i);
    }

    while (!st.empty()) st.pop();
    for (ll i = n - 1; i >= 0; i--) {
        while (!st.empty() && tps[st.top()].first >= tps[i].first)
            st.pop();
        kanan[i] = st.empty() ? n - 1 : st.top() - 1;
        st.push(i);
    }

    for (ll i = 0; i < n; i++) {
        ll total_width = prefix[kanan[i]] - (kiri[i] > 0 ? prefix[kiri[i] - 1] : 0);
        ll area = tps[i].first * total_width;
        ans = max(ans, area);
    }
    return ans;
}

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> tps(n); //tinggi, lebar
    for (ll i = 0; i < n; i++) cin >> tps[i].first;
    for (ll i = 0; i < n; i++) cin >> tps[i].second;
    cout << solve(n, tps) << endl;
    return 0;
}
