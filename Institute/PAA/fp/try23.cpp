#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef unsigned __int128 u128;

static u128 inputnum, exp16[32];
static char input[32], pool[2048][64];
static int m, poolcnt;

void memo() {
    exp16[0] = 1;
    for (int i=1; i<32; ++i) exp16[i] = exp16[i-1]<<4;
}

int slen(const char *s) {
    int i = 0;
    while (s[i]) ++i;
    return i;
}

void scpy(char *dst, const char *src) {
    int i = 0;
    while (src[i]) { dst[i] = src[i]; ++i; }
    dst[i] = 0;
}

void srev(char *s, int n) {
    for (int i=0, j=(n-1); i<j; ++i, --j) {
        char t = s[i];
        s[i]=s[j]; s[j]=t;
    }
}

void trim0(char *dst, const char *s) {
    int i = 0;
    while (s[i] == '0' && s[i+1]) ++i;
    scpy(dst, s+i);
}

int dcmp(const char *a, const char *b) {
    char ta[64], tb[64];
    trim0(ta, a); trim0(tb, b);
    int la = slen(ta), lb = slen(tb);
    if (la != lb) return la<lb ? -1 : 1;
    for (int i = 0; i < la; ++i) { if (ta[i] != tb[i]) return ta[i] < tb[i] ? -1 : 1; }
    return 0;
}

void dadd(char *res, const char *a, const char *b) {
    int la = slen(a), lb = slen(b);
    int i = la-1, j = lb-1, carry = 0, k = 0;
    char buf[64];
    while (i >= 0 || j >= 0 || carry) {
        int da = (i >= 0 ? a[i] - '0' : 0);
        int db = (j >= 0 ? b[j] - '0' : 0);
        int sum = da + db + carry;
        buf[k++] = (char)('0' + (sum % 10));
        carry = sum / 10;
        --i; --j;
    }
    srev(buf, k);
    buf[k] = 0;
    trim0(res, buf);
}

void dsub(char *res, const char *a, const char *b) {
    int la = slen(a), lb = slen(b);
    int i = la-1, j = lb-1, borrow = 0, k = 0;
    char buf[64];
    while (i >= 0) {
        int da = a[i] - '0' - borrow;
        int db = (j >= 0 ? b[j] - '0' : 0);
        if (da < db) { da += 10; borrow = 1; } else borrow = 0;
        buf[k++] = (char)('0' + (da - db));
        --i; --j;
    }
    while (k > 1 && buf[k-1] == '0') --k;
    srev(buf, k);
    buf[k] = 0;
    scpy(res, buf);
}

void u128tostr(char *dst, u128 x) {
    if (x == 0) { dst[0] = '0'; dst[1] = 0; return; }
    char buf[64]; int k = 0;
    while (x > 0) { buf[k++] = (char)('0' + (int)(x % 10)); x /= 10; }
    srev(buf, k);
    buf[k] = 0;
    scpy(dst, buf);
}

void itostr(char *dst, int x) {
    if (x == 0) { dst[0] = '0'; dst[1] = 0; return; }
    char buf[16]; int k = 0;
    while (x > 0) { buf[k++] = (char)('0' + (x % 10)); x /= 10; }
    srev(buf, k);
    buf[k] = 0;
    scpy(dst, buf);
}

u128 hex2dec(const char *s) {
    u128 res = 0;
    for (int i = 0; s[i]; ++i) {
        res <<= 4;
        if (s[i] >= '0' && s[i] <= '9') res += (u128)(s[i] - '0');
        else res += (u128)(s[i] - 'A' + 10);
    }
    return res;
}

void dec2hex(char *dst, u128 num) {
    if (num == 0) { dst[0] = '0'; dst[1] = 0; return; }
    static const char digits[] = "0123456789ABCDEF";
    char buf[64]; int k = 0;
    while (num > 0) { buf[k++] = digits[(int)(num & 15)]; num >>= 4; }
    srev(buf, k);
    buf[k] = 0;
    scpy(dst, buf);
}

int hexlen(u128 x) {
    int len = 0;
    do { ++len; x >>= 4; } while (x>0);
    return len;
}

