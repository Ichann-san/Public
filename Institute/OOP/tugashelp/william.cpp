#include <cstdio>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Builder{
    string bef,aft;
    bool has_point=false,started=false;
    int digits=0;
    void reset(){bef.clear();aft.clear();has_point=false;started=false;digits=0;}
    void push_dot(){ if(has_point) return; has_point=true; if(digits==0){digits=1; started=true;} }
    void push_digit(char c){ if(digits>=8) return; if(has_point) aft.push_back(c); else bef.push_back(c); digits++; started=true; }
    double value() const{
        long long iv=0; for(char c:bef) iv=iv*10+(c-'0');
        double fv=0.0, base=1.0; for(int i=(int)aft.size()-1;i>=0;--i){ fv+=(aft[i]-'0')base; base=10.0; }
        if(base>1.0) fv/=base; return (double)iv + fv;
    }
};

static inline string ltrim(string s){ size_t p=s.find_first_not_of(" \t\r\n"); return p==string::npos?string():s.substr(p); }
static inline bool is_all_digits(const string& s){ if(s.empty()) return false; for(char c:s) if(!isdigit((unsigned char)c)) return false; return true; }
static inline string pad10(const string& s){ if((int)s.size()>=10) return s; return string(10-(int)s.size(),' ')+s; }
static inline int exp_from_double(double ax){ char buf[64]; snprintf(buf,sizeof(buf),"%.0e",ax); char* p=strchr(buf,'e'); return atoi(p+1); }
static inline int digits_before_dot(const string& s){ int i=0; while(i<(int)s.size() && (s[i]==' '||s[i]=='-')) i++; int cnt=0; for(; i<(int)s.size() && s[i]!='.'; ++i) if(isdigit((unsigned char)s[i])) cnt++; return cnt==0?1:cnt; }
static inline bool is_zero_string(const string& s){ for(char c:s) if(c!='0'&&c!='.'&&c!='-'&&c!=' ') return false; return true; }
static inline void trim_frac_keep_dot(string& s){ size_t p=s.find('.'); if(p==string::npos){ s.push_back('.'); return; } size_t i=s.size(); while(i>p+1 && s[i-1]=='0') --i; s.erase(i); if(s.find('.')==string::npos) s.push_back('.'); if(s.back()!='.' && s.find('.')==string::npos) s.push_back('.'); }
static inline double pre_round(double x, int places){ int guard=places+5; if(guard<0) guard=0; if(guard>18) guard=18; char buf[128]; snprintf(buf,sizeof(buf),"%.*f",guard,x); return strtod(buf,nullptr); }

static inline string fmt_fixed(double x){
    double ax=fabs(x);
    if(ax==0.0) return pad10("0.");
    int e=exp_from_double(ax);
    int db=(e>=0)?(e+1):1;
    if(db>8) return "";
    int frac=8-db;
    double y=pre_round(x,max(0,frac));
    char buf[128]; snprintf(buf,sizeof(buf),"%.*f",max(0,frac),y);
    string s(buf);
    if(s.size()>=2 && s[0]=='-' && is_zero_string(s.substr(1))) s=s.substr(1);
    trim_frac_keep_dot(s);
    if(digits_before_dot(s)>8) return "";
    if(ax>0.0 && is_zero_string(s)) return "";
    return pad10(s);
}

static inline string fmt_sci(double x){
    double ax=fabs(x);
    if(ax==0.0) return pad10("0.");
    char buf[64]; snprintf(buf,sizeof(buf),"%.4e",ax);
    string t(buf); size_t pe=t.find('e'); string mant=t.substr(0,pe); string ex=t.substr(pe+1);
    int sgn=(ex[0]=='-'?-1:1); int val=atoi(ex.c_str()+1);
    size_t dp=mant.find('.'); string ip=mant.substr(0,dp), fp=mant.substr(dp+1);
    while(!fp.empty() && fp.back()=='0') fp.pop_back();
    string m=ip; m.push_back('.'); if(!fp.empty()) m+=fp;
    string ee; if(val<10) ee="0"+to_string(val); else ee=to_string(val/10%10)+to_string(val%10);
    string out; if(x<0) out.push_back('-'); out+=m; out.push_back(sgn<0?'-':' '); out+=ee;
    return pad10(out);
}

static string solve_line(const string& line_in){
    string line=line_in;
    double acc=0.0; char op='+'; bool err=false; Builder b;
    auto sanitize=[&](double &v){ if(fabs(v)<=1e-100) v=0.0; if(fabs(v)>=1e100) err=true; if(v==0.0) v=0.0; };
    auto apply=[&](double a,char o,double v)->double{
        if(o=='+') return a+v;
        if(o=='-') return a-v;
        if(o=='x') return a*v;
        if(o==':'){ if(v==0.0){ err=true; return 0.0;} return a/v; }
        if(o=='=') return v;
        return v;
    };
    auto slash_reset=[&](){ b.reset(); acc=0.0; op='='; };
    auto commit=[&](char newop){
        if(newop=='/'){ slash_reset(); return; }
        if(err){ if(newop=='C'){ err=false; acc=0.0; op='+'; b.reset(); } else op=newop; return; }
        if(newop=='C'){ acc=0.0; op='+'; b.reset(); return; }
        if(b.started){
            double val=b.value();
            double res=apply(acc,op,val);
            sanitize(res);
            acc=res;
            b.reset();
        }else{
            double tmp=acc; sanitize(tmp); acc=tmp;
        }
        op=newop;
    };
    for(size_t i=0;i<line.size();){
        if(line[i]!='['){ ++i; continue; }
        size_t j=line.find(']',i+1); if(j==string::npos) break;
        string tok=line.substr(i+1,j-i-1); i=j+1;
        if(tok.size()==1){
            char c=tok[0];
            if(c>='0'&&c<='9'){ if(!err) b.push_digit(c); }
            else if(c=='.'){ if(!err) b.push_dot(); }
            else if(c=='+'||c=='-'||c=='x'||c==':'||c=='='||c=='C'||c=='/'){ commit(c); }
        }else{
            if(tok=="C") commit('C');
            else if(tok=="=") commit('=');
            else if(tok=="+") commit('+');
            else if(tok=="-") commit('-');
            else if(tok=="x") commit('x');
            else if(tok==":") commit(':');
            else if(tok=="/") commit('/');
            else if(tok=="."){ if(!err) b.push_dot(); }
            else if(tok.size()==1 && tok[0]>='0'&&tok[0]<='9'){ if(!err) b.push_digit(tok[0]); }
        }
    }
    if(err) return pad10("Error.");
    string out=fmt_fixed(acc);
    if(out.empty()) out=fmt_sci(acc);
    return out.empty()?pad10("Error."):out;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string first;
    if(!getline(cin,first)) return 0;
    string ftrim=ltrim(first);
    if(is_all_digits(ftrim)){
        int T=stoi(ftrim);
        for(int i=0;i<T;i++){
            string line; if(!getline(cin,line)) break;
            cout<<solve_line(line)<<endl;
        }
        return 0;
    }else{
        int cnt=0;
        cout<<solve_line(first)<<endl;
        cnt++;
        string line;
        while(cnt<8 && getline(cin,line)){
            cout<<solve_line(line)<<endl;
            cnt++;
        }
        return 0;
    }
}