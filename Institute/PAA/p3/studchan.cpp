#include<cstdio>
typedef long long LL;
using namespace std;

int main(){
    int t;
    LL ans[33], pow2=4LL, n;
    for(int i=2; i<=31; i++){
        ans[i-1] = (LL)i * pow2 - 1LL;
        pow2 <<= 1;
    }

    scanf("%d", &t);
    while(t--){
        scanf("%lld", &n);
        for(int i=1; i<=30; i++){
            if(n <= ans[i]){
                printf("%d\n", i);
                break;
            }
        }
    }
return 0;
}