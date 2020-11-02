// Author: Lang Trung Hieu

#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))
#define mod 1000000007
//#define mod 100000000
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

#define maxn 400005

ll calsum(ll x){
	ll res = 0;
	while(x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

ll add(ll x, ll y){
	ll res = x + y;
	if(res >= mod) res -= mod;
	return res;
}

ll sum[1005];
ll f[205][20][205];
ll T[205][20][205];
ll nex[205][20][205];
ll mu10[20];
ll test, n;

ll cal(ll x){
	x--;
	int run = 1, sum = 0;
	ll res = 0, RR = 0;
	for(int i = 16; i >= 0; i--){
		int id = 0;
		while(f[sum + id][i][run] <= x){
			RR = add(RR, (T[sum + id][i][run] + (f[sum + id][i][run] % mod * id % mod * mu10[i + 3] % mod)) % mod);
			x -= f[sum + id][i][run];
			run = nex[sum + id][i][run];
			id++;
		}
		res = res * 10 + id;
		RR = add(RR, (x % mod * id % mod * mu10[i + 3] % mod));
		sum = calsum(res);
	}
//	cout << RR << " " << res << " " << x << " " << run << endl;
	Rep(i, x){
		RR = add(RR, run);
		run += calsum(run) + sum;
	}
//	cout << RR << endl;
	res = res * 1000 + run;
	RR = add(RR, res % mod);
	return RR;
}

void init(){
	For(i, 0, 1000) sum[i] = calsum(i);
	mu10[0] = 1;
	For(i, 1, 18) mu10[i] = mu10[i - 1] * 10 % mod;
	ms(f, 0);
	for(int i = 0; i <= 200; i++) for(int j = 0; j <= 200; j++) if(i + j){
		int run = j, dem = 0;
		T[i][0][j] = 0;
		while(run < 1000){
			T[i][0][j] += run;
			dem++;
			run += calsum(run) + i;
		}
		f[i][0][j] = dem;
		nex[i][0][j] = run - 1000;
	}

	for(int t = 1; t <= 16; t++) for(int i = 0; i <= 190; i++) for(int j = 0; j <= 200; j++) if(i + j){
		int run = j;
		T[i][t][j] = 0;
		for(int k = 0; k < 10; k++){
			ll A = f[i + k][t - 1][run];
			ll B = nex[i + k][t - 1][run];
			ll C = add(T[i + k][t - 1][run], mu10[t + 2] % mod * k % mod * (A % mod) % mod);
			f[i][t][j] += A;
			run = B;
			T[i][t][j] = add(T[i][t][j], C);
		}
		nex[i][t][j] = run;
	}
//	cout << T[0][0][1] << endl;
}

ll trau(ll n){
	ll res = 0;
	ll run = 1;
	for(ll i = 0; i < n; i++){
		res = add(res, run % mod);
		run += calsum(run);
	}
	return res;
}

void sol(ll n){
	cout << cal(n) << endl;
}

void solve(){
//	freopen("in.txt", "r", stdin);
//	freopen("2.ans", "w", stdout);
//	freopen("2.in", "r", stdin);
//	freopen("2.ans", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	cin >> test;
	Rep(itest, test){
		cin >> n;
		sol(n);
	}
}

ll randNum(){
	ll res = 0;
	Rep(i, 15){
		ll x = rand() % 10;
		res = res * 10 + x;
	}
	return res + 1;
}

void gen(){
	srand(1413);
	freopen("2.in", "w", stdout);
	cout << 1000 << endl;
	For(i, 1, 100) cout << 1000000 - i << endl;
	For(i, 101, 200) cout << i * 1ll * 11234813 << endl;
	For(i, 201, 999) cout << randNum() << endl;
	cout << "1000000000000000" << endl;
}

int main() {

//	gen();
	solve();

//	cerr << clock() << endl;

	return 0;
}

