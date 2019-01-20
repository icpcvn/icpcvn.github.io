#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define ALL(v) (v).begin(), (v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x > y + eps) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x + eps < y) {
            x = y;
            return true;
        } else return false;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

#define MAX   300300

vector<pair<int, int>> edges;
vector<int> adj[MAX];
vector<int> queryAt[MAX];
int numNode, numEdge;
bool marked[MAX];

void loadGraph(void) {
    scanf("%d", &numNode);
    REP(love, numNode - 1) {
        int u, v; scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        edges.push_back(make_pair(u, v));
    }
    sort(ALL(edges));
    edges.resize(unique(ALL(edges)) - edges.begin());
    FORE(it, edges) {
        adj[it->fi].push_back(it->se);
        adj[it->se].push_back(it->fi);
    }
}

int biggerNode(int u, int v) {
    if (adj[u].size() > adj[v].size()) return u;
    if (adj[v].size() > adj[u].size()) return v;
    return max(u, v);
}

void process(void) {
    FORE(it, edges) {
        int big = biggerNode(it->fi, it->se);
        int small = it->fi ^ it->se ^ big;
        queryAt[big].push_back(small);
    }

    long long res = 0;
    FOR(i, 1, numNode) res += 1LL * adj[i].size() * (adj[i].size() - 1) / 2;

    FOR(i, 1, numNode) if (!queryAt[i].empty()) {
        FORE(jt, adj[i]) marked[*jt] = true;

        FORE(jt, queryAt[i]) {
            int j = *jt;
            FORE(kt, adj[j]) if (marked[*kt]) res--;
        }

        FORE(jt, adj[i]) marked[*jt] = false;
    }

    cout << (res << 1) << endl;
}

int main(void) {
    loadGraph();
    process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/