#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long llong;

class ll {
private:
    static const int BASE = 100000000;
    static const int KARATSUBA_CUTOFF = 32;
    vector<int> a;
    
    void trim() {
        while(a.size() > 1 && a.back() == 0) a.pop_back();
    }
    
    static void add(vector<int>& res, const vector<int>& x, int shift) {
        if (res.size() < x.size() + shift) res.resize(x.size() + shift);
        llong carry = 0;
        for (int i = 0; i < (int)x.size() || carry; i++) {
            llong sum = (i + shift < (int)res.size() ? res[i + shift] : 0) + 
                       (i < (int)x.size() ? x[i] : 0) + carry;
            if (i + shift >= (int)res.size()) res.push_back(sum % BASE);
            else res[i + shift] = sum % BASE;
            carry = sum / BASE;
        }
    }
    
    static void sub(vector<int>& res, const vector<int>& x, int shift) {
        llong carry = 0;
        for (int i = 0; i < (int)x.size() || carry; i++) {
            llong diff = res[i + shift] - (i < (int)x.size() ? x[i] : 0) - carry;
            if (diff < 0) {
                diff += BASE;
                carry = 1;
            } else {
                carry = 0;
            }
            res[i + shift] = diff;
        }
    }
    
    static vector<int> multiply_simple(const vector<int>& x, const vector<int>& y) {
        vector<int> res(x.size() + y.size());
        for (int i = 0; i < (int)x.size(); i++) {
            llong carry = 0;
            for (int j = 0; j < (int)y.size() || carry; j++) {
                llong cur = res[i + j] + carry + 
                           (llong)x[i] * (j < (int)y.size() ? y[j] : 0);
                res[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        while (res.size() > 1 && res.back() == 0) res.pop_back();
        return res;
    }
    
    static vector<int> karatsuba(const vector<int>& x, const vector<int>& y) {
        int n = max(x.size(), y.size());
        if (n <= KARATSUBA_CUTOFF) return multiply_simple(x, y);
        
        int k = n / 2;
        vector<int> x0(x.begin(), x.begin() + min((int)x.size(), k));
        vector<int> x1(x.size() > k ? x.begin() + k : x.end(), x.end());
        vector<int> y0(y.begin(), y.begin() + min((int)y.size(), k));
        vector<int> y1(y.size() > k ? y.begin() + k : y.end(), y.end());
        
        vector<int> z0 = karatsuba(x0, y0);
        vector<int> z2 = karatsuba(x1, y1);
        
        vector<int> x_sum = x0; add(x_sum, x1, 0);
        vector<int> y_sum = y0; add(y_sum, y1, 0);
        vector<int> z1 = karatsuba(x_sum, y_sum);
        sub(z1, z0, 0);
        sub(z1, z2, 0);
        
        vector<int> res = z0;
        add(res, z1, k);
        add(res, z2, 2 * k);
        
        while (res.size() > 1 && res.back() == 0) res.pop_back();
        return res;
    }
    
public:
    ll(llong n = 0) {
        do {
            a.push_back(n % BASE);
            n /= BASE;
        } while (n > 0);
    }
    
    ll(const vector<int>& v) : a(v) { trim(); }
    
    ll operator*(const ll& b) const {
        return ll(karatsuba(a, b.a));
    }

    ll operator-(llong n) const {
        ll res = *this;
        for (int i = 0; i < (int)res.a.size() && n > 0; i++) {
            llong sub = n % BASE;
            n /= BASE;
            if (res.a[i] >= sub) {
                res.a[i] -= sub;
            } else {
                res.a[i] += BASE - sub;
                n++;
            }
        }
        res.trim();
        return res;
    }
    
    void print() const {
        printf("%d", a.back());
        for (int i = (int)a.size() - 2; i >= 0; i--) 
            printf("%08d", a[i]);
    }
};

ll binexp(int base, int exp) {
    ll res(1), a(base);
    while (exp) {
        if (exp & 1) res = res * a;
        exp >>= 1;
        if (exp) a = a * a;
    }
    return res;
}

inline int readInt() {
    int num = 0, c;
    while ((c = getchar_unlocked()) < '0');
    do num = num * 10 + c - '0';
    while ((c = getchar_unlocked()) >= '0');
    return num;
}

int main() {
    int t = readInt();
    while(t--) {
        int x = readInt(), n = readInt();
        ll result = binexp(x, n) - 1;
        result.print();
        putchar_unlocked('/');
        printf("%d\n", x - 1);
    }
    return 0;
}