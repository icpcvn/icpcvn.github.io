// Author: RR
// O(L^2)

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

string toString(int n) {
    stringstream ss; ss << n;
    return ss.str();
}

// f[length][good][mod8][lower]
int f[22][22][8][2];

int isGood(int n) {
    return n == 6 || n == 8;
}

int cntGood(int n) {
    int res = 0;
    while (n) {
        int c = n % 10;
        if (isGood(c)) ++res;

        n /= 10;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        string s = toString(n);
        int l = SZ(s);
        s = " " + s + " ";

        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;
        FOR(i,0,l-1) FOR(good,0,i) FOR(mod,0,7) FOR(lower,0,1)
        if (f[i][good][mod][lower]) {
            FOR(next,0,9) {
                int good2 = good; if (isGood(next)) ++good2;
                int mod2 = (mod * 10 + next) % 8;
                int lower2 = lower;

                if (!lower && next > (s[i + 1] - '0')) continue;
                if (next < (s[i + 1] - '0')) lower2 = 1;

                f[i+1][good2][mod2][lower2] += f[i][good][mod][lower];
            }
        }

        int res = 0;
        FOR(good,1,18) {
            // check if overflow
            assert(f[l][good][0][1] <= 1000111000111000111LL / good);

            res += f[l][good][0][1] * good;
        }
        res += cntGood(n);
        cout << res << endl;
    }
}
