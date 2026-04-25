#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef unsigned __int128 u128;

// ─────────────────────────────────────────────────────────────
//  BigInt — arbitrary-precision unsigned decimal (string)
// ─────────────────────────────────────────────────────────────
class BigInt {
    string value;

    static string trim0(string& s) {
        if ((int)s.find_first_not_of('0') == string::npos) return "0";
        return s.substr((int)s.find_first_not_of('0'));
    }

public:
    BigInt() : value("0") {}
    BigInt(string& s) : value(trim0(s)) {}
    BigInt(u128 x) : value(u1282str(x)) {}
    const string& str() const { return value; }

    // ── comparison ──
    static int compare(string& a, string& b) {
        string x = trim0(a), y = trim0(b);
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        if (x == y) return 0;
        return x < y ? -1 : 1;
    }

    bool operator<(BigInt& o) { return compare(value, o.value) < 0; }
    bool operator>=(BigInt& o) { return compare(value, o.value) >= 0; }
    bool operator==(BigInt& o) { return compare(value, o.value) == 0; }

    // ── addition ──
    BigInt operator+(BigInt& o) {
        string& x = value; string& y = o.value;
        string out;
        int i = (int)x.size()-1, j = (int)y.size()-1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int da = (i >= 0 ? x[i] - '0' : 0);
            int db = (j >= 0 ? y[j] - '0' : 0);
            int sum = da + db + carry;
            out.push_back((char)('0' + (sum % 10)));
            carry = sum/10;
            --i; --j;
        }
        reverse(out.begin(), out.end());
        return BigInt(out);
    }

    // ── subtraction (assumes *this >= o) ──
    BigInt operator-(BigInt& o) {
        string& x = value; string& y = o.value;
        string out;
        int i = (int)x.size()-1, j = (int)y.size()-1, borrow = 0;
        while (i >= 0) {
            int da = x[i] - '0' - borrow;
            int db = (j >= 0 ? y[j] - '0' : 0);
            if (da < db) {
                da += 10;
                borrow = 1;
            } else borrow = 0;
            out.push_back((char)('0' + (da - db)));
            --i; --j;
        }
        while (out.size() > 1 && out.back() == '0') out.pop_back();
        reverse(out.begin(), out.end());
        return BigInt(out);
    }

    // ── u128 → decimal string ──
    static string u1282str(u128 x) {
        if (x==0) return "0";
        string out;
        while (x > 0) {
            out.push_back((char)('0' + (int)(x % 10)));
            x/=10;
        }
        reverse(out.begin(), out.end());
        return out;
    }

    // ── comparator for use in ordered containers ──
    struct Less {
        bool operator()(BigInt& a, BigInt& b) { return a < b; }
    };
};

// ─────────────────────────────────────────────────────────────
//  Hexadecimal — u128 / hexadecimal conversion helpers
// ─────────────────────────────────────────────────────────────
class Hexadecimal {
public:
    static u128 hex2dec(string& s) {
        u128 res = 0;
        for (char c : s) {
            res <<= 4;
            if (c >= '0' && c <= '9') res += (u128)(c - '0');
            else res += (u128)(c - 'A' + 10);
        }
        return res;
    }

    static string dec2hex(u128 num) {
        if (num == 0) return "0";
        const string digits = "0123456789ABCDEF";
        string out;
        while (num > 0) {
            out = digits[(int)(num & 15)] + out;
            num >>= 4;
        }
        return out;
    }

    static int hexlen(u128 x) {
        int len = 0;
        do {
            ++len;
            x >>= 4;
        } while (x > 0);
        return len;
    }
};

// ─────────────────────────────────────────────────────────────
//  Algo — main solver
// ─────────────────────────────────────────────────────────────
class Algo {
    u128 inputnum, exp16[32];           // precomputed powers of 16
    string input;             // uppercase hex pattern to find
    int m;                    // length of input
    set<BigInt, BigInt::Less> starts; // candidate starting positions

    // ── precompute powers of 16 ──
    void memo() {
        exp16[0] = 1;
        for (int i = 1; i < 32; ++i) exp16[i] = exp16[i-1]<<4;
    }

