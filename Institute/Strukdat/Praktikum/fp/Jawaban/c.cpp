#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& kartu) {
    int ans = 0;
    vector<int> kiri(n);
    vector<int> kanan(n);
    kiri[0] = kartu[0];
    kanan[n - 1] = kartu[n - 1];
    for(int i = 1; i < n; i++){
        kiri[i] = max(kiri[i - 1], kartu[i]);
    }
    for(int i = n - 2; i >= 0; i--){
        kanan[i] = max(kanan[i + 1], kartu[i]);
    }
    for(int i = 1; i < n-1; i++){
        ans += min(kiri[i], kanan[i]) - kartu[i];
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<int> kartu(n);
    for(int i = 0; i < n; i++){
        cin >> kartu[i];
    }
    cout << solve(n, kartu);
return 0;
}