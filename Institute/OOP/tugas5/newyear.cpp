#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
template <typename T>
T getnum(){
    T res=0;
    char c;
    while(1){
        c=getchar_unlocked();
        if(c==' ' || c=='\n') continue;
        else break;
    }
    res=c-'0';
    while(1){
        c=getchar_unlocked();
        if(c>='0' && c<='9') res=res*10+(c-'0');
        else break;
    }
    return res;
}

class Gift{
    int t1, t2;
public:
    Gift (int a, int b) : t1(a), t2(b) {}
    int getT1() { return t1; }
    int getT2() { return t2; }
    bool operator < (Gift const &obj) const {
        return (min(t1, obj.t2) < min(t2, obj.t1));
    }
};

int n, temp1[350], temp2[350], packing, res;
vector<Gift> vect_gift;

int main(){
    n = getnum<int>();
    for(int i=0; i<n; i++) temp1[i] = getnum<int>();
    for(int i=0; i<n; i++) temp2[i] = getnum<int>();
    for(int i=0; i<n; i++){
        Gift temp(temp1[i], temp2[i]);
        vect_gift.push_back(temp);
    }
    sort(vect_gift.begin(), vect_gift.end());
    packing = 0; res = 0;
    for(int i=0; i<n; i++){
        packing += vect_gift[i].getT1();
        if(res < packing) res = packing;
        res += vect_gift[i].getT2();
    }
    printf("%d\n", res);
return 0;
}