void found1st(char *res, u128 n) {
    int k = hexlen(n);
    char pos[64]; pos[0] = '0'; pos[1] = 0;
    char tmp[64];
    for (int d = 1; d < k; ++d) {
        u128 term = (u128)d * (u128)15 * exp16[d-1];
        u128tostr(tmp, term);
        char npos[64]; dadd(npos, pos, tmp);
        scpy(pos, npos);
    }
    u128 tail = (u128)k * (n - exp16[k-1]);
    u128tostr(tmp, tail);
    char npos[64]; dadd(npos, pos, tmp);
    scpy(res, npos);
}

int found2nd(u128 n, int off) {
    int need = off + m;
    char window[256]; int wlen = 0;
    u128 cur = n;
    while (wlen < need) {
        char h[64]; dec2hex(h, cur);
        int hlen = slen(h);
        for (int i = 0; i < hlen; ++i) window[wlen++] = h[i];
        ++cur;
    }
    window[wlen] = 0;
    for (int i = 0; i < m; ++i)
        if (window[off + i] != input[i]) return 0;
    return 1;
}

void addpool(const char *s) {
    for (int i = 0; i < poolcnt; ++i)
        if (dcmp(pool[i], s) == 0) return;
    scpy(pool[poolcnt++], s);
}

void add_res(u128 n, int off) {
    if (n == 0) return;
    if (hexlen(n) > m + 1) return;
    if (off < 0 || off >= hexlen(n)) return;
    if (!found2nd(n, off)) return;
    char pos[64]; found1st(pos, n);
    char offstr[16]; u128tostr(offstr, (u128)off);
    char final_pos[64]; dadd(final_pos, pos, offstr);
    addpool(final_pos);
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
        char rest[32];
        scpy(rest, input + a);
        int r = m-a;
        if (!rest[0] || rest[0] == '0') continue;

        for (int l = 1; l <= r; ++l) {
            char subfirst[32];
            for (int i = 0; i < l; ++i) subfirst[i] = rest[i];
            subfirst[l] = 0;
            if (subfirst[0] == '0') continue;

            u128 y = hex2dec(subfirst);
            if (hexlen(y) != l) continue;
            if (y == 0) continue;

            int off = hexlen(y - 1) - a;
            add_res(y - 1, off);
        }
    }
}

void case3() {
    for (int a = 1; a < m; ++a) {
        char head[32];
        scpy(head, input + a);
        int r = m - a;
        if (head[0] == '0') continue;

        u128 mask = exp16[a] - 1;

        char tail[32];
        for (int i = 0; i < a; ++i) tail[i] = input[i];
        tail[a] = 0;

        u128 left = hex2dec(head), right = (hex2dec(tail) + 1) & mask;

        for (int l = r + 1; l <= m + 2; ++l) {
            int extra = l - r;
            if (extra < 1 || extra >= 32) continue;

            u128 block = exp16[extra];
            u128 low = left * block, high = (left + 1) * block - 1;
            if (high < low) continue;

            u128 rem = low & mask;
            u128 delta = (right + exp16[a] - rem) & mask;
            u128 y = low + delta;

            while (y <= high) {
                if (hexlen(y) == l) {
                    u128 n = y - 1;
                    int offside = hexlen(n) - a;
                    add_res(n, offside);
                }
                if (high - y < exp16[a]) break;
                y += exp16[a];
            }
        }
    }
}

int poolsort_cmp(const void *a, const void *b) {
    return dcmp((const char *)a, (const char *)b);
}

int main() {
    memo();
    scanf("%s", input);
    inputnum = hex2dec(input);
    m = slen(input);

    case1();
    case2();
    case3();

    qsort(pool, poolcnt, 64, poolsort_cmp);
    char *first = pool[0];
    char mstr[16]; itostr(mstr, m);
    char lim[64]; dadd(lim, first, mstr);

    char *second = 0;
    for (int i = 1; i < poolcnt; ++i) {
        if (dcmp(pool[i], lim) >= 0) {
            second = pool[i];
            break;
        }
    }

    char tmp[64]; dsub(tmp, second, first);
    char result[64]; dsub(result, tmp, mstr);
    printf("%s\n", result);
    return 0;
}
