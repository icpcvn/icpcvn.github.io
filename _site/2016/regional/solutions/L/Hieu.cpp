// Author: hieult

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

#define maxn 22
#define maxm 10005

int test;
ll f[1 << 20], F[22], a[22][10005];
int n, m, q;

void sol(){
	ms(f, 0);
	cin >> n >> m >> q;
	Rep(i, n) Rep(j, m) cin >> a[i][j];
	ms(f, 0); ms(F, 0);
	ll RR = 0;

	Rep(j, m){
		vector<II> V;
		Rep(i, n) V.pb(mp(a[i][j], i));
		sort(all(V));
		ll Max = V[n - 1].fi;
		RR += Max;
		int mask = 0;
		for(int i = n - 1; i > 0; i--){
			mask = onbit(mask, V[i].se);
			f[mask] += V[i].fi - V[i - 1].fi;
		}
	}

	Rep(i, n) Rep(mask, 1 << n) if(getbit(mask, i)){
		f[mask] += f[offbit(mask, i)];
	}

	Rep(mask, 1 << n){
		F[n - cntbit(mask)] = max(F[n - cntbit(mask)], f[mask]);
	}

	Rep(iq, q){
		int u;
		cin >> u;
		cout << RR - F[u] << "\n";
	}
}

void solve(){
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> test;
    For(itest, 1, test) sol();
}

void traubo(){
	ms(F, 0x3f);
	cin >> n >> m >> q;
	Rep(i, n) Rep(j, m) cin >> a[i][j];
	For(mask, 1, (1 << n) - 1){
		ll ret = 0;
		vector<int> V;
		Rep(i, n) if(getbit(mask, i)) V.pb(i);
		Rep(j, m){
			ll Max = 0;
			Rep(i, sz(V)){
				Max = max(a[V[i]][j], Max);
			}
			ret += Max;
		}
		F[cntbit(mask)] = min(F[cntbit(mask)], ret);
	}
	Rep(iq, q){
		int u;
		cin >> u;
		cout << F[u] << "\n";
	}
}

void trau(){
//	freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> test;
    cerr << "test = " << test << endl;
    For(itest, 1, test) {
        cerr << "itest = " << itest << endl;
        traubo();
    }
}

int main()
{
	solve();
//	trau();
    return 0;
}
