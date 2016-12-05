// Author: Le Yen Thanh

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

const int maxn = 10007;
const int maxm = 1000007;

int n,m,T,lab[maxn],l,s;
struct Edge{
    int x,y,w;
    Edge(){}
    Edge(int _x, int _y, int _w){
        x = _x;
        y = _y;
        w = _w;
    }
}e[maxm];

int getRoot(int u){
    if(lab[u]<0) return u;
    return lab[u]=getRoot(lab[u]);
}

void dsu(int r1, int r2){
    if(lab[r1]<lab[r2]) swap(r1,r2);
    lab[r2] += lab[r1];
    lab[r1] = r2;
}

bool cmp(const Edge &a, const Edge &b){
    return a.w < b.w;
}

void solve(){
    reset(lab,-1);
    scanf("%d%d%d%d",&n,&m,&l,&s);
    int prev = 0;
    for(int i=1; i<=s; ++i){
        int v;
        scanf("%d",&v);
        if(prev){
            int r1=getRoot(prev);
            int r2=getRoot(v);
            if(r1!=r2) dsu(r1,r2);
        }
        prev = v;
    }
    for(int i=1; i<=m; ++i) scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
    sort(e+1,e+m+1,cmp);
    ll res = 0;
    for(int i=1; i<=m; ++i){
        int r1=getRoot(e[i].x), r2=getRoot(e[i].y);
        if(r1==r2) continue;
        res += e[i].w;
        dsu(r1, r2);

    }
    for(int i = 1; i <= n; i++)
        assert(getRoot(i) == getRoot(1));
    printf("%lld\n",res + 1ll*l*(n-s));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--) solve();
}
