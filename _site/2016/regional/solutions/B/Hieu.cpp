// Author: hieult
// O(N)

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

#define maxn 200005
//#define maxv 100005

ll n, a[maxn], h[maxn], q, l[maxn], sum[maxn];
ll f[maxn];
vector<ll> V;
int test;

void solve(){
    V.clear();
    scanf("%lld\n", &n);
	For(i, 1, n) scanf("%lld\n", &a[i]);
	sum[0] = 0;
	For(i, 1, n){
        scanf("%lld\n", &h[i]);
		sum[i] = sum[i - 1] + h[i];
	}
	a[0] = -1; h[0] = inf; f[0] = 0;
	For(i, 1, n){
		l[i] = i;
		while(h[l[i] - 1] <= h[i]) l[i] = l[l[i] - 1];
		f[i] = f[l[i] - 1] + (h[i] * (a[i] - a[l[i] - 1])) - (sum[i] - sum[l[i] - 1]);
		V.pb(f[i]);
	}
    scanf("%lld\n", &q);
	Rep(iq, q){
		ll x;
        scanf("%lld\n", &x);
		int res = lower_bound(all(V), x) - V.begin();
        printf("%d\n", res);
	}

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    int test; scanf("%d\n", &test);
	Rep(itest, test){
		solve();
	}

    return 0;
}
