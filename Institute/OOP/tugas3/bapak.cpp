#include <map>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

queue<int> team, each_team[1001];
map<int,int> on_team;

int main(){
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;i++){
        int n;
        scanf("%d",&n);
        for(int j=0;j<n;j++){
            int id;
            scanf("%d",&id);
            on_team[id] = i;
        }
    }

    char ch[20];
    while(scanf("%s",ch) != EOF){
        if(ch[0] == 'D'){
            int can_team = team.front();
            printf("%d\n", each_team[can_team].front());
            each_team[can_team].pop();
            if(each_team[can_team].empty()){
                team.pop();
            }
        } else {
            int id;
            scanf("%d",&id);
            int id_team = on_team[id];
            if(each_team[id_team].empty()){
                team.push(id_team);
            }
            each_team[id_team].push(id);
        }
    }
    return 0;
}