#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

inline long long fastRead()
{
    long long x = 0;
    int c = getchar_unlocked();
    while (c <= ' ')
        c = getchar_unlocked();
    bool neg = false;
    if (c == '-')
    {
        neg = true;
        c = getchar_unlocked();
    }
    for (; c >= '0' && c <= '9'; c = getchar_unlocked())
        x = x * 10 + (c - '0');
    return neg ? -x : x;
}

long double fastPow(long double base, long long exp)
{
    long double result = 1.0;
    while (exp > 0)
    {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = fastRead();
    while (t--)
    {
        long long x = fastRead();
        long long n = fastRead();

        if (x > 100 || n > 20)
        {
            cout << x << "^" << n << "-1/" << x - 1 << '\n';
            continue;
        }

        long double p = fastPow(x, n);
        long long num = (long long)(p - 1 + 0.5);
        cout << num << "/" << (x - 1) << '\n';
    }
    return 0;
}