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

#define maxn 1005

int n;
ll p[maxn];

ll mu(ll x, ll k){
  if(k == 0) return 1;
  if(k & 1) return mu(x, k - 1) * x % mod;
  ll T = mu(x, k >> 1);
  return T * T % mod;
}

ll go(int c) {

  ll res = 0;
  ll POS = (1ll << c), REST = POS-1;

	ll cnt[] = {1,0}, ncnt[2];
	Rep(i, n){
		ll a,b;
		if (p[i] & (1ll << c)) { a = 1ll<<c; b = 1 + (p[i]&REST); }
		else { a = 1+(p[i]&REST); b = 0; }
    a %= mod;
    b %= mod;
		ncnt[0] = (cnt[0] * a % mod + cnt[1] * b % mod) % mod;
		ncnt[1] = (cnt[0] * b % mod + cnt[1] * a % mod) % mod;
		copy(ncnt, ncnt+2, cnt);
	}

	if (c == 0) {
		res = 1;
		bool found = false;
		Rep(i, n) if (p[i] & 1) {
			res = res * 2 % mod;
			found = true;
		}
		if (found) res = res * mu(2, mod - 2) % mod;
		return res;
	}

	ll sum = 0;
	Rep(i, n) if (p[i] & (1ll<<c)) sum ^= 1;

	if (sum == 0) {
		ll prod = 1;
		Rep(i, n) prod = prod * ((1 + (p[i] & REST)) % mod) % mod;
		return res = ((cnt[0] + mod - prod) % mod * mu((1ll<<c) % mod, mod - 2) + go(c-1)) % mod;
	}
	else {
		return res = cnt[0] * mu((1ll<<c) % mod, mod - 2) % mod;
	}
}

string toString(int x){
  stringstream ss;
  ss << x;
  string res;
  ss >> res;
  return res;
}

ll cal(vector<ll> a){
  Rep(i, n) p[i] = a[i];
  return go(61);
}

void solve(int itest){
  /* freopen((toString(itest) + ".in").c_str(), "r", stdin); */
  /* freopen((toString(itest) + ".ans").c_str(), "w", stdout); */

  cin >> n;
  vector<ll> a(n);
  Rep(i, n) cin >> a[i];
  ll res = cal(a);
  Rep(i, n) --a[i];
  Rep(i, n){
    a[i]++;
    res = (res + mod - cal(a)) % mod;
    a[i]--;
  }
  res = (res + cal(a) * (n - 1) % mod) % mod;
  cout << res << endl;
}

ll randN(int num){
  ll res = 0;
  Rep(i, num) res = res * 10 + rand() % 10;
  return res + 1;
}

void gen(int itest){

  freopen((toString(itest) + ".in").c_str(), "w", stdout);
  if(itest == 0){
    cout << 3 << endl;
    cout << "4 5 6" << endl;
  } else{
    if(itest <= 20){
      n = itest * 10;
      cout << n << endl;
      For(i, 1, n) {
        cout << randN(3);
        if(i == n) cout << endl;
        else cout << " ";
      }
    } else{
      n = min(1000, itest * 25);
      cout << n << endl;
      For(i, 1, n) {
        cout << randN(18);
        if(i == n) cout << endl;
        else cout << " ";
      }
    }
  }
}

int main() {

  /* srand(1412); */
  /* For(i, 0, 50) */
  /*   gen(i); */
  /* ll run = 0; */
  For(i, 0, 0){
    solve(i);
    /* ll temp = clock(); */
    /* cerr << (ld)(temp - run) / CLOCKS_PER_SEC << endl; */
    /* run = temp; */
  }

	return 0;
}

