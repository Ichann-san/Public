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
    
    void trim() { while(a.size() > 1 && a.back() == 0) a.pop_back(); }
    
    void add_internal(const ll& other, int shift) {
        if (a.size() < other.a.size() + shift) a.resize(other.a.size() + shift);
        llong carry = 0;
        for (int i = 0; i < (int)other.a.size() || carry; i++) {
            llong sum = (i + shift < (int)a.size() ? a[i + shift] : 0) + (i < (int)other.a.size() ? other.a[i] : 0) + carry;
            if (i + shift >= (int)a.size()) a.push_back(sum % BASE);
            else a[i + shift] = sum % BASE;
            carry = sum / BASE;
        }
    }
    
    void sub_internal(const ll& other, int shift) {
        llong carry = 0;
        for (int i = 0; i < (int)other.a.size() || carry; i++) {
            llong diff = a[i + shift] - (i < (int)other.a.size() ? other.a[i] : 0) - carry;
            if (diff < 0) {
                diff += BASE;
                carry = 1;
            } else carry = 0;
            a[i + shift] = diff;
        }
    }
    
    ll multiply_base(const ll& other) const {
        ll res;
        res.a.resize(a.size() + other.a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            llong carry = 0;
            for (int j = 0; j < (int)other.a.size() || carry; j++) {
                llong cur = res.a[i + j] + carry + (llong)a[i] * (j < (int)other.a.size() ? other.a[j] : 0);
                res.a[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        res.trim();
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
    ll(const ll& other) : a(other.a) {}
    
    ll& operator=(const ll& other) {
        if (this != &other) {
            a = other.a;
        }
        return *this;
    }
    
    ll operator+(const ll& other) const {
        ll res = *this;
        res.add_internal(other, 0);
        res.trim();
        return res;
    }
    
    ll operator-(const ll& other) const {
        ll res = *this;
        res.sub_internal(other, 0);
        res.trim();
        return res;
    }
    
    ll operator-(llong n) const {
        ll res = *this;
        for (int i = 0; i < (int)res.a.size() && n > 0; i++) {
            llong sub = n % BASE;
            n /= BASE;
            if (res.a[i] >= sub) res.a[i] -= sub;
            else {
                res.a[i] += BASE - sub;
                n++;
            }
        }
        res.trim();
        return res;
    }
    
    ll operator*(const ll& other) const {
        int n = max(a.size(), other.a.size()), k = n / 2;
        if (n <= KARATSUBA_CUTOFF) return multiply_base(other);
        
        ll x0, x1, y0, y1;
        x0.a = vector<int>(a.begin(), a.begin() + min((int)a.size(), k));
        x1.a = (a.size() > k) ? vector<int>(a.begin() + k, a.end()) : vector<int>();
        if (x1.a.empty()) x1.a.push_back(0);
        
        y0.a = vector<int>(other.a.begin(), other.a.begin() + min((int)other.a.size(), k));
        y1.a = (other.a.size() > k) ? vector<int>(other.a.begin() + k, other.a.end()) : vector<int>();
        if (y1.a.empty()) y1.a.push_back(0);
        
        ll z0 = x0 * y0, z2 = x1 * y1;
        ll x_sum = x0 + x1, y_sum = y0 + y1;
        ll z1 = x_sum * y_sum, res = z0;

        z1 = z1 - z0 - z2;
        res.add_internal(z1, k);
        res.add_internal(z2, 2 * k);
        res.trim();
        return res;
    }
    
    ~ll() {}
    
    void print() const {
        printf("%d", a.back());
        for (int i = (int)a.size() - 2; i >= 0; i--) printf("%08d", a[i]);
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