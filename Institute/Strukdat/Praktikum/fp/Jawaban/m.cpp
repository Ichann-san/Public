#include <bits/stdc++.h>
using namespace std;

void solve(int n, map<string, int>& buah) {
    string s, nama;
    int kuantitas;
    while(n--) {
        cin >> s >> nama >> kuantitas;
        if (s == "ADD") {
            if (buah.find(nama) == buah.end()) {
                buah[nama] = 0;
            }
            buah[nama] += kuantitas;
        }
        if (s == "SELL") {
            if (buah.find(nama) != buah.end()) {
                if (buah[nama] >= kuantitas) {
                    buah[nama] -= kuantitas;
                    cout << "SUCCESS ";
                } else {
                    cout << "not enough stock";
                }
            } else {
                cout << "item not found";
            }
            cout << endl;
        }
    }
}

int main(){
    int n;
    map<string, int> buah;
    cin >> n;
    solve(n, buah);
return 0;
}