// Author: Pham Van Hanh

#include<bits/stdc++.h>
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
template<class T>
    T Abs(const T &x) {
        return (x<0?-x:x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

#define MAX   100100
const long long INF = (long long)1e18 + 7LL;

int numNode, numEdge, sa, sb;
vector<int> adj[MAX];
int value[MAX];
long long best[MAX];

char input[22];

void loadGraph(void) {
    scanf("%d%d", &numNode, &numEdge);
    scanf("%d", &sa);
    scanf("%d%d", &sa, &sb);

    REP(love, numEdge) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    FOR(i, 1, numNode) {
        scanf("%s", input);
        int x; scanf("%d", &x);
        if (input[0] == 'P') {
            scanf("%d", &x);
            value[i] = 0;
        } else value[i] = input[0] == 'S' ? x : -x;
    }
}

long long calcDist(int u) {
    if (adj[u].empty()) return 0;
    if (best[u] > -INF) return best[u];
    FORE(it, adj[u]) maximize(best[u], value[*it] + calcDist(*it));
    return best[u];
}

void process(void) {
    memset(best, -0x3f, sizeof best);
    cout << calcDist(sa) << " " << calcDist(sb) << endl;
}

int main(void) {
    loadGraph();
    process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/

