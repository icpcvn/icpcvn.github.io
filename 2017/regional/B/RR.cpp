// Author: RR

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

const int MN = 1000111;
int f[MN];
int primes[MN], nPrime, sieve[MN];

void init() {
    FOR(i,2,2000) if (!sieve[i]) {
        for (int j = i*i; j < MN; j += i) {
            sieve[j] = i;
        }
    }
    FOR(i,2,MN-1) if (!sieve[i]) {
        primes[++nPrime] = i;
    }
}

int power(int p, int k, int MOD) {
    if (k == 0) return 1 % MOD;
    if (k == 1) return p % MOD;

    int mid = power(p, k / 2, MOD);
    mid = mid * mid % MOD;

    if (k % 2 == 1) return mid * p % MOD;
    else return mid;
}

// Return max k: n % (p ^ k) == 0
int get(int p, int n) {
    if (n < p) return 0;
    return n / p + get(p, n / p);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int ntest; cin >> ntest;
    init();
    while (ntest--) {
        int n, MOD; cin >> n >> MOD;
        f[0] = 1 % MOD;
        f[1] = 2 % MOD;
        FOR(i,2,n) f[i] = (f[i-1] + f[i-2]) % MOD;

        int res;
        if (n % 2 == 1) res = f[n];
        else {
            res = f[n];
            int C = 1;

            FOR(i,1,nPrime) {
                int k = get(primes[i], n)
                    - 2 * get(primes[i], n / 2);

                assert(k >= 0);
                C = C * power(primes[i], k, MOD) % MOD;
            }

            res = (res + C) % MOD;
            res = (res - (n / 2 + 1) % MOD + MOD) % MOD;
        }
        cout << res << '\n';
    }
    return 0;
}

