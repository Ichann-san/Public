#include <bits/stdc++.h>
using namespace std;

int main(){
    string temp;
    int n, prio;
    priority_queue<pair<int, string>> antri;
    
    cin >> n;
    while(n--){
        cin >> prio;
        getline(cin, temp);
        if(temp.find("seru-seruan") != string::npos) continue;
        else {
            antri.push(make_pair(prio, temp));
        }
    }
    
    while(!antri.empty()){
        cout << antri.top().second << "\n";
        antri.pop();
    }
    return 0;
}