// Author: Nguyen Diep Xuan Quang
// Code submit trong ky thi.

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point;
#define debug(a) cout << #a << ": " << a << endl
#define fto(i, l, r) for(int i = l; i <= r; ++i)
#define fdto(i, r, l) for(int i = r; i >= l; --i)
#define forit(it, var) for(__typeof(var.begin()) it = var.begin(); it != var.end(); ++it)
#define ff first
#define ss second
#define X real()
#define Y imag()
#define mp make_pair
#define pb push_back
#define ii pair<int, int>
#define ll long long
#define maxN 1000005
#define oo 1000000000000000007LL
#define sz(a) (int)a.size()

struct DSU {
    vector<int> pset;
    DSU(int n) {
        pset.resize(n);
        fto(i, 0, n-1) pset[i] = i;
    }
    int findSet(int i) {
        return (pset[i] == i) ? i : pset[i] = findSet(pset[i]);
    }
    bool unionSet(int u, int v) {
        int p = findSet(u), q = findSet(v);
        if (p == q) return false;
        pset[p] = q;
        return true;
    }
};

vector<int> g[maxN];    
int n, m, dp[maxN];

int toInd(int r, int c) {return r*m+c;}

int Solve(int u) {
    if (dp[u] != -1) return dp[u];
    int res = 1;
    forit(it, g[u]) {
        int v = *it;
        res = max(res, Solve(v)+1);
    }
    return dp[u] = res;
}

int main() {
    scanf("%d%d", &n, &m);

    vector<vector<int> > a(n, vector<int>(m, 0));   
    fto(i, 0, n-1) fto(j, 0, m-1) scanf("%d", &a[i][j]);
    
    DSU s(n*m);
        
    fto(i, 0, n-1) {
        vector<ii> p;
        fto(j, 0, m-1) p.pb(mp(a[i][j], j));
        sort(p.begin(), p.end());
        fto(j, 1, m-1) {
            if (p[j].ff == p[j-1].ff) s.unionSet(toInd(i, p[j].ss), toInd(i, p[j-1].ss));
        }
    }

    fto(j, 0, m-1) {
        vector<ii> p;
        fto(i, 0, n-1) p.pb(mp(a[i][j], i));
        sort(p.begin(), p.end());
        fto(i, 1, n-1) {
            if (p[i].ff == p[i-1].ff) s.unionSet(toInd(p[i].ss, j), toInd(p[i-1].ss, j));
        }
    }
    
    fto(i, 0, n-1) {
        vector<ii> p;
        fto(j, 0, m-1) p.pb(mp(a[i][j], j));
        sort(p.begin(), p.end());
        fto(j, 1, m-1) {
            if (p[j].ff != p[j-1].ff) 
                g[s.findSet(toInd(i, p[j-1].ss))].pb(s.findSet(toInd(i, p[j].ss)));
        }
    }

    fto(j, 0, m-1) {
        vector<ii> p;
        fto(i, 0, n-1) p.pb(mp(a[i][j], i));
        sort(p.begin(), p.end());
        fto(i, 1, n-1) {
            if (p[i].ff != p[i-1].ff) 
                g[s.findSet(toInd(p[i-1].ss, j))].pb(s.findSet(toInd(p[i].ss, j)));
        }
    }
    
    /*
    fto(i, 0, n*m-1) {
        debug(i);
        forit(it, g[i]) printf("%d ", *it);
        puts("");
    }
    */
    
    //return 0;
    fto(i, 0, n*m-1) dp[i] = -1;
    
    int ans = 0;
    fto(i, 0, n*m-1) {
        ans = max(ans, Solve(i));
    }
    printf("%d", ans);
    
    

    return 0; 
}
