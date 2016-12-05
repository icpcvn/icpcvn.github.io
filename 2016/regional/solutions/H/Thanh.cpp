// Author: Le Yen Thanh
// Max flow O(N) vertices

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
typedef pair<int,pii> iii;
typedef long long ll;

const int maxn=607;
const int maxm=200007;

struct Edge{
    int x,y,c,f;
    Edge(){}
    Edge(int _x, int _y, int _c){
        x = _x;
        y = _y;
        c = _c;
        f = 0;
    }
} e[maxm];
int n,m,k,ce,p[maxn],from[maxn],to[maxn];
int S,F,N,trace[maxn],head[maxn],jmp[maxm];
vector<int> vals;

void pushEdge(int x, int y, int c){
    e[++ce] = Edge(x,y,c);
    jmp[ce] = head[x]; head[x] = ce;
    e[++ce] = Edge(y,x,0);
    jmp[ce] = head[y]; head[y] = ce;
}

int findPos(int v){
    return lower_bound(vals.begin(), vals.end(), v)-vals.begin();
}

int myq[maxn],first,last;

bool findPath(){
    for(int i=1; i<=N; ++i) trace[i]=0; trace[S]=-1;
    myq[first=last=1]=S;
    while(first<=last){
        int u=myq[first++];
        for(int i=head[u]; i; i=jmp[i])
            if(e[i].c > e[i].f && !trace[e[i].y]){
                trace[e[i].y] = i;
                myq[++last]=e[i].y;
            }
    }
    return trace[F]!=0;
}

int dinic(){
    while(findPath()){
        for(int i=head[F]; i; i=jmp[i]){
            int delta=e[i^1].c - e[i^1].f;
            int u = e[i].y;
            while(delta>0 && u!=S){
                int i=trace[u];
                delta=min(delta,e[i].c - e[i].f);
                u=e[i].x;
            }
            if(delta==0) continue;
            e[i^1].f += delta;
            e[i].f -= delta;
            u = e[i].y;
            while(u!=S){
                int i=trace[u];
                e[i].f += delta;
                e[i^1].f -= delta;
                u=e[i].x;
            }
        }
    }
    int flow = 0;
    for(int i=head[S]; i; i=jmp[i]) flow += e[i].f;
    return flow;
}

int main(){
//    freopen("H_thanh.in","r",stdin);
//    freopen("H_thanh.out","w",stdout);
    int T=1;
    scanf("%d",&T);
    while(T--){
        ce = 1;
        vals.clear();
        reset(head,0);
        scanf("%d%d",&n,&m);
        int sumP = 0;
        for(int i=1; i<=n; ++i){
            scanf("%d%d%d",&p[i],&from[i],&to[i]);
            vals.pb(from[i]);
            vals.pb(to[i]);
            sumP += p[i];
        }
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end())-vals.begin());
        k = sz(vals)-1;
        N = n + k + 2;
        S = N-1; F = N;

        for(int i=1; i<=n; ++i) pushEdge(S, i, p[i]);
        for(int i=1; i<=k; ++i) pushEdge(i + n, F, (vals[i] - vals[i-1]) * m);
        for(int i=1; i<=n; ++i){
            int posFrom = findPos(from[i]);
            int posTo = findPos(to[i]);
            for(int j=posFrom+1; j<=posTo; ++j)
                pushEdge(i, n + j, vals[j]-vals[j-1]);
        }
        int flow = dinic();
        if(flow == sumP){
            puts("YES");
        }else{
            puts("NO");
        }
    }
}
