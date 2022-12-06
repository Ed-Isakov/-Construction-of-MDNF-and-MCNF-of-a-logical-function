#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
bool cint(int &a){ // функция считывания количества переменных функции
    a=0;
    string s;
    cin >> s;
    try {
        a=stoi(s);
        string t=to_string(a);
        if (t!=s){
            getline(cin, s);
            return 1;
        } else {
            getline(cin, s);
            return 0;
        }
    } catch(invalid_argument){
        getline(cin, s);
        return 1;
    }
}
bool cper(vector <string> &a){ // функция считывания названий переменных
    set <string> m;
    bool f=0;
    for (int i=0; i<a.size(); i++){
        cin >> a[i];
        for (int j=0; j<a[i].length(); j++){
            if (a[i][j]<48 or (a[i][j]>57 and a[i][j]<65) or (a[i][j]>90 and a[i][j]<97) or a[i][j]>122){
                f=1;
            }
        }
        m.insert(a[i]);
    }
    if (m.size()!=a.size() or f){
        string g;
        getline(cin, g);
        return 1;
    }
    string g;
    getline(cin, g);
    return 0;
}
bool cf(string &s){ // функция считывания формата представления таблицы истиности
    cin >> s;
    string g;
    if (s=="0" or s=="1"){
        getline(cin, g);
        return 0;
    }
    getline(cin, g);
    return 1;
}
void ct(vector <int> &t, string f){ // функция считывания таблицы истиности
    if (f=="0"){
        string s;
        getline(cin, s);
        bool f=0;
        while (s.length()!=(t.size()/4) or f){
            cout << "Некорректный ввод. Повторите ввод\n";
            getline(cin, s);
            //cout << s;
            f=0;
            for (int i=0; i<s.length(); i++){
                if (s[i]<48 or s[i]<65 and s[i]>57 or s[i]>70){
                    f=1;
                }
            }
        }
        for (int i=0; i<t.size(); i+=4){
            char c=s[i/4]-48;
            if (c>9){
                c-=7;
            }
            //cout << (int)c << " ";
            t[i]=c/8;
            t[i+1]=c/4%2;
            t[i+2]=c/2%2;
            t[i+3]=c%2;
            //cout << t[i] << t[i+1] << t[i+2] << t[i+3];
        }
        //cout << '\n';
    } else {
        bool f=0;
        string s;
        getline(cin, s);
        while (s.length()!=t.size() or f){
            cout << "Некорректный ввод. Повторите ввод\n";
            getline(cin, s);
            f=0;
            for (int i=0; i<s.length(); i++){
                if (s[i]!='0' and s[i]!='1'){
                    f=1;
                }
            }
        }
        for (int i=0; i<t.size(); i++){
            char c;
            c=s[i];
            t[i]=c-48;
        }
    }
}
vector <string> split(string s, char sep){ // функция разбиения строки по символу-сепаратору
    vector <string> res;
    int l=0;
    for (int i=0; i<s.length(); i++){
        if (s[i]==sep){
            res.push_back(s.substr(l, i-l));
            l=i+1;
        }
    }
    res.push_back(s.substr(l, s.length()-l));
    return res;
}
string concat(vector <string> a, vector <string> b, string sep){ //функция, которая сокращает логическое выражение, если это возможно
    if (a.size()!=b.size()){
        return "-";
    } else if (a.size()==1){
        if ((a[0].substr(1, a[0].length()-1)==b[0] and a[0][0]=='!') or (b[0].substr(1, b[0].length()-1)==a[0] and b[0][0]=='!')){
            return "+";
        }else {
            return "-";
        }
    }
    int k=0;
    bool f=0;
    string ans;
    for (int i=0; i<a.size(); i++){
        if (a[i]==b[i]){
            k++;
            ans=ans+sep+a[i];
            continue;
        }
        string x=a[i];
        string y=b[i];
        if ((x.substr(1, x.length()-1)==y and x[0]=='!') or (y.substr(1, y.length()-1)==x and y[0]=='!')){
            f=1;
        }
    }
    if (k==a.size()-1 and f){
        return ans.substr(1, ans.length()-1);
    } else {
        return "-";
    }
}
bool cor(vector <int> t, vector <string> per, vector <string> expr, char sep){ // функция, которая по заданной функции проверяет её соответствие таблице истиности
    int f=0;
    if (sep=='+'){
        f=1;
    }
    vector <int> a(t.size(), f);
    int n=per.size();
    for (auto e:expr){
        vector <string> v=split(e, sep);
        vector <int> ind(1, 0);
        int i=0;
        int j=0;
        while (i<n){
            if (j<v.size() and (per[i]==v[j] or (per[i]==v[j].substr(1, v[j].length()-1) and v[j][0]=='!'))){
                if (v[j][0]!='!' and f==0){
                    for (int k=0; k<ind.size(); k++){
                        ind[k]+=(1<<(n-i-1));
                    }
                }
                if (v[j][0]=='!' and f==1){
                    for (int k=0; k<ind.size(); k++){
                        ind[k]+=(1<<(n-i-1));
                    }
                }
                j++;
            } else{
                int m=ind.size();
                for (int k=0; k<m; k++){
                    ind.push_back(ind[k]+(1<<(n-i-1)));
                    //cout << (1<<(n-i-1)) << " ";
                }
            }
            i++;
        }
        for (auto e:ind){
            //cout << e << " ";
            a[e]=1;
            if (f){
                a[e]=0;
            }
        }
    }
    f=1;
    for (int i=0; i<t.size(); i++){
        if (t[i]!=a[i]){
            f=0;
            break;
        }
    }
    if (f){
        return true;
    } else {
        return false;
    }
}
vector <vector<int> > comb(int n, int k, int m){ // функция которая генерирует все сочетания длины k из массива (0, 1....n-2, n-1)
    if (k==1){
        vector <vector <int> > ans;
        for (int i=m; i<n; i++){
            vector <int> res;
            res.push_back(i);
            ans.push_back(res);
        }
        return ans;
    }
    vector <vector<int> > ans;
    for (int i=m; i<n-k+1; i++){
        vector <vector<int> > res=comb(n, k-1, i+1);
        for (auto e:res){
            vector <int> ind;
            ind.push_back(i);
            for (auto w:e){
                ind.push_back(w);
            }
            ans.push_back(ind);
        }
    }
    return ans;
}
string mdnf(vector <int> t, vector <string> per){ // функция построения МДНФ
    vector <string> sdnf;
    set <string> m;
    set <string> al;
    for (int i=0; i<t.size(); i++){
        if (t[i]==1){
            int a=i;
            string expr;
            //cout << 0;
            for (int j=per.size()-1; j>=0; j--){
                if (a%2==0){
                    expr="!"+per[j]+"&"+expr;
                }else{
                    expr=per[j]+"&"+expr;
                }
                a=a/2;
            }
            //cout << 0;
            expr=expr.substr(0, expr.length()-1);
            sdnf.push_back(expr);
            m.insert(expr);
            al.insert(expr);
            //cout << expr << " ";
        }
    }
    if (sdnf.size()==0){
        return "0";
    }
    if (sdnf.size()==t.size()){
        return "1";
    }
    bool f=1;
    for (;;){
        if (f==0){
            break;
        }
        f=0;
        for (int x=0; x<sdnf.size()-1; x++){
            for (int y=x+1; y<sdnf.size(); y++){
                string a=sdnf[x];
                string b=sdnf[y];
                vector <string> l=split(a, '&');
                vector <string> r=split(b, '&');
                string res=concat(l, r, "&");
                if (res=="-"){
                    continue;
                } else {
                    m.erase(a);
                    m.erase(b);
                    if (al.find(res)==al.end()){
                        sdnf.push_back(res);
                        m.insert(res);
                        al.insert(res);
                        f=1;
                    }
                }
            }
        }
    }
    sdnf.clear();
    for (auto e:m){
        sdnf.push_back(e);
    }
    int n=sdnf.size();
    int b_r=1000;
    vector <string> b_e;
    for (int i=1; i<=n; i++){
        vector <vector<int> > indx=comb(n, i, 0);
        for(auto e:indx){
            vector <string> expr;
            int r=0;
            for (auto w:e){
                expr.push_back(sdnf[w]);
                vector <string> q=split(sdnf[w], '&');
                r+=q.size();
            }
            if (cor(t, per, expr, '&')){
                if (r<b_r){
                    b_r=r;
                    b_e=expr;
                }
            }
        }
    }
    string ans;
    ans+=b_e[0];
    for (int i=1; i<b_e.size(); i++){
        ans+=" + ";
        ans+=b_e[i];
    }
    return ans;
}
string mknf(vector <int> t, vector <string> per){ // функция построения МКНФ
    vector <string> sknf;
    set <string> m;
    set <string> al;
    for (int i=0; i<t.size(); i++){
        if (t[i]==0){
            int a=i;
            string expr;
            //cout << 0;
            for (int j=per.size()-1; j>=0; j--){
                if (a%2==1){
                    expr="!"+per[j]+"+"+expr;
                }else{
                    expr=per[j]+"+"+expr;
                }
                a=a/2;
            }
            //cout << 0;
            expr=expr.substr(0, expr.length()-1);
            sknf.push_back(expr);
            m.insert(expr);
            al.insert(expr);
            //cout << expr << " ";
        }
    }
    if (sknf.size()==0){
        return "1";
    }
    if (sknf.size()==t.size()){
        return "0";
    }
    bool f=1;
    for (;;){
        if (f==0){
            break;
        }
        f=0;
        for (int x=0; x<sknf.size()-1; x++){
            for (int y=x+1; y<sknf.size(); y++){
                string a=sknf[x];
                string b=sknf[y];
                vector <string> l=split(a, '+');
                vector <string> r=split(b, '+');
                string res=concat(l, r, "+");
                if (res=="-"){
                    continue;
                } else {
                    m.erase(a);
                    m.erase(b);
                    if (al.find(res)==al.end()){
                        sknf.push_back(res);
                        m.insert(res);
                        al.insert(res);
                        f=1;
                    }
                }
            }
        }
    }
    sknf.clear();
    for (auto e:m){
        sknf.push_back(e);
    }
    int n=sknf.size();
    int b_r=1000;
    vector <string> b_e;
    for (int i=1; i<=n; i++){
        vector <vector<int> > indx=comb(n, i, 0);
        for(auto e:indx){
            vector <string> expr;
            int r=0;
            for (auto w:e){
                expr.push_back(sknf[w]);
                vector <string> q=split(sknf[w], '+');
                r+=q.size();
            }
            if (cor(t, per, expr, '+')){
                if (r<b_r){
                    b_r=r;
                    b_e=expr;
                }
            }
        }
    }
    string ans;
    ans+="("+b_e[0]+")";
    for (int i=1; i<b_e.size(); i++){
        ans+=" & ";
        ans+="("+b_e[i]+")";
    }
    return ans;
}
int main(){
    system("chcp 1251");
    int n;
    cout << "Введите число переменных от 2 до 6\n";
    while (cint(n) or (n<2 or n>6)){
        cout << "Некорректный ввод. Повторите ввод\n";
    }
    vector <string> per(n);
    cout << "Введите названия переменных, разделённые пробелом, используя латинские буквы или цифры\n";
    while (cper(per)){
        cout << "Некорректный ввод, названия переменных должны быть различны. Повторите ввод с начала\n";
    }
    string f;
    cout << "Выберите формат ввода таблицы истиности: Шестнадцатеричное число-0; Двоичное число-1\n";
    while (cf(f)){
        cout << "Некорректный ввод. Повторите ввод\n";
    }
    cout << "Введите таблицу истиности\n";
    vector <int> t(1<<n, 0);
    ct(t, f);
    //for (auto e:t){
    //    cout << e << " ";
    //}
    //mdnf(t, per);
    string ans0=mdnf(t, per);
    cout << "МДНФ функции: "<<ans0 << '\n';
    //mknf(t, per);
    string ans1=mknf(t, per);
    cout << "МКНФ функции: " << ans1 << '\n';
}
