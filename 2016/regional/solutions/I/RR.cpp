// Author: RR

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
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MV = 1000 * 1000;
int smallSieve[MV + 11];
int cnt[111];
int p2[100111];
const int MOD = 1e9 + 7;

void init() {
    p2[0] = 1;
    FOR(i,1,100110) p2[i] = p2[i-1] * 2 % MOD;

    for(int i = 2; i <= 1000; i++) if (!smallSieve[i]) {
        int j = i*i;
        while (j <= MV) {
            smallSieve[j] = i;
            j += i;
        }
    }
}

int fact[100111];
int initial[100111];

int f[111][111][2];

void update(int& a, int b) {
    a = (a + b) % MOD;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    init();

    FOR(test,1,ntest) {
        int a, b; cin >> a >> b;

        // init fact = number of factors
        memset(fact, 0, sizeof fact);
        FOR(i,a,b) initial[i-a] = i;

        FOR(i,2,MV) if (!smallSieve[i]) {
            int x = (a / i) * i; if (x < a) x += i;
            assert(x >= a);

            while (x <= b) {
                int u = initial[x-a], k = 0;
                while (u % i == 0) {
                    u /= i;
                    ++k;
                }
                fact[x - a] += k;
                initial[x - a] = u;

                x += i;
            }
        }

        FOR(i,a,b) if (initial[i-a] > 1) ++fact[i-a];

        // init cnt
        memset(cnt, 0, sizeof cnt);
        int ln = 0;
        FOR(i,a,b) {
            cnt[fact[i-a]]++;
            ln = max(ln, fact[i-a]);
        }

        // DP(i, x, two)
        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        FOR(i,0,ln-1) FOR(x,0,63) FOR(greaterOne,0,1) {
            int cur = f[i][x][greaterOne];
            if (!cur) continue;

            int has = cnt[i+1];

            // do not choose (i+1)
            update(f[i+1][x][greaterOne], cur);

            if (has) {
                // odd number of (i+1)
                int greater2 = greaterOne;
                if (i+1 > 1) greater2 = 1;
                update(f[i+1][x ^ (i+1)][greater2], cur * p2[has-1] % MOD);

                // even number of (i+1)
                update(f[i+1][x][greater2], cur * (p2[has-1] - 1 + MOD) % MOD);
            }
        }

        cout << (f[ln][0][1] + f[ln][1][0]) % MOD << endl;
    }
}
