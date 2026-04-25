#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef unsigned __int128 u128;

class BigInt {
    string value;

    static string trim0(string s) {
        int p = (int)s.find_first_not_of('0');
        if (p == (int)string::npos) return "0";
        return s.substr(p);
    }

public:
    BigInt() : value("0") {}
    BigInt(string s) : value(trim0(s)) {}
    BigInt(u128 x) : value(u1282str(x)) {}
    string str() { return value; }

    static int compare(string a, string b) {
        string x = trim0(a), y = trim0(b);
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        if (x == y) return 0;
        return x < y ? -1 : 1;
    }

    bool operator<(BigInt o) { return compare(value, o.value) < 0; }
    bool operator>=(BigInt o) { return compare(value, o.value) >= 0; }
    bool operator==(BigInt o) { return compare(value, o.value) == 0; }

    BigInt operator+(BigInt o) {
        string x = value, y = o.value;
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

    BigInt operator-(BigInt o) {
        string x = value, y = o.value;
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
};

struct mindec {
    bool operator()(string a, string b) const { return BigInt::compare(a, b) < 0; }
};

class Hexadecimal {
public:
    static u128 hex2dec(string s) {
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
        string out, digits = "0123456789ABCDEF";
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

class Algo {
    u128 inputnum, exp16[32];//dp memoization
    string input;
    int m;
    set<string, mindec> possible;//maybe ans

    void memo() {
        exp16[0] = 1;
        for (int i = 1; i < 32; ++i) exp16[i] = exp16[i-1]<<4;
    }

    BigInt found1st(u128 n) {//hasil nurunin
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

    bool found2nd(u128 n, int off) {//offset dikit
        int need = off + (int)input.size();
        string window;
        u128 cur = n;
        while ((int)window.size() < need) {
            window += Hexadecimal::dec2hex(cur);
            ++cur;
        }
        return window.compare(off, input.size(), input) == 0;
    }

    void add_res(u128 n, int off) {
        if (n == 0) return;
        if (Hexadecimal::hexlen(n) > m + 1) return;
        if (off < 0 || off >= Hexadecimal::hexlen(n)) return;
        if (!found2nd(n, off)) return;
        BigInt pos = found1st(n)+BigInt((u128)off);
        possible.insert(pos.str());
    }

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

    void case2() {
        for (int a = 1; a < m; ++a) {
            string rest = input.substr(a);
            int r = m-a;
            if (rest.empty() || rest[0] == '0') continue;

            for (int l = 1; l <= r; ++l) {
                string subfirst = rest.substr(0, l);
                if (subfirst[0] == '0') continue;

                u128 y = Hexadecimal::hex2dec(subfirst);//y = n+1
                if (Hexadecimal::hexlen(y) != l) continue;
                if (y == 0) continue;

                int off = Hexadecimal::hexlen(y - 1) - a;
                add_res(y-1, off);
            }
        }
    }

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

        vector<string> arr(possible.begin(), possible.end());
        string first = arr[0], second;
        string lim = (BigInt(first) + BigInt((u128)m)).str();
        bool found = false;

        for (int i = 1; i < (int)arr.size(); ++i) {
            if (BigInt::compare(arr[i], lim) >= 0) {
                second = arr[i];
                found = true;
                break;
            }
        }
        string result = (BigInt(second)-BigInt(first)-BigInt(to_string(m))).str();
        printf("%s\n", result.c_str());
    }
};

int main() {
    Algo fp;
    fp.solve();
    return 0;
}