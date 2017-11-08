// Author: RR
// Segment tree O(Q*logN)

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

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
	unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
	asm(
		"divl %4; \n\t"
		: "=a" (d), "=d" (m)
		: "d" (xh), "a" (xl), "r" (y)
	);
#else
	__asm {
		mov edx, dword ptr[xh];
		mov eax, dword ptr[xl];
		div dword ptr[y];
		mov dword ptr[d], eax;
		mov dword ptr[m], edx;
	};
#endif
	out_d = d; out_m = m;
}

template<int MOD>
struct ModInt {
	static const int Mod = MOD;
	unsigned x;
	ModInt() : x(0) { }
	ModInt(signed sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	int get() const { return (int)x; }

	ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator*=(ModInt that) {
		unsigned dummy;
		fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, x);
		return *this;
	}
	ModInt operator*(ModInt that) const {
		ModInt res;
		unsigned dummy;
		fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, res.x);
		return res;
	}
	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
};
typedef ModInt<1000000007> mint;

const int MN = 200111;
struct Node {
    mint sum;
    mint lazy[4];
} it[MN * 4];
mint sum[4][MN];

mint getSum(int t, int l, int r) {
    return sum[t][r] - sum[t][l-1];
}

void down(int i, int l, int r, int mid) {
    REP(t,4) {
        mint val = it[i].lazy[t];
        if (val.x == 0) continue;

        it[i<<1].lazy[t] += val;
        it[i<<1|1].lazy[t] += val;

        it[i<<1].sum += val * getSum(t, l, mid);
        it[i<<1|1].sum += val * getSum(t, mid+1, r);

        it[i].lazy[t] = mint(0);
    }
}

void up(int i) {
    it[i].sum = it[i<<1].sum + it[i<<1|1].sum;
}

mint get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return mint(0);
    if (u <= l && r <= v) return it[i].sum;
    
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    mint res = get(i<<1, l, mid, u, v) + get(i<<1|1, mid+1, r, u, v);
    up(i);

    return res;
}

mint f(int t, int u) {
    if (t == 3) return 1;
    if (t == 2) return mint(-3*u + 6);
    if (t == 1) return mint(3*u*u) - mint(12*u) + mint(11);
    if (t == 0) return mint(-1*u) * mint(u*u) + mint(6*u*u) - mint(11*u) + mint(6);
    throw 1ll;
}

void update(int i, int l, int r, int u, int v, int sign) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        REP(t, 4) {
            mint val = f(t, u) * mint(sign);

            it[i].sum += val * getSum(t, l, r);
            it[i].lazy[t] += val;
        }
        return ;
    }

    int mid = (l + r) >> 1;
    down(i, l, r, mid);
    update(i<<1, l, mid, u, v, sign);
    update(i<<1|1, mid+1, r, u, v, sign);
    up(i);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;

    int n, q; cin >> n >> q;
    FOR(i,1,n) {
        sum[0][i] = sum[0][i-1] + mint(1);
        sum[1][i] = sum[1][i-1] + mint(i);
        sum[2][i] = sum[2][i-1] + mint(i) * mint(i);
        sum[3][i] = sum[3][i-1] + mint(i) * mint(i) * mint(i);
    }
    while (q--) {
        int typ, u, v; cin >> typ >> u >> v;
        if (typ == 0) cout << get(1, 1, n, u, v).x << '\n';
        else if (typ == 1) update(1, 1, n, u, v, +1);
        else update(1, 1, n, u, v, -1);
    }
    return 0;
}

