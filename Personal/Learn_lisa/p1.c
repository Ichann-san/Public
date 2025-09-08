#include<stdio.h>
#include<math.h>

int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    double s = (float) (a+b+c)/2;
    double l = sqrt(s*(s-a)*(s-b)*(s-c));
    printf("%.3f %d", l, a+b+c);
return 0;
}
