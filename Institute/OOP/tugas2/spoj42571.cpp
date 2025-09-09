#include<stdio.h>
#include<algorithm>
using namespace std;

int main(){
int n;
scanf("%d", &n);
int left=0, right=n-1, total=100, jumlah;
pair <int, int> isi[10000];
for(int i=0; i<n; i++){
    scanf("%d", &isi[i].first);
    isi[i].second = i;
}
if(n == 1){
    printf("1");
    return 0;
} else if(n == 2){
    printf("1\n2");
    return 0;
}
sort(isi, isi+n);
while(left<right){
    jumlah = isi[left].first + isi[right].first;
    if(jumlah == total) {
        printf("%d\n%d", isi[left].second+1, isi[right].second+1);
        return 0;
    }
    else if(jumlah < total) {
        left++;
    }
    else {
        right--;
    }
}
return 0;
}