#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BigInt {
private:
    vector<int> digits;
    void hapus0() {while(digits.size()>1 && digits.back()==0) digits.pop_back();}
    
public:
    BigInt(long long n = 0) {
        if (n == 0) {
            digits.push_back(0);
            return;
        }
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }
    
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.assign(digits.size() + other.digits.size(), 0);
        
        for (size_t i = 0; i < digits.size(); i++) { //ops
            for (size_t j = 0; j < other.digits.size(); j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }
        
        for (size_t i = 0; i < result.digits.size() - 1; i++) { //carry
            result.digits[i + 1] += result.digits[i] / 10;
            result.digits[i] %= 10;
        }
        
        while (result.digits.size() > 1 && result.digits.back() == 0) result.digits.pop_back(); //0awal
        return result;
    }

    BigInt operator-(long long n) const {
        BigInt result = *this;
        int carry = n;
        
        for (size_t i = 0; i < result.digits.size() && carry > 0; i++) {
            int diff = result.digits[i] - (carry % 10); //carry
            if (diff < 0) {
                diff += 10;
                carry = carry / 10 + 1;
            } else {
                carry = carry / 10;
            }
            result.digits[i] = diff;
        }
        
        while (result.digits.size() > 1 && result.digits.back() == 0) result.digits.pop_back();
        return result;
    }
    
    void print() const {
        for (int i = digits.size() - 1; i >= 0; i--) cout << digits[i];
    }
};

BigInt binexp(long long base, long long exp) {
    BigInt result(1);
    BigInt a(base);
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * a;
        }
        a = a * a;
        exp >>= 1;
    }
    return result;
}

void solve(){
    long long x, n;
    cin >> x >> n;
    BigInt pangkat = binexp(x, n) - 1;
    pangkat.print(); cout << '/' << x-1 << endl;
}


int main() {
    int n;
    cin >> n;
    while(n--) solve();
    return 0;
}