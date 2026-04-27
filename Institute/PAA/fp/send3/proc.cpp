#include <cstdio>
#include <cstring>
typedef unsigned __int128 u128;

static u128 inputnum, pref[32], exp16[32];
static char input[32], prepos[32][48], pool[4096][64];
static int m, poolcnt, preposlen[32];
static unsigned char hval[32], poollen[4096];
static const char HEXD[] = "0123456789ABCDEF";

int hexlen(u128 x) {
    int len = 0;
    do { ++len; x >>= 4; } while (x);
    return len;
}

int u128tostr(char *dst, u128 x) {
    if (!x) { dst[0]='0'; dst[1]=0; return 1; }
    char buf[42]; int k=0;
    while (x) { buf[k++]=(char)('0'+(int)(x%10)); x/=10; }
    for (int i=0; i<k; ++i) dst[i]=buf[k-1-i];
    dst[k]=0;
    return k;
}

int dadd(char *res, const char *a, int la, const char *b, int lb) {
    int i=la-1, j=lb-1, carry=0, k=0;
    char buf[48];
    while (i>=0 || j>=0 || carry) {
        int s = carry;
        if (i>=0) s += a[i--]-'0';
        if (j>=0) s += b[j--]-'0';
        buf[k++] = (char)('0'+(s%10));
        carry = s/10;
    }
    for (int i2=0; i2<k; ++i2) res[i2]=buf[k-1-i2];
    res[k]=0;
    return k;
}

int dsub(char *res, const char *a, int la, const char *b, int lb) {
    int i=la-1, j=lb-1, borrow=0, k=0;
    char buf[48];
    while (i>=0) {
        int d = a[i--]-'0'-borrow;
        if (j>=0) d -= b[j--]-'0';
        if (d<0) { d+=10; borrow=1; } else borrow=0;
        buf[k++] = (char)('0'+d);
    }
    while (k>1 && buf[k-1]=='0') --k;
    for (int i2=0; i2<k; ++i2) res[i2]=buf[k-1-i2];
    res[k]=0;
    return k;
}

int dcmp(const char *a, int la, const char *b, int lb) {
    if (la!=lb) return la<lb ? -1 : 1;
    for (int i=0; i<la; ++i) { if (a[i]!=b[i]) return a[i]<b[i] ? -1 : 1; }
    return 0;
}

void precompute() {
    exp16[0]=1;
    for (int i=1; i<32; ++i) exp16[i]=exp16[i-1]<<4;

    prepos[0][0]='0'; prepos[0][1]=0; preposlen[0]=1;
    prepos[1][0]='0'; prepos[1][1]=0; preposlen[1]=1;
    for (int k=2; k<=31; ++k) {
        char term[42];
        u128 t = (u128)(k-1) * (u128)15 * exp16[k-2];
        int tl = u128tostr(term, t);
        preposlen[k] = dadd(prepos[k], prepos[k-1], preposlen[k-1], term, tl);
    }
}

int calcpos(char *res, u128 n) {
    int k = hexlen(n);
    u128 tail = (u128)k * (n - exp16[k-1]);
    char ts[42]; int tl = u128tostr(ts, tail);
    return dadd(res, prepos[k], preposlen[k], ts, tl);
}

int verify(u128 n, int off) {
    int need = off + m;
    char window[128]; int wlen=0;
    u128 cur = n;
    while (wlen < need) {
        u128 x = cur;
        char buf[64]; int bk=0;
        do { buf[bk++]=HEXD[(int)(x&15)]; x>>=4; } while(x);
        for (int i=bk-1; i>=0; --i) window[wlen++]=buf[i];
        ++cur;
    }
    return memcmp(window+off, input, m)==0;
}

void addpool(const char *s, int sl) {
    for (int i=0; i<poolcnt; ++i) { if (poollen[i]==sl && memcmp(pool[i],s,sl)==0) return; }
    memcpy(pool[poolcnt], s, sl);
    pool[poolcnt][sl]=0;
    poollen[poolcnt]=(unsigned char)sl;
    ++poolcnt;
}

void add_res(u128 n, int off) {
    if (!n) return;
    int hl = hexlen(n);
    if (hl > m+1) return;
    if (off<0 || off>=hl) return;
    if (!verify(n, off)) return;
    char pos[48]; int pl = calcpos(pos, n);
    if (off) {
        char offstr[8]; int ol = u128tostr(offstr, (u128)off);
        char fp[48]; int fl = dadd(fp, pos, pl, offstr, ol);
        addpool(fp, fl);
    } else addpool(pos, pl);
}

void case1() {
    if (input[0]!='0') {
        add_res(inputnum, 0);
        u128 prefix = inputnum<<4;
        for (int t=0; t<16; ++t) add_res(prefix+(u128)t, 0);
    }
    for (int h=1; h<=15; ++h) add_res((u128)h*exp16[m]+inputnum, 1);
}

void case2() {
    for (int a=1; a<m; ++a) {
        if (input[a]=='0') continue;
        u128 y = 0;
        for (int l=1; l<=(m-a); ++l) {
            y = (y<<4) + (u128)hval[a+l-1];
            add_res(y-1, hexlen(y-1)-a);
        }
    }
}

void case3() {
    for (int a=1; a<m; ++a) {
        if (input[a]=='0') continue;
        int r = m-a;
        u128 mask = exp16[a]-1, tv = pref[a];
        u128 left = pref[m] - pref[a]*exp16[m-a];
        u128 right = (tv+1)&mask;

        for (int l=r+1; l<=m+2; ++l) {
            if ((l-r)<1 || (l-r)>=32) continue;
            u128 block = exp16[(l-r)];
            u128 low = left*block, high = (left+1)*block-1;
            if (high<low) continue;
            u128 rem = low&mask;
            u128 delta = (right+exp16[a]-rem)&mask;
            u128 y = low+delta;
            while (y<=high) {
                u128 n=y-1;
                add_res(n, hexlen(n)-a);
                if (high-y<exp16[a]) break;
                y += exp16[a];
            }
        }
    }
}

int main() {
    precompute();
    scanf("%s", input);
    m = (int)strlen(input);
    pref[0]=0;
    u128 iv=0;
    for (int i=0; i<m; ++i) {
        int v = (input[i] <= '9') ? (input[i]-'0') : (input[i]-'A'+10);
        hval[i] = (unsigned char)v;
        iv = (iv<<4) + (u128)v;
        pref[i+1] = iv;
    }
    inputnum = iv;

    case1();
    case2();
    case3();

    for (int i=1; i<poolcnt; ++i) {
        int li = poollen[i];
        char key[64]; memcpy(key, pool[i], li+1);
        int j=i-1;
        while (j>=0 && dcmp(pool[j],poollen[j],key,li)>0) {
            int lj = poollen[j];
            memcpy(pool[j+1], pool[j], lj+1);
            poollen[j+1] = (unsigned char)lj;
            --j;
        }
        memcpy(pool[j+1], key, li+1);
        poollen[j+1] = (unsigned char)li;
    }

    char *first = pool[0]; int fl = poollen[0];
    char *second = 0;      int sl=0;
    char mstr[8];          int ml = u128tostr(mstr, (u128)m);
    char lim[48];          int ll = dadd(lim, first, fl, mstr, ml);

    for (int i=1; i<poolcnt; ++i) {
        int il = poollen[i];
        if (dcmp(pool[i],il,lim,ll)>=0) {
            second = pool[i]; sl=il;
            break;
        }
    }

    char tmp[48]; int tl = dsub(tmp, second, sl, first, fl);
    char result[48]; dsub(result, tmp, tl, mstr, ml);
    printf("%s\n", result);
    return 0;
}