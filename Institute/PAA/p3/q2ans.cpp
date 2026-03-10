#include<cstdio>
using namespace std;

int main(){
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        double val = 1.0;
        for(int i=1; i<9; i++) val*= (double)(n+i);
        double result = (((double)n+9.0)/9.0-(40320.0/val));
        printf("%.6lf\n", result);
    }
return 0;
}