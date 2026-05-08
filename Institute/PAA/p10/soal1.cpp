#include<cstdio>
#include<algorithm>

int main(){
    long long n, x;
    scanf("%d", &n);
    while(n--){
        scanf("%lld", &x);
        printf("%lld\n", __builtin_popcountll(x-1)%3);
    }
}