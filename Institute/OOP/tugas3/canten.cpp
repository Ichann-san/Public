#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

int main(){
    int t, n, x, id;
    string input;
    unordered_map<int, int> tim;
    queue<int> mainq;
    scanf("%d", &t);
    vector<pair<queue<int>, bool>> teamq(t);
    for(int i=0; i<t; i++) teamq[i].second = false;
    for(int i=0; i<t; i++){
        scanf("%d", &n);
        for(int j=0; j<n; j++){
            scanf("%d", &id);
            tim[id] = i;
        }
    }
    while(cin >> input){
        if(input == "ENQUEUE"){
            scanf("%d", &x);
            int tim_id = tim[x];
            if(!teamq[tim_id].second){
                mainq.push(tim_id);
                teamq[tim_id].second = true;
            }
            teamq[tim_id].first.push(x);
        } else if(input == "DEQUEUE"){
            if(mainq.empty()) continue;
            int tid = mainq.front();
            x = teamq[tid].first.front();
            teamq[tid].first.pop();
            printf("%d\n", x);
            if(teamq[tid].first.empty()){
                teamq[tid].second = false;
                mainq.pop();
            }
        }
    }
    return 0;
}