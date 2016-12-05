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

#define maxn 10005
//#define maxv 100005

int n;
ld W, L, D, V;
ld w[maxn], r[maxn];

ld calcu(ld R, ld X){
	if(X >= R + R) return 4 * (ld)(1.0) / 3 * PI * R * R * R;
	else if(X <= R){
		return PI * X * X * (R - X / 3);
	}else{
		return 4 * (ld)(1.0) / 3 * PI * R * R * R - calcu(R, R + R - X);
	}
}

ld cal(ld x){
	ld res = x * W * L;
	Rep(i, n){
		ld v = calcu(r[i], x);
		ld vball = 4 * (ld)(1.0) / 3 * PI * r[i] * r[i] * r[i];
		if(v >= vball * w[i]){
			res -= vball * w[i];
		} else res -= v;
	}
	return res;
}

void solve(){
	cin >> n;
	cin >> W >> L >> D >> V;
	Rep(i, n) cin >> r[i] >> w[i];
	ld l = 0, r = D, mid;
	Rep(run, 100){
		mid = (l + r) / 2;
		if(cal(mid) <= V) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(3) << l << endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int test;
	cin >> test;
	Rep(itest, test){
		solve();
	}

    return 0;
}

