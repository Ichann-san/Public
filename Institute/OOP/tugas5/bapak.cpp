#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct S_gift{
    int t1, t2;
} gift;

bool compare(gift a, gift b){
    return (min(a.t1, b.t2) < min(a.t2, b.t1));
}

int n, temp1[350], temp2[350], packing, res;

int main(){
    vector<gift> vect_gift;
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &temp1[i]);
    for(int i=0; i<n; i++) scanf("%d", &temp2[i]);
    for(int i=0; i<n; i++){
        gift temp;
        temp.t1 = temp1[i];
        temp.t2 = temp2[i];
        vect_gift.push_back(temp);
    }
    sort(vect_gift.begin(), vect_gift.end(), compare);
    packing = 0; res = 0;
    for(int i=0; i<n; i++){
        packing += vect_gift[i].t1;
        if(res < packing) res = packing;
        res += vect_gift[i].t2;
    }
    printf("%d\n", res);
return 0;
}