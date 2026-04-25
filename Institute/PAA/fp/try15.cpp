#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned __int128 u128;
typedef long long ll;
static u128 exp16[32];

string trim0s(const string& s){
    if ((int)s.find_first_not_of('0') == string::npos) return "0";
    return s.substr((int)s.find_first_not_of('0'));
}

int cmp(const string& a, const string& b){
    string x = trim0s(a), y = trim0s(b);
    if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
    if (x == y) return 0;
    return x < y ? -1 : 1;
}

string add(const string& a, const string& b){
    string x = trim0s(a), y = trim0s(b), out;
    int i = (int)x.size()-1, j = (int)y.size()-1, carry = 0;
    while (i >= 0 || j >= 0 || carry){
        int da = (i >= 0 ? x[i]-'0' : 0);
        int db = (j >= 0 ? y[j]-'0' : 0);
        int sum = da + db + carry;
        out.push_back((char)('0' + (sum % 10)));
        carry = sum/10;
        --i; --j;
    }
    reverse(out.begin(), out.end());
    return trim0s(out);
}

string sub(const string& a, const string& b){
    string x = trim0s(a), y = trim0s(b), out;
    int i = (int)x.size()-1, j = (int)y.size()-1, borrow = 0;
    while (i >= 0){
        int da = x[i]-'0' - borrow;
        int db = (j >= 0 ? y[j]-'0' : 0);
        if (da < db) {
            da += 10; borrow = 1;
        } else borrow = 0;
        out.push_back((char)('0' + (da - db)));
        --i; --j;
    }
    while (out.size() > 1 && out.back() == '0') out.pop_back();
    reverse(out.begin(), out.end());
    return trim0s(out);
}

string u1282dec(u128 x){
    if (x == 0) return "0";
    string out;
    while (x > 0){
        out.push_back((char)('0' + (int)(x % 10)));
        x /= 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

string addu128(const string& a, u128 b){ return add(a, u1282dec(b));}
struct mindec {
    bool operator()(const string& lhs, const string& rhs) const { return cmp(lhs, rhs) < 0; }
};

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

string found1st(u128 n){
    int k = len16(n);
    string pos = "0";
    for (int d = 1; d < k; ++d) {
        u128 term = (u128)d * (u128)15 * exp16[d-1];
        pos = add(pos, u1282dec(term));
    }
    u128 tail = (u128)k * (n - exp16[k-1]);
    pos = add(pos, u1282dec(tail));
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
    char temp[32];
    scanf("%s", temp);
    string input = temp;
    for (char &c : input) c = (char)toupper((unsigned char)c);
    u128 dec_inp = hex2dec(input);
    int m = (int)input.size();
    set<string, mindec> starts;

    auto add_res = [&](u128 n, int off) {//max len theory
        if (n == 0) return;
        if (len16(n) > m+1) return;
        if (off<0 || off>=len16(n)) return;
        if (!found2nd(n, off, input)) return;
        string pos = found1st(n);
        starts.insert(addu128(pos, (u128)off));
    };

    //case1
    if (input[0] != '0') {
        add_res(dec_inp, 0);
        u128 prefix = dec_inp<<4;
        for (int t = 0; t < 16; ++t) add_res(prefix+(u128)t, 0);
    }
    for (int h = 1; h <= 15; ++h) {
        u128 n = (u128)h * exp16[m] + dec_inp;
        add_res(n, 1);
    }

    //case2
    for (int a = 1; a < m; ++a) {
        string rest = input.substr(a);
        int r = m-a;
        if (rest.empty() || rest[0] == '0') continue;

        for (int l=1; l <= r; ++l) {
            string subfirst = rest.substr(0, l); //ini misal kasus "ABC" + 98
            if (subfirst[0] == '0') continue;

            u128 y = hex2dec(subfirst);   //y = n+1
            if (len16(y) != l) continue;
            if (y == 0) continue;

            int off = len16(y-1)-a;
            add_res(y-1, off);
        }
    }

    //case3
    for (int a = 1; a<m; ++a) {
        string tail = input.substr(0, a), head = input.substr(a);
        int r = m-a;
        if (head[0] == '0') continue;

        u128 mask = exp16[a]-1;
        u128 left = hex2dec(head), right = (hex2dec(tail) + 1) & mask; //y mod 16^a

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

    vector<string> arr(starts.begin(), starts.end());
    if (arr.empty()) {
        printf("0\n");
        return;
    }

    string first = arr[0], second, result;
    string lim = addu128(first, (u128)m);
    for (size_t i=1; i<arr.size(); ++i) {
        if (cmp(arr[i], lim) >= 0) {
            second = arr[i];
            break;
        }
    }

    if (second.empty()) {
        printf("0\n");
        return;
    }

    result = sub(sub(second, first), to_string(m));
    printf("%s\n", result.c_str());
}

int main() {
    solve();
    return 0;
}