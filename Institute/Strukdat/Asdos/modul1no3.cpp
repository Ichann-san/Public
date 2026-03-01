#include<bits/stdc++.h>
using namespace std;

string kurang(string s1, string s2);
string tambah(string s1, string s2);
string kali(string s1, string s2);
string bagi(string s1, string s2);
string modulo(string s1, string s2);
string postfix(string s);
string count_ops(string s);

void solve(){
    string s;
    cin >> s;
    string res = count_ops(postfix(s));
    cout << res << endl;
}

int main(){
    int n;
    cin >> n;
    while(n--) solve();
return 0;
}

bool neg_res(string s1, string s2){
    if(s1.length() < s2.length()) return true;
    if(s1.length() > s2.length()) return false;
    for(int i=0; i<s1.length(); i++){
        if(s1[i] < s2[i]) return true;
        else if(s1[i] > s2[i]) return false;
    }
    return false;
}

int pred(char c){
    if(c=='*' || c=='/' || c=='%') return 2;
    else if (c=='+' || c=='-') return 1;
    else return 0;
}

string clear(string s){
    int i=0;
    while(i<s.length() && s[i]=='0') i++;
    if(i == s.length()) return "0";
    else return s.substr(i);
}

string kurang(string s1, string s2){
    if(s1[0]=='-' && s2[0]=='-') return kurang(s2.substr(1), s1.substr(1));
    else if(s1[0]=='-' && s2[0]!='-') return "-"+tambah(s1.substr(1), s2);
    else if(s1[0]!='-' && s2[0]=='-') return tambah(s1, s2.substr(1));
    if(s1==s2) return "0";
    if(neg_res(s1, s2)) return "-"+kurang(s2, s1);

    list<int> list1, list2, res;
    string hasil = "";
    int borrow = 0;
    for(int i=0; i<s1.length(); i++) list1.push_front(s1[i]-48);
    for(int i=0; i<s2.length(); i++) list2.push_front(s2[i]-48);
    auto pointer1 = list1.begin(), pointer2 = list2.begin();

    while(pointer1 != list1.end()){
        int num1=*pointer1, num2=(pointer2 != list2.end()) ? *pointer2 : 0;
        int diff = num1-num2-borrow;
        if(diff<0){
            diff += 10;
            borrow = 1;
        } else borrow = 0;
        res.push_back(diff);
        pointer1++;
        if(pointer2 != list2.end()) pointer2++;
    }
    while(res.size() > 1 && res.back() == 0) res.pop_back();
    res.reverse();
    for(auto i = res.begin(); i != res.end(); i++) hasil += to_string(*i);

    return hasil;
}

string tambah(string s1, string s2){
    if(s1[0]=='-' && s2[0]=='-') return "-"+tambah(s1.substr(1), s2.substr(1));
    else if(s1[0]=='-' && s2[0]!='-') return kurang(s2, s1.substr(1));
    else if(s1[0]!='-' && s2[0]=='-') return kurang(s1, s2.substr(1));

    list<int> list1, list2, res;
    string hasil = "";
    int carry = 0;
    for(int i=0; i<s1.length(); i++) list1.push_front(s1[i]-48);
    for(int i=0; i<s2.length(); i++) list2.push_front(s2[i]-48);
    auto pointer1 = list1.begin(), pointer2 = list2.begin();

    while(pointer1 != list1.end() || pointer2 != list2.end() || carry != 0){
        int sum = carry;
        if(pointer1 != list1.end()){sum += *pointer1; pointer1++;}
        if(pointer2 != list2.end()){sum += *pointer2; pointer2++;}
        res.push_back(sum%10);
        carry = sum/10;
    }
    res.reverse();
    for(auto i = res.begin(); i != res.end(); i++) hasil += to_string(*i);

    return hasil;
}

