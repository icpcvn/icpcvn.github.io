// Author: hieult
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

#define maxn 100005

template<int MAXP> struct BitSieve {
	#define isOn(x) ( p[x >> 6] & ( 1 << ( (x & 63) >> 1) ) )
	#define turnOn(x) ( p[x >> 6] |= ( 1 << ( (x & 63) >> 1 ) ) )
	int p[(MAXP >> 6) + 1];
	BitSieve() {
		for (int i = 3; i * i <= MAXP; i += 2) {
			if (!isOn(i)) {
				int ii = i * i, i2 = i << 1;
				for (int j = ii; j <= MAXP; j += i2) turnOn(j);
			}
		}
	}
	bool operator [] (const int x) {
		return x > 1 && (x == 2 || ( (x & 1) && !isOn(x) ) );
	}
};

int test;
vector<ll> prime;
BitSieve<maxn * 10> BS;
vector<ll> V[maxn];
int mask = 64;

void add(ll &x, ll y){
	x += y;
	if(x >= mod) x -= mod;
}

void sol(){
	ll A, B, n;
	cin >> A >> B;
	n = B - A;
	ll f[mask][2], g[mask][2];
	For(i, 0, n) V[i].clear();
	for(int i = 0; prime[i] * prime[i] <= B; i++){
		ll u = ((A - 1) / prime[i] + 1) * prime[i];
		for(ll j = u; j <= B; j += prime[i]){
			V[j - A].pb(prime[i]);
		}
	}
	ms(f, 0); ms(g, 0);
	f[0][0] = 1;

//	cout << n << endl;

	For(t, 0, n){
		Rep(i, mask) Rep(j, 2){
			g[i][j] = f[i][j];
			f[i][j] = 0;
		}

		ll x = A + t;
		int num = 0;
		Rep(j, sz(V[t])){
			ll u = V[t][j];
			while(x % u == 0){
				x /= u;
				num++;
			}
		}
		if(x > 1) num++;
//		cout << t << " " << num << endl;
		Rep(i, mask) Rep(j, 2){
			add(f[i][j], g[i][j]);
			if(num != 1) add(f[i ^ num][1], g[i][j]);
			else add(f[i ^ num][j], g[i][j]);
		}
	}

	ll res = f[1][0];
	add(res, f[0][1]);
	cout << res << endl;
}

void solve(){
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> test;
	For(i, 2, maxn * 10 - 1) if(BS[i]) prime.pb(i);

	Rep(itest, test){
		sol();
	}
}

int main()
{
	solve();
//	trau();
    return 0;
}

