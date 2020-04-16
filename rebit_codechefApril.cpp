#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int modu = 998244353;
vector<ll> res(4,1);

int mult(int a,int b){
    if(a == 0 || b == 0)
        return 0;
    else if(a == 1 && b == 1)
        return 1;
    else if(a == 1 && b == 2)
        return 2;
    else if(a == 1 && b == 3)
        return 3;
    else if(a == 2 && b == 1)
        return 2;
    else if(a == 2 && b == 2)
        return 2;
    else if(a == 2 && b == 3)
        return 0;
    else if(a == 3 && b == 1)
        return 3;
    else if(a == 3 && b == 3)
        return 3;
    else if(a == 3 && b == 2)
        return 0;
    else
        return 0;

}
int add(int a,int b){
    if(a == 0 && b == 0)
        return 0;
    else if(a == 0)
        return b;
    else if(a == 1 || b == 1)
        return 1;
    else if(a == 2 && b == 0)
        return 2;
    else if(a == 2 && b == 2)
        return 2;
    else if(a == 3 && b == 0)
        return 3;
    else if(a == 3 && b == 3)
        return 3;
    else
        return 1;

}
int exor(int a,int b){
    if(a == 0 && b == 1)
        return 1;
    else if(a == 1 && b == 0)
        return 1;
    else if(a == 2 && b == 0)
        return 2;
    else if(a == 1 && b == 2)
        return 3;
    else if(a == 1 && b == 3)
        return 2;
    else if(a == 2 && b == 1)
        return 3;
    else if(a == 2 && b == 3)
        return 1;
    else if(a == 3 && b == 0)
        return 3;
    else if(a == 3 && b == 1)
        return 2;
    else if(a == 3 && b == 2)
        return 1;
    else if(a == 0)
        return b;
    else
        return 0;


}
vector<ll> andOp(vector<ll>& h1,vector<ll> &h2){
    vector<ll> resu(4,0);
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
           resu[mult(i,j)] = (resu[mult(i,j)]+(h1[i]*h2[j])%modu)%modu;
            //resu[mult(i,j)] += h1[i]*h2[j];
        }
    }
    return resu;
}
vector<ll> orOp(vector<ll>& h1,vector<ll> &h2){
    vector<ll> resu(4,0);
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            resu[add(i,j)] = (resu[add(i,j)]+(h1[i]*h2[j])%modu)%modu;
            //resu[add(i,j)] += h1[i]*h2[j];
        }
    }
    return resu;
}
vector<ll> exorOp(vector<ll>& h1,vector<ll> &h2){
    vector<ll> resu(4,0);
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
           resu[exor(i,j)] = (resu[exor(i,j)]+(h1[i]*h2[j])%modu)%modu;
            //resu[exor(i,j)] += h1[i]*h2[j];
        }
    }
    return resu;
}
void eval(string str){
    stack<char> s1;
    stack<vector<ll>> s2;
    for(char c : str){
        if(c != ')'){
            if(c == '#'){
                s2.push({1,1,1,1});
            }else{
                s1.push(c);
            }

        }else{
            char op = s1.top();
            s1.pop();
            s1.pop();
            vector<ll> a = s2.top();
            s2.pop();
            vector<ll> b = s2.top();
            s2.pop();
            if(op == '&')
                res = andOp(a,b);
            if(op == '|')
                res = orOp(a,b);
            if(op == '^')
                res = exorOp(a, b);
            s2.push(res);
        }

    }
}

ll eeu(ll a,int b){
    ll s = 0;
    ll t = 1;
    ll r = b;
    ll olds = 1;
    ll oldt = 0;
    ll oldr = a;
    while(r!=0){

        ll q = oldr/r;
        ll temp = r;
        r = oldr - q*r;
        oldr = temp;
        temp = s;
        s = olds-q*s;
        olds = temp;
        temp = t;
        t = oldt-q*t;
        oldt= temp;

    }

    if(olds<0)
        return olds+b;
    else
        return olds;

}
ll power(ll a , ll n)
{
    ll res = 1;
    while(n)
    {
        if(n & 1)
            res = (res * a) % modu;
        n >>= 1;
        a = (a * a) % modu;
    }
    return res;
}
int main(){

    int t;
    cin >> t;
    while(t--){
        res = {1,1,1,1};
        string s;
        cin >> s;
        if(s.size() == 1){
            cout << (res[0]*eeu(4,modu))%modu << " " << (res[1]*eeu(4,modu))%modu << " " <<(res[2]*eeu(4,modu))%modu << " " <<  (res[3]*eeu(4,modu))%modu << endl;

        }else{
            eval(s);
            int number = 0;
            for(char c : s){
                if(c == '#')
                    number++;
            }
            long long r = 0;
            for(int i = 0;i<4;i++){
                r = (r+res[i])%modu;

            }

           ll d = eeu(r , modu);
           cout<<(res[0] * d)%modu<<" ";
           cout<<(res[1] * d)%modu<<" ";
           cout<<(res[2] * d)%modu<<" ";
           cout<<(res[3] * d)%modu<<endl;
        }
    }

}
