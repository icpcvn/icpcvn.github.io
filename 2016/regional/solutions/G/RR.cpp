// Author: RR
// O(M*logM)

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
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 10111;
int lab[MN];
struct DSU {
    void init(int n) {
        REP(i,n+2) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

struct Edge {
    int u, v, c;
} edges[1001111];

bool operator < (const Edge& a, const Edge& b) {
    return a.c < b.c;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        int n, m, l, s;
        GI(n); GI(m); GI(l); GI(s);
        FOR(i,1,s) {
            int x; GI(x);
            edges[m+i].u = x;
            edges[m+i].v = n+1;
            edges[m+i].c = 0;
        }
        FOR(i,1,m) {
            GI(edges[i].u);
            GI(edges[i].v);
            GI(edges[i].c);
        }
        m += s;
        sort(edges+1, edges+m+1);

        DSU dsu; dsu.init(n);
        int res = 0;
        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            dsu.merge(u, v);
            res += edges[i].c;
        }
        FOR(i,1,n+1) assert(dsu.getRoot(i) == dsu.getRoot(1));
        printf("%lld\n", res + (n - s) * l);
    }
}