string kali(string s1, string s2){
    if(s1[0]=='-' && s2[0]=='-') return kali(s1.substr(1), s2.substr(1));
    else if(s1[0]=='-' && s2[0]!='-') return "-"+kali(s1.substr(1), s2);
    else if(s1[0]!='-' && s2[0]=='-') return "-"+kali(s1, s2.substr(1));
    if(s1[0]=='0' && s1.length()==1 || s2[0]=='0' && s2.length()==1 ) return "0";

    list<int> list1, list2, res;
    string hasil = "";
    int carry = 1;
    for(int i=0; i<s1.length(); i++) list1.push_front(s1[i]-48);
    for(int i=0; i<s2.length(); i++) list2.push_front(s2[i]-48);
    for(int i=0; i<s1.length()+s2.length(); i++) res.push_back(0);
    auto pointer1 = list1.begin(), mark_res = res.begin();

    while(pointer1 != list1.end()){
        auto pointer2 = list2.begin(), pointer_res = mark_res;
        int temp, carry = 0;

        while(pointer2 != list2.end()){
            temp = (*pointer1)*(*pointer2)+(*pointer_res)+carry;
            *pointer_res = temp%10;
            carry = temp/10;
            pointer2++;
            pointer_res++;
        }

        while(carry>0){
            temp = (*pointer_res)+carry;
            *pointer_res = temp%10;
            carry = temp/10;
            pointer_res++;
        }

        pointer1++;
        mark_res++;
    }
    while(res.size() > 1 && res.back() == 0) res.pop_back();
    res.reverse();
    for(auto i = res.begin(); i != res.end(); i++) hasil += to_string(*i);

    return hasil;
}

string bagi(string s1, string s2){
    if(s2[0]=='0' && s2.length()==1 ) return "undefined";
    if(s1[0]=='0' && s1.length()==1 || neg_res(s1, s2)) return "0";
    if(s1[0]=='-' && s2[0]=='-') return bagi(s1.substr(1), s2.substr(1));
    else if(s1[0]=='-' && s2[0]!='-') return "-"+bagi(s1.substr(1), s2);
    else if(s1[0]!='-' && s2[0]=='-') return "-"+bagi(s1, s2.substr(1));


    string temp="", res="";
    int count;
    for(int i=0; i<s1.length(); i++){
        temp += s1[i];
        temp = clear(temp);
        count = 0;
        while(temp != "0" && !neg_res(temp, s2)){
            temp = kurang(temp, s2);
            count++;
        }
        res += to_string(count);
    }
    return clear(res);
}

string modulo(string s1, string s2){
    if(s2 == "0") return "undefined";
    if(s1 == "0" || s1 == s2) return "0";
    if(s1[0]=='-' && s2[0]=='-') return "-"+modulo(s1.substr(1), s2.substr(1));
    else if(s1[0]=='-' && s2[0]!='-') return "-"+modulo(s1.substr(1), s2);
    else if(s1[0]!='-' && s2[0]=='-') return modulo(s1, s2.substr(1));
    if(neg_res(s1, s2)) return s1;

    string temp = "", res = "";
    int count = 0;
    for(int i=0; i<s1.length(); i++){
        temp += s1[i];
        temp = clear(temp);
        count = 0;
        while(temp != "0" && !neg_res(temp, s2)){
            temp = kurang(temp, s2);
            count++;
        }
        res += to_string(count);
    }
    return clear(temp);
}

string postfix(string s){
    stack<string> temp;
    string res;
    int start=0;
    for(int i=0; i<s.length(); i++){
        if(!isdigit(s[i])){
            res.append(s.substr(start, i-start)); res.append(1, ' ');
            start = i+1;
            while(!temp.empty() && pred(s[i])<=pred(temp.top()[0])) {res.append(temp.top()); res.append(1, ' '); temp.pop();}
            temp.push(string(1, s[i]));
        }
    }
    if(start<s.length()) {res.append(s.substr(start)); res.append(1, ' ');}
    while(!temp.empty()) {res.append(temp.top()); res.append(1, ' '); temp.pop();}
    return res;
}

string count_ops(string s){
    stack<string> res;
    string temp1, temp2, ops_res, token;
    int start=0;
    
    for(int i=0; i<s.length(); i++){
        if(s[i]==' '){
            token = s.substr(start, i-start);
            start = i+1;
            
            if(token.length() == 1 && pred(token[0]) > 0){
                temp2 = res.top(); res.pop(); 
                temp1 = res.top(); res.pop(); 
                
                switch(token[0]){
                    case '-': ops_res = kurang(temp1, temp2); break;
                    case '+': ops_res = tambah(temp1, temp2); break;
                    case '*': ops_res = kali(temp1, temp2); break;
                    case '/': ops_res = bagi(temp1, temp2); break;
                    case '%': ops_res = modulo(temp1, temp2); break;
                }
                res.push(ops_res);
            } 
            else res.push(token);
        }
    }
    string hasil = res.top();
    res.pop();
    return hasil;
}