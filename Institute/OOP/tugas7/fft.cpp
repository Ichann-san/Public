#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
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
    
    // FFT Implementation
    typedef complex<double> cd;
    const double PI = acos(-1);
    
    void fft(vector<cd>& a, bool invert) const {
        int n = a.size();
        if (n == 1) return;
        
        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        
        // Cooley-Tukey FFT
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        
        if (invert) {
            for (cd& x : a) x /= n;
        }
    }
    
    // FFT-based multiplication
    ll fftMultiply(const ll& a, const ll& b) const {
        vector<cd> fa(a.digits.begin(), a.digits.end());
        vector<cd> fb(b.digits.begin(), b.digits.end());
        
        size_t n = 1;
        while (n < a.digits.size() + b.digits.size()) n <<= 1;
        
        fa.resize(n);
        fb.resize(n);
        
        fft(fa, false);
        fft(fb, false);
        
        for (size_t i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }
        
        fft(fa, true);
        
        ll result;
        result.digits.resize(n);
        
        // Convert back to integer with carry handling
        long long carry = 0;
        for (size_t i = 0; i < n; i++) {
            long long val = (long long)(fa[i].real() + 0.5) + carry;
            result.digits[i] = val % 10;
            carry = val / 10;
        }
        
        while (carry > 0) {
            result.digits.push_back(carry % 10);
            carry /= 10;
        }
        
        result.hapus0();
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
    
    // Operator perkalian: gunakan FFT untuk bilangan besar
    ll operator*(const ll& pengali) const {
        // Gunakan grade-school untuk bilangan kecil (menghindari overhead FFT)
        if (digits.size() + pengali.digits.size() < 128) {
            return gradeSchoolMultiply(*this, pengali);
        }
        return fftMultiply(*this, pengali);
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