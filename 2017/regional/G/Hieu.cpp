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

#define maxn 1000005

int n, k;
ll a[maxn];
int num[105];

void solve(){
  cin >> n >> k;
  ms(num, 0);
  ll sum = 0, half = 0;
  For(i, 1, n){
    cin >> a[i];
    num[a[i] % k]++;
    sum += a[i];
  }
  vector<int> V;
  Rep(i, k) {
	  if(num[i] & 1) V.pb(i);
	  half += (num[i] / 2) * 1ll * i;
  }
  sum %= k;
  half %= k;

  if(sum == 0 || sz(V) == 0 || sz(V) > 2){
    cout << "DRAW" << endl;
  } else if(sz(V) == 1){
    if(half == 0){
      cout << "SECOND" << endl;
    } else if((half + V[0]) % k == 0){
      cout << "FIRST" << endl;
    } else cout << "DRAW" << endl;
  } else{
    if((half + V[0]) % k == 0 || (half + V[1]) % k == 0){
      cout << "FIRST" << endl;
    } else cout << "DRAW" << endl;
  }
}

int main() {
  /* freopen("out.txt", "w", stdout); */
  //freopen("game.inp", "r", stdin);
  //freopen("game.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int ntest;
	cin >> ntest;
	while(ntest--)
  solve();

	return 0;
}

