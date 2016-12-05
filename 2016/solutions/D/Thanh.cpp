// Thanh's solution + test generator.
// Suffix automaton

#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define pb push_back
#define sqr(x) (x)*(x)
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))
#define oo 1000000007

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;


int T,go[55][26],len;
ll n,M;
char s[55];

ll mul(ll a, ll b){
    if(a==0 || b==0) return 0;
    if(a < 1000111000111000111/b) return a*b%M;
    if(a>b) swap(a,b);
    ll t=mul(a/2,b);
    t=(t*2 + b*(a&1))%M;
    return t;
}


struct Matrix{
    ll arr[51][51];
    int m,n;
    Matrix(){}
    Matrix(int _m, int _n){
        m = _m; n = _n;
        for(int i=0; i<=m; ++i) for(int j=0; j<=n; ++j) arr[i][j]=0;
    }

    Matrix operator * (Matrix &other){
        int x = m, y = other.n;
        Matrix res(x,y);
        for(int i=0; i<=x; ++i) for(int j=0; j<=y; ++j){
            for(int k=0; k<=n; ++k)
                res.arr[i][j] = (res.arr[i][j] + mul(arr[i][k], other.arr[k][j]))%M;
        }
        return res;
    }
};

Matrix myPow(Matrix base, ll n){
    if(n==1) return base;
    Matrix t = myPow(base, n/2);
    t = t*t;
    if(n&1) return t*base;
    return t;
}

void solve(){
    scanf("%d",&T);
    int nTest=0;
    while(T--){
        cerr<<"Processing: "<<++nTest<<"... ";
        scanf("%lld%lld",&n,&M);
        scanf("%s",s+1); len=strlen(s+1);
        reset(go, 0);
        for(int i=1; i<=len; ++i){
            int prefix = go[i-1][s[i]-'a'];
            go[i-1][s[i]-'a']=i;
            for(int c=0; c<26; ++c) go[i][c]=go[prefix][c];
        }

        for(int c=0; c<26; ++c) go[len][c]=len;
        if(n<len) puts("0");
        else{
            Matrix base(len, len);
            for(int i=0; i<=len; ++i) for(int c=0; c<26; ++c){
                int j=go[i][c];
                ++base.arr[j][i];
            }
            Matrix res = myPow(base, n);
            printf("%lld\n", res.arr[len][0]);
        }
        cerr<<" => DONE"<<endl;
    }
}

// ======================================================

//Random function
double randf() {
    double base = 0.1;
    double res = 0;
    for (int i = 0; i < 15; i++) {
        res += base * (rand() % 10);
        base /= 10;
    }
    return res;
}

ll randi(ll n) {
    return (ll)floor(randf() * n);
}


void mktest(){
    srand(time(NULL));
    int T=20;
    ll n, M,range=26;
    cout<<T<<endl;
    for(int tt=1; tt<=T; ++tt){
        if(tt==1){
            n = 10; M = 1000; len=5;
        } else if(tt<=5){
            n = randi(1000); M = randi(10000000); len=randi(10)+1;
        } else if(tt<=10){
            n = randi(1000000000000ll); M = randi(1000000000000ll); len = randi(20)+1;
        } else if(tt<=15){
            n = randi(1000000000000ll); M = randi(1000000000000ll); len = randi(10)+20;
        } else {
            n = randi(1000000000000ll); M = randi(1000000000000ll); len = randi(10)+41;
            if(tt==19 || tt==20){
                n = M = 1000000000000ll;
                len = 50;
            }
        }
        string s="";

        if(tt==13 || tt==16 || tt==9) M = 1234567*(randi(10)+1);

        if(tt==17 || tt==11 || tt == 8 || tt==3) range=3;
        else range=26;

        for(int i=0; i<len; ++i){
            s+=char(randi(range)+'a');
        }
        if(tt==15 || tt==10 || tt==5){
            s="";
            for(int i=0; i<len; ++i) s+='a';
        }
        if(tt==20){
            len=50;
            s="acmvietnamacmvietnamacmvietnamacmvietnamacmvietnam";
        }

        cout<<n<<' '<<M<<endl;
        cout<<s<<endl;
    }
}

int main(){
//    mktest();
    solve();
}


