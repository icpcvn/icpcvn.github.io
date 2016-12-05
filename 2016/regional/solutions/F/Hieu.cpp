// Author: hieult
// Mincost maxflow

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
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))
#define mod 1000000007
#define sz(a) ((ll)(a).size())

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define eps 1e-9
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxv 5005
#define maxe 20005
#define maxn 22

struct MincostFlow {
    int n, s, t, E, adj[maxe], next[maxe], last[maxv], which[maxv];
    ll totalCost, totalFlow, cap[maxe], flow[maxe], cost[maxe], pot[maxe], dist[maxv];

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        ms(last, -1); E = 0;
    }

    void add(int u, int v, ll ca, ll co) {
        adj[E] = v; cap[E] = ca; flow[E] = 0; cost[E] = +co; next[E] = last[u]; last[u] = E++;
        adj[E] = u; cap[E] =  0; flow[E] = 0; cost[E] = -co; next[E] = last[v]; last[v] = E++;
    }

    void bellman() {
        bool stop = false;
        ms(pot, 0);

        while (!stop) {
            stop = true;
            Rep(u, n) for (int e = last[u]; e != -1; e = next[e]) if (flow[e] < cap[e]) {
                int v = adj[e];
                if (pot[v] > pot[u] + cost[e]) {
                    pot[v] = pot[u] + cost[e];
                    stop = false;
                }
            }
        }
    }

    bool dijkstra() {
        typedef pair<ll, int> node;
        priority_queue<node, vector<node>, greater<node> > que;

        Rep(u, n) dist[u] = linf;
        dist[s] = 0;
        que.push(mp(0, s));

        while (!que.empty()) {
            ll dnow = que.top().fi;
            int u = que.top().se;
            que.pop();

            if (dnow > dist[u]) continue;

            for (int e = last[u]; e != -1; e = next[e]) if (flow[e] < cap[e]) {
                int v = adj[e];
                ll dnext = dnow + cost[e] + pot[u] - pot[v];

                if (dist[v] > dnext) {
                    dist[v] = dnext;
                    which[v] = e;
                    que.push(mp(dnext, v));
                }
            }
        }

        return dist[t] < linf;
    }

    bool maxflow(ll desireFlow = linf) {
        totalCost = totalFlow = 0;
        bellman();

        while (totalFlow < desireFlow) {
            if (!dijkstra()) return false;

            ll delta = desireFlow - totalFlow;
            for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) delta = min(delta, cap[e] - flow[e]);
            for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) {
                flow[e] += delta;
                flow[e ^ 1] -= delta;
            }

            totalFlow += delta;
            totalCost += delta * (dist[t] - pot[s] + pot[t]);

            Rep(u, n) pot[u] += dist[u];
        }

        return true;
    }
} mcf;

int n, m;
string s[maxn];
int a[maxn][maxn], b[maxn][maxn];

int dr[4] = {0, +1, 0, -1};
int dc[4] = {-1, 0, +1, 0};

bool inside(int r, int c){
	return r >= 0 && r < n && c >= 0 && c < m;
}

void solve(int itest){
	cin >> n >> m;
	Rep(i, n) cin >> s[i];
	Rep(i, n) Rep(j, m) cin >> a[i][j];
	Rep(i, n) Rep(j, m) cin >> b[i][j];
	mcf.init(2 + 3 * n * m, 0, 1 + 3 * n * m);

	int num = 0;
	Rep(i, n) Rep(j, m) if(s[i][j] != '#'){
		int id = i * m + j + 1;
		num++;
		if((i + j) & 1){
			mcf.add(0, id, 2, 0);
			mcf.add(id, id + n * m, 1, 0);
			mcf.add(id, id + n * m, 1, a[i][j]);
			mcf.add(id, id + 2 * n * m, 1, 0);
			mcf.add(id, id + 2 * n * m, 1, b[i][j]);
			Rep(t, 4){
				int ii = i + dr[t], jj = j + dc[t];
				if(inside(ii, jj) && s[ii][jj] != '#'){
					int id1 = ii * m + jj + 1;
					if(!(t & 1)){
						mcf.add(id + n * m, id1 + n * m, 1, 0);
					} else mcf.add(id + 2 * n * m, id1 + 2 * n * m, 1, 0);
				}
			}
		} else{
			mcf.add(id, 1 + 3 * n * m, 2, 0);
			mcf.add(id + n * m, id, 1, 0);
			mcf.add(id + n * m, id, 1, a[i][j]);
			mcf.add(id + 2 * n * m, id, 1, 0);
			mcf.add(id + 2 * n * m, id, 1, b[i][j]);
		}
	}
	mcf.maxflow();
//	cout << "Case #" << itest << ": ";
	if(mcf.totalFlow < num){
		cout << "NO" << endl;
	} else cout << "YES " << mcf.totalCost << endl;

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int test;
	cin >> test;
	Rep(itest, test){
		solve(itest + 1);
	}
	cerr << clock() << endl;

    return 0;
}

