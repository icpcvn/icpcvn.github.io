// Author: Lang Trung Hieu

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
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))
/* #define mod 1000000007 */
/* #define mod 1000267129 */
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
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 1005

struct Hungary {
	int nx, ny, cost[maxn][maxn], fx[maxn], fy[maxn], maty[maxn], which[maxn], dist[maxn];
	bool used[maxn];

	void init(int _nx, int _ny) {
		nx = _nx; ny = _ny; ms(fx, 0); ms(fy, 0);
		For(i, 0, nx) For(j, 0, ny) cost[i][j] = 0;
	}

	void add(int x, int y, int c) { cost[x][y] = c; }

	int mincost() {
		For(x, 1, nx) {
			int y0 = 0; maty[0] = x;
			For(y, 0, ny) { dist[y] = -1; used[y] = false; }

			do {
				used[y0] = true;
				int x0 = maty[y0], delta = -1, y1;

				For(y, 1, ny) if (!used[y]) {
					int curdist = cost[x0][y] - fx[x0] - fy[y];
					if (curdist > dist[y]) {
						dist[y] = curdist;
						which[y] = y0;
					}
					if (dist[y] > delta) {
						delta = dist[y];
						y1 = y;
					}
				}

				For(y, 0, ny) if (used[y]) {
					fx[maty[y]] += delta;
					fy[y] -= delta;
				} else dist[y] -= delta;

				y0 = y1;
			} while (maty[y0] != 0);

			do {
				int y1 = which[y0];
				maty[y0] = maty[y1];
				y0 = y1;
			} while (y0);
		}
		int ret = 0;
		For(y, 1, ny) {
			int x = maty[y];
			ret += cost[x][y];
		}
		return ret;
	}
} hungary;

int n, m, k;

int main() {
//  freopen("out.txt", "w", stdout);
  /* freopen("in.txt", "r", stdin); */
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n >> m >> k;
  n = max(n, m);
  hungary.init(n, n);
  Rep(run, k){
    int u, v, c;
    cin >> u >> v >> c;
    hungary.add(u, v, c);
  }
  

  cout << hungary.mincost() << endl;
  vector<II> Vres;
  For(i, 1, n){
    if(hungary.cost[hungary.maty[i]][i]){
      Vres.pb(mp(hungary.maty[i], i));
    }
  }

  sort(all(Vres));
  cout << sz(Vres) << endl;
  Rep(i, sz(Vres)) cout << Vres[i].fi << " " << Vres[i].se << endl;

  /* cerr << clock() << endl; */
  return 0;
}

