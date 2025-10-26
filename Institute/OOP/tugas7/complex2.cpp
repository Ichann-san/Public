#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ll {
private:
    vector<int> digits;
    void hapus0() {while(digits.size()>1 && digits.back()==0) digits.pop_back();}
    
public:
    ll(long long n = 0) {
        do{
            digits.push_back(n%10);
            n /= 10;
        } while (n>0);
    }
    
    ll operator*(const ll& pengali) const {
        ll res;
        res.digits.assign(digits.size() + pengali.digits.size(), 0);
        
        for (size_t i = 0; i < digits.size(); i++) { //ops
            for (size_t j = 0; j < pengali.digits.size(); j++) {
                res.digits[i + j] += digits[i] * pengali.digits[j];
            }
        }
        
        for (size_t i = 0; i < res.digits.size() - 1; i++) { //carry
            res.digits[i + 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }

        res.hapus0();
        return res;
    }

    ll operator-(long long n) const {
        ll res = *this;
        int carry = n;
        
        for (size_t i = 0; i < res.digits.size() && carry > 0; i++) {
            int diff = res.digits[i] - (carry % 10); //carry
            if (diff < 0) {
                diff += 10;
                carry = carry / 10 + 1;
            } else {
                carry = carry / 10;
            }
            res.digits[i] = diff;
        }
        
        res.hapus0();
        return res;
    }
    
    void print() const {
        for (int i = digits.size() - 1; i >= 0; i--) cout << digits[i];
    }
};

ll binexp(long long base, long long exp) {
    ll res(1), a(base);
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = res * a;
        }
        a = a * a;
        exp >>= 1;
    }
    return res;
}

void solve(){
    long long x, n;
    cin >> x >> n;
    ll pangkat = binexp(x, n) - 1;
    pangkat.print(); cout << '/' << x-1 << endl;
}


int main() {
    int n;
    cin >> n;
    while(n--) solve();
    return 0;
}