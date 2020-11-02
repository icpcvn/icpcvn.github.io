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

#define maxn 21
//#define maxv 100005

int num;
int test;
int n, a[maxn];
ll f[maxn][maxn][10][2];

ll go(int id, int so, int du, int behon){
//	cout << id << " " << so << " " << du << " " << behon << endl;
	if(id < 0){
		if(du == 0) return so;
		else return 0;
	}
	ll &ret = f[id][so][du][behon];
	if(ret != -1) return ret;
	ret = 0;
	int l = 0, r = 9;
	if(!behon) r = a[id];
	For(i, l, r){
		int dnew = (du * 10 + i) % 8;
		int sonew = so;
		if(i == 8 || i == 6) sonew++;
		ret += go(id - 1, sonew, dnew, behon | (i < a[id]));
	}
	return ret;
}

ll dem(ll X){
	ll res = 0;
	while(X){
		ll d = X % 10;
		res += (d == 6 || d == 8);
		X /= 10;
	}
	return res;
}

void sol(){
	ms(f, -1); ms(a, 0);
	ll X, temp;
	cin >> X;
	temp = X - 1;
	n = 0;
	while(temp){
		a[n++] = temp % 10;
		temp /= 10;
	}

	cout << go(19, 0, 0, 0) + dem(X) << "\n";
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> test;
	Rep(itest, test){
		sol();
	}

    return 0;
}

