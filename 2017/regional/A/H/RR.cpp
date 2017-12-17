// Author: RR

#include <sstream>
#include <fstream>
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 2000111;
vector<int> ke[MN];
int row[MN], col[MN];
bool visited[MN];
pair<int,int> pos[MN];

void addEdge(int u, int v) {
    ke[u].push_back(v);
    ke[v].push_back(u);
}

void go(int u, vector< pair<int,int> > &all) {
    queue<int> qu;
    qu.push(u);
    visited[u] = true;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        all.push_back(pos[u]);
        for (int v : ke[u]) if (!visited[v]) {
            visited[v] = true;
            qu.push(v);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int m, n; cin >> m >> n;
    vector< vector<int> > a(m + 2, vector<int> (n + 2, 0));
    vector< vector<int> > id(m + 2, vector<int> (n + 2, 0));

    int cur = 0;
    FOR(i,1,m) FOR(j,1,n) {
        cin >> a[i][j];

        ++cur;
        id[i][j] = cur;
        pos[cur] = make_pair(i, j);
    }

    FOR(i,1,m) {
        vector< pair<int,int> > all;
        FOR(j,1,n) all.emplace_back(a[i][j], id[i][j]);
        sort(ALL(all));

        FOR(t,1,SZ(all)-1) if (all[t].first == all[t-1].first) {
            addEdge(all[t-1].second, all[t].second);
        }
    }

    FOR(j,1,n) {
        vector< pair<int,int> > all;
        FOR(i,1,m) all.emplace_back(a[i][j], id[i][j]);
        sort(ALL(all));

        FOR(t,1,SZ(all)-1) if (all[t].first == all[t-1].first) {
            addEdge(all[t-1].second, all[t].second);
        }
    }

    vector< pair<int, int> > all;
    FOR(i,1,m) FOR(j,1,n) all.emplace_back(a[i][j], id[i][j]);
    sort(ALL(all));

    int res = 0;
    for (auto it : all) {
        int id = it.second;
        if (visited[id]) continue;

        vector< pair<int,int> > all;
        go(id, all);

        int cur = 0;
        for (auto p : all) {
            cur = max(cur, row[p.first]);
            cur = max(cur, col[p.second]);
        }
        ++cur;
        for (auto p : all) {
            row[p.first] = cur;
            col[p.second] = cur;
        }
        res = max(res, cur);
    }
    cout << res << endl;
    return 0;
}

