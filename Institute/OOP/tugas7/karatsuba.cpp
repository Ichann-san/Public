#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T>

T getnum(){
    T res=0;
    char c;
    while(1){
        c=getchar_unlocked();
        if(c==' ' || c=='\n') continue;
        else break;
    }
    res=c-'0';
    while(1){
        c=getchar_unlocked();
        if(c>='0' && c<='9') res=res*10+(c-'0');
        else break;
    }
    return res;
}

class ll {
private:
    vector<int> digits;
    void hapus0() {while(digits.size()>1 && digits.back()==0) digits.pop_back();}
    
    // Helper untuk Karatsuba
    ll karatsuba(const ll& a, const ll& b) const {
        size_t n = max(a.digits.size(), b.digits.size());
        
        // Base case: gunakan grade-school untuk bilangan kecil
        if (n <= 32) {
            return gradeSchoolMultiply(a, b);
        }
        
        size_t m = n / 2;
        
        // Split a = a1 * 10^m + a0
        ll a0, a1, b0, b1;
        a0.digits.assign(a.digits.begin(), a.digits.begin() + min(m, a.digits.size()));
        a1.digits.assign(a.digits.begin() + min(m, a.digits.size()), a.digits.end());
        
        b0.digits.assign(b.digits.begin(), b.digits.begin() + min(m, b.digits.size()));
        b1.digits.assign(b.digits.begin() + min(m, b.digits.size()), b.digits.end());
        
        if (a0.digits.empty()) a0.digits.push_back(0);
        if (a1.digits.empty()) a1.digits.push_back(0);
        if (b0.digits.empty()) b0.digits.push_back(0);
        if (b1.digits.empty()) b1.digits.push_back(0);
        
        // Karatsuba: 3 recursive multiplications
        ll z0 = karatsuba(a0, b0);           // a0 * b0
        ll z2 = karatsuba(a1, b1);           // a1 * b1
        ll z1 = karatsuba(addLL(a0, a1), addLL(b0, b1));  // (a0+a1)*(b0+b1)
        z1 = subtractLL(subtractLL(z1, z2), z0);  // z1 - z2 - z0
        
        // Result = z2 * 10^(2m) + z1 * 10^m + z0
        ll result = z0;
        result = addLL(result, shiftLeft(z1, m));
        result = addLL(result, shiftLeft(z2, 2 * m));
        
        return result;
    }
    
    // Grade-school multiplication (untuk base case)
    ll gradeSchoolMultiply(const ll& a, const ll& b) const {
        ll res;
        res.digits.assign(a.digits.size() + b.digits.size(), 0);
        
        for (size_t i = 0; i < a.digits.size(); i++) {
            for (size_t j = 0; j < b.digits.size(); j++) {
                res.digits[i+j] += a.digits[i] * b.digits[j];
            }
        }
        
        for (size_t i = 0; i < res.digits.size() - 1; i++) {
            res.digits[i + 1] += res.digits[i]/10;
            res.digits[i] %= 10;
        }
        
        res.hapus0();
        return res;
    }
    
    // Helper: shift left (multiply by 10^n)
    ll shiftLeft(const ll& num, size_t n) const {
        if (num.digits.size() == 1 && num.digits[0] == 0) return num;
        ll result;
        result.digits.assign(n, 0);
        result.digits.insert(result.digits.end(), num.digits.begin(), num.digits.end());
        return result;
    }
    
    // Helper: addition
    ll addLL(const ll& a, const ll& b) const {
        ll result;
        size_t maxSize = max(a.digits.size(), b.digits.size());
        result.digits.resize(maxSize + 1, 0);
        
        int carry = 0;
        for (size_t i = 0; i < maxSize; i++) {
            int sum = carry;
            if (i < a.digits.size()) sum += a.digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry) result.digits[maxSize] = carry;
        
        result.hapus0();
        return result;
    }
    
    // Helper: subtraction (assumes a >= b)
    ll subtractLL(const ll& a, const ll& b) const {
        ll result = a;
        int borrow = 0;
        
        for (size_t i = 0; i < b.digits.size() || borrow; i++) {
            int sub = result.digits[i] - borrow;
            if (i < b.digits.size()) sub -= b.digits[i];
            
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = sub;
        }
        
        result.hapus0();
        return result;
    }
    
public:
    ll(long long n = 0) {
        if (n == 0) {
            digits.push_back(0);
        } else {
            while (n > 0) {
                digits.push_back(n % 10);
                n /= 10;
            }
        }
    }
    
    // Operator perkalian menggunakan Karatsuba
    ll operator*(const ll& pengali) const {
        return karatsuba(*this, pengali);
    }

    ll operator-(long long n) const {
        ll res = *this;
        int carry = n;
        
        for (size_t i = 0; i < res.digits.size() && carry > 0; i++) {
            int diff = res.digits[i] - (carry % 10);
            if (diff < 0) {
                diff += 10;
                carry = carry / 10 + 1;
            } else {
                carry /= 10;
            }
            res.digits[i] = diff;
        }
        
        res.hapus0();
        return res;
    }
    
    void print() const {
        for (int i = digits.size() - 1; i >= 0; i--) printf("%d", digits[i]);
    }
};

ll binexp(long long base, long long exp) {
    ll res(1), a(base);
    
    while (exp > 0) {
        if (exp % 2) res = res * a;
        a = a * a;
        exp >>= 1;
    }
    return res;
}

void solve(){
    long long x, n;
    x = getnum<long long>(), n = getnum<long long>();
    ll pangkat = binexp(x, n) - 1;
    pangkat.print(); printf("/%lld\n", x - 1);
}

int main() {
    int n = getnum<int>();
    while(n--) solve();
    return 0;
}