    // ── position of the first digit of n in the Champernowne-like hex sequence ──
    BigInt found1st(u128 n) {
        int k = Hexadecimal::hexlen(n);
        BigInt pos;
        for (int d = 1; d < k; ++d) {
            u128 term = (u128)d * (u128)15 * exp16[d-1];
            pos = pos+BigInt(term);
        }
        u128 tail = (u128)k * (n - exp16[k-1]);
        pos = pos+BigInt(tail);
        return pos;
    }

    // ── verify that `input` appears at offset `off` inside dec2hex(n)||dec2hex(n+1)||… ──
    bool found2nd(u128 n, int off) {
        int need = off + (int)input.size();
        string window;
        u128 cur = n;
        while ((int)window.size() < need) {
            window += Hexadecimal::dec2hex(cur);
            ++cur;
        }
        return window.compare(off, input.size(), input) == 0;
    }

    // ── try to register a candidate (n, off) ──
    void add_res(u128 n, int off) {
        if (n == 0) return;
        if (Hexadecimal::hexlen(n) > m + 1) return;
        if (off < 0 || off >= Hexadecimal::hexlen(n)) return;
        if (!found2nd(n, off)) return;
        BigInt pos = found1st(n)+BigInt((u128)off);
        starts.insert(pos);
    }

    // ── case 1: pattern contained within a single number or starts at its beginning ──
    void case1() {
        if (input[0] != '0') {
            add_res(inputnum, 0);
            u128 prefix = inputnum << 4;
            for (int t = 0; t < 16; ++t) add_res(prefix + (u128)t, 0);
        }
        for (int h = 1; h <= 15; ++h) {
            u128 n = (u128)h * exp16[m] + inputnum;
            add_res(n, 1);
        }
    }

    // ── case 2: pattern straddles two consecutive numbers (split at position a) ──
    void case2() {
        for (int a = 1; a < m; ++a) {
            string rest = input.substr(a);
            int r = m-a;
            if (rest.empty() || rest[0] == '0') continue;

            for (int l = 1; l <= r; ++l) {
                string subfirst = rest.substr(0, l);
                if (subfirst[0] == '0') continue;

                u128 y = Hexadecimal::hex2dec(subfirst);   // y = n+1
                if (Hexadecimal::hexlen(y) != l) continue;
                if (y == 0) continue;

                int off = Hexadecimal::hexlen(y - 1) - a;
                add_res(y-1, off);
            }
        }
    }

    // ── case 3: pattern straddles with carry / wrap-around alignment ──
    void case3() {
        for (int a = 1; a < m; ++a) {
            string tail = input.substr(0, a), head = input.substr(a);
            int r = m-a;
            if (head[0] == '0') continue;

            u128 mask  = exp16[a] - 1;
            u128 left  = Hexadecimal::hex2dec(head), right = (Hexadecimal::hex2dec(tail)+1) & mask;

            for (int l = r + 1; l <= m + 2; ++l) {
                int extra = l-r;
                if (extra < 1 || extra >= 32) continue;

                u128 block = exp16[extra];
                u128 low = left*block, high = (left + 1)*block - 1;
                if (high < low) continue;

                u128 rem   = low & mask;
                u128 delta = (right + exp16[a] - rem) & mask;
                u128 y     = low + delta;

                while (y <= high) {
                    if (Hexadecimal::hexlen(y) == l) {
                        u128 n = y - 1;
                        int offside = Hexadecimal::hexlen(n) - a;
                        add_res(n, offside);
                    }
                    if (high-y < exp16[a]) break;
                    y += exp16[a];
                }
            }
        }
    }

public:
    // ── read input, run all cases, print result ──
    void solve() {
        memo();
        char temp[32];
        scanf("%s", temp);

        input = temp;
        inputnum = Hexadecimal::hex2dec(input);
        m = (int)input.size();

        case1();
        case2();
        case3();

        vector<BigInt> arr(starts.begin(), starts.end());
        BigInt first = arr[0], second;
        BigInt lim   = first + BigInt((u128)m);
        bool found = false;

        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] >= lim) {
                second = arr[i];
                found = true;
                break;
            }
        }

        BigInt result = (second - first) - BigInt(to_string(m));
        printf("%s\n", result.str().c_str());
    }
};

int main() {
    Algo solver;
    solver.solve();
    return 0;
}