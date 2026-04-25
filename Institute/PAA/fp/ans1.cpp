#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned __int128 u128;
static u128 exp16[32];

struct BigNum {
    u128 hi;
    u128 lo;
};

struct BigLess {
    bool operator()(const BigNum& a, const BigNum& b) const {
        if (a.hi != b.hi) return a.hi < b.hi;
        return a.lo < b.lo;
    }
};

bool isZero(const BigNum& x){
    return x.hi == 0 && x.lo == 0;
}

void addU128(BigNum& a, u128 b){
    u128 old = a.lo;
    a.lo += b;
    if (a.lo < old) ++a.hi;
}

void addBig(BigNum& a, const BigNum& b){
    u128 old = a.lo;
    a.lo += b.lo;
    u128 carry = (a.lo < old) ? 1 : 0;
    a.hi += b.hi + carry;
}

BigNum subBig(const BigNum& a, const BigNum& b){
    BigNum r = a;
    u128 borrow = (r.lo < b.lo) ? 1 : 0;
    r.lo -= b.lo;
    r.hi = r.hi - b.hi - borrow;
    return r;
}

BigNum subU128(const BigNum& a, u128 b){
    BigNum r = a;
    u128 borrow = (r.lo < b) ? 1 : 0;
    r.lo -= b;
    r.hi -= borrow;
    return r;
}

BigNum mulU128Small(u128 x, int mult){
    BigNum r{0, 0};
    for (int i = 0; i < mult; ++i) addU128(r, x);
    return r;
}

int div10(BigNum& x){
    uint64_t limbs[4] = {
        (uint64_t)(x.hi >> 64),
        (uint64_t)x.hi,
        (uint64_t)(x.lo >> 64),
        (uint64_t)x.lo
    };

    u128 rem = 0;
    for (int i = 0; i < 4; ++i) {
        u128 cur = (rem << 64) | (u128)limbs[i];
        limbs[i] = (uint64_t)(cur / 10);
        rem = cur % 10;
    }

    x.hi = ((u128)limbs[0] << 64) | (u128)limbs[1];
    x.lo = ((u128)limbs[2] << 64) | (u128)limbs[3];
    return (int)rem;
}

string bigToDecimal(BigNum x){
    if (isZero(x)) return "0";
    string out;
    while (!isZero(x)) {
        int rem = div10(x);
        out.push_back((char)('0' + rem));
    }
    reverse(out.begin(), out.end());
    return out;
}

u128 hex2dec(const string& s){
    u128 res = 0;
    for (char c : s) {
        res <<= 4;
        if (c>='0' && c<='9') res += (u128)(c-'0');
        else res += (u128)(c-'A'+10);
    }
    return res;
}

string dec2hex(u128 num){
    if (num == 0) return "0";
    const string digits = "0123456789ABCDEF";
    string out;
    while (num > 0) {
        char temp = digits[(int)(num&15)];
        out = temp+out;
        num >>= 4;
    }
    return out;
}

int len16(u128 x){
    int len = 0;
    do {
        ++len;
        x >>= 4;
    } while (x > 0);
    return len;
}

BigNum found1st(u128 n){
    int k = len16(n);
    BigNum pos{0, 0};
    for (int d = 1; d < k; ++d) {
        u128 term = (u128)d * (u128)15 * exp16[d-1];
        addU128(pos, term);
    }

    u128 diff = n - exp16[k-1];
    BigNum tail = mulU128Small(diff, k);
    addBig(pos, tail);
    return pos;
}

bool found2nd(u128 n, int off, const string& input){
    int need = off+(int)input.size();
    string window;
    u128 cur = n;
    while ((int)window.size() < need) {
        window += dec2hex(cur);
        ++cur;
    }
    return window.compare(off, input.size(), input) == 0;
}

void solve() {
    //memo dp
    exp16[0] = 1;
    for (int i = 1; i < 32; ++i) exp16[i] = exp16[i-1] << 4;

    //input
    string input;
    cin >> input;
    for (char &c : input) c = (char)toupper((unsigned char)c);
    u128 dec_inp = hex2dec(input);
    int m = (int)input.size();
    set<BigNum, BigLess> starts;

    auto add_res = [&](u128 n, int off) {//max len theory
        if (n == 0) return;
        if (len16(n) > m+1) return;
        if (off<0 || off>=len16(n)) return;
        if (!found2nd(n, off, input)) return;
        BigNum start = found1st(n);
        addU128(start, (u128)off);
        starts.insert(start);
    };

    // Case 1: occurrence entirely inside one number (length <= m+1 bound).
    if (input[0] != '0') {
        add_res(dec_inp, 0);
        u128 prefix = dec_inp<<4;
        for (int t = 0; t < 16; ++t) add_res(prefix+(u128)t, 0);
    }
    for (int h = 1; h <= 15; ++h) {
        u128 n = (u128)h * exp16[m] + dec_inp;
        add_res(n, 1);
    }

    // Case 2: crossing a boundary and at least one full number after that boundary.
    for (int a = 1; a < m; ++a) {
        string rest = input.substr(a);
        int r = m-a;
        if (rest.empty() || rest[0] == '0') continue;

        for (int l=1; l <= r; ++l) {
            string subfirst = rest.substr(0, l); //ini misal kasus "ABC" + 98
            if (subfirst[0] == '0') continue;

            u128 y = hex2dec(subfirst);   // y = n+1
            if (len16(y) != l) continue;
            if (y == 0) continue;

            int off = len16(y-1) - a;
            add_res(y-1, off);
        }
    }

    // Case 3: crossing a boundary but ending inside n+1 (no full number after boundary).
    for (int a = 1; a<m; ++a) {
        string tail = input.substr(0, a), head = input.substr(a);
        int r = m-a;
        if (head[0] == '0') continue;

        u128 mask = exp16[a]-1;
        u128 left = hex2dec(head), right = (hex2dec(tail) + 1) & mask; // y mod 16^a

        for (int l = r+1; l <= m+2; ++l) {
            int extra = l-r;
            if (extra < 1 || extra >= 32) continue;

            u128 block = exp16[extra];
            u128 low = left*block, high = (left+1) * block - 1;
            if (high < low) continue;

            u128 rem = low & mask;
            u128 delta = (right + exp16[a] - rem) & mask;
            u128 y = low + delta;

            while (y <= high) {
                if (len16(y) == l) {
                    u128 n = y-1;
                    int offside = len16(n)-a;
                    add_res(n, offside);
                }
                if (high-y < exp16[a]) break;
                y += exp16[a];
            }
        }
    }

    vector<BigNum> arr(starts.begin(), starts.end());
    if (arr.empty()) {
        printf("0\n");
        return;
    }

    BigNum first = arr[0], second{0, 0}, result{0, 0};
    bool foundSecond = false;
    for (size_t i=1; i<arr.size(); ++i) {
        BigNum lim = first;
        addU128(lim, (u128)m);
        if (!BigLess{}(arr[i], lim)) {
            second = arr[i];
            foundSecond = true;
            break;
        }
    }

    if (!foundSecond) {
        printf("0\n");
        return;
    }

    result = subBig(second, first);
    result = subU128(result, (u128)m);
    if (isZero(result)) printf("0\n");
    else cout << bigToDecimal(result) << "\n";
}

int main() {
    solve();
    return 0;
}