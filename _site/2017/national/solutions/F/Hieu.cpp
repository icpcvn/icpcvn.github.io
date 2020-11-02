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

#define maxn 400005

ll f[20][1 << 10], F[20][1 << 10], C[11][11];

ll mu(ll x, ll k){
	if(k == 0) return 1;
	if(k & 1) return mu(x, k - 1) * x % mod;
	ll T = mu(x, k >> 1);
	return T * T % mod;
}

ll add(ll x, ll y){
  ll res = (x + y);
  if(res >= mod) res -= mod;
  return res;
}
ll sub(ll x, ll y){
  ll res = (x - y);
  if(res < 0) res += mod;
  return res;
}

void init(){
	ms(f, 0);
	ms(F, 0);
  F[0][0] = 1;
	Rep(i, 10) f[1][1 << i] = 1;

	for(int i = 2; i <= 18; i++){
		for(int j = 0; j < i; j++) Rep(mask, 1 << 10){
			int x = mask;
			if(j < i - 1) x = onbit(x, 0);
			F[i - 1][x] = add(F[i - 1][x], f[j][mask]);
		}
		For(j, 1, 9) Rep(mask, 1 << 10){
			int x = onbit(mask, j);
			f[i][x] = add(f[i][x], F[i - 1][mask]);
		}
	}

  ms(C, 0);
  Rep(i, 11) C[0][i] = 1;
  For(i, 1, 10) For(j, 1, i) C[j][i] = add(C[j - 1][i - 1], C[j][i - 1]);

}

int test;
ll A, B, k, d;

ll calA(ll x, int k){
  ll res = 1;
  for(int i = 0; i < k; i++){
    ll A = (x - i) % mod;
    if(A >= mod) A -= mod;
    res = res * A % mod;
  }
  return res;
}

vector<ll> cal(ll x){
  int a[22], m = 0;
  vector<ll> res(1 << 10);
  if(x == 0) a[++m] = 0;
  while(x){
    a[++m] = x % 10;
    x /= 10;
  }
  int run = 0;
  for(int i = 1; i < m; i++) Rep(mask, 1 << 10) res[mask] = add(res[mask], f[i][mask]);
  for(int i = m; i >= 1; i--){
    int start = 0;
    if(i == m && i > 1) start = 1;
    for(int j = start; j < a[i]; j++){
      int M = onbit(run, j);
      Rep(mask, 1 << 10){
        int MM = (M | mask);
        res[MM] = add(res[MM], F[i - 1][mask]);
      }
    }
    run = onbit(run, a[i]);    
  }
  res[run]++;
  return res;
}

ll sol(){
  vector<ll> V1 = cal(B), V2 = cal(A - 1), V(1 << 10);
  Rep(mask, 1 << 10) {
    V[mask] = sub(V1[mask], V2[mask]);
    for(int mask1 = mask; mask1 > 0; mask1 = mask & (mask1 - 1)){
      int x = mask ^ mask1;
      V[x] = add(V[x], V[mask]);
    }
  }
  
  ll res = 0;
  
  ll mul = 1;
  For(i, 1, k) mul = mul * i % mod;
  mul = mu(mul, mod - 2);

  for(int mask = 0; mask < (1 << 10); mask++){
    int num = cntbit(mask);
    ll so = V[mask];
    if(num >= d){
      ll need = calA(so, k) * mul % mod * C[d][num] % mod;
      if((num - d) % 2 == 0) res = add(res, need);
      else res = add(res, mod - need);
    }
  }
  
  return res;
}

void solve(){
  
	/* freopen("2.in", "r", stdin); */
	/* freopen("2.ans", "w", stdout); */

	ios::sync_with_stdio(0);
	cin.tie(0);
  init();
  cin >> test;
  Rep(itest, test){
    cin >> A >> B >> k >> d;
    cout << sol() << endl;
  }
}

ll randN(int num){
  ll res = 0;
  Rep(i, num) res = res * 10 + rand() % 10;
  res = min(res + 1, (ll)(1e18 - 2));
  return res;
}

void gen1(){
  
	freopen("1.in", "w", stdout);
  cout << 100 << endl;
  ll run = 1;
  srand(1412);
  For(i, 1, 10){
    run = run * 10;
    cout << 1 << " " << run - 1 << " " << 2 << " " << i << endl; 
  }
  For(i, 11, 50){
    A = randN(9);
    B = randN(9);
    if(A > B) swap(A, B);
    k = rand() % 2 + 2;
    d = rand() % 3; 
    cout << A << " " << B << " " << k << " " << d << endl;
  }
  For(i, 51, 99){
    A = randN(18);
    B = randN(18);
    if(A > B) swap(A, B);
    k = rand() % 9 + 2;
    d = rand() % 11; 
    cout << A << " " << B << " " << k << " " << d << endl;
  }
  cout << "1 999999999999999999 10 5" << endl;
}

void gen2(){
	freopen("2.in", "w", stdout);
  cout << 100 << endl;
  ll run = 1;
  srand(1413);
  For(i, 1, 10){
    run = run * 10;
    cout << 1 << " " << run - 1 << " " << 2 << " " << 0 << endl; 
  }
  For(i, 11, 50){
    A = randN(i / 5 - 1);
    B = randN(i / 5 - 1);
    if(A > B) swap(A, B);
    k = rand() % 2 + 2;
    d = rand() % 3; 
    cout << A << " " << B << " " << k << " " << d << endl;
  }
  For(i, 51, 99){
    A = randN(i / 5 - 1);
    B = randN(i / 5 - 1);
    if(A > B) swap(A, B);
    k = rand() % 9 + 2;
    d = rand() % 11; 
    cout << A << " " << B << " " << k << " " << d << endl;
  }
  cout << "1 999999999999999999 10 5" << endl;
}

int main() {
  
  /* gen2(); */
  solve();
  
  cerr << (ld)clock() / CLOCKS_PER_SEC << endl;
	return 0;
}

