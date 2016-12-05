// Author: RR
// O(L^3 * logN)

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

int n, MOD;
const int INF = 1000111000111000111LL;

struct Matrix {
    int x[55][55];
} a, p[66];

int mul(int a, int b) {
    if (b == 0) return 0;
    int b1 = b / 1000000;
    int b2 = b % 1000000;

    return (((a * b1) % MOD * 1000000) + (b2 * a)) % MOD;
}

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    FOR(i,0,n) {
        FOR(j,0,n) {
            FOR(k,0,n) {
                res.x[i][j] = (res.x[i][j] + mul(a.x[i][k], b.x[k][j])) % MOD;
            }
        }
    }
    return res;
}

string s;

bool equals(int a, int b) {
    while (a && b) {
        if (s[a] != s[b]) return 0;
        --a; --b;
    }
    return 1;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int k;
        cin >> k >> MOD;
        cin >> s; n = SZ(s);
        s = " " + s + " ";

        memset(a.x, 0, sizeof a.x);
        FOR(i,0,n) {
            // already matched i characters
            FOR(c,'a','z') {
                // add character c
                if (i == n) {
                    a.x[n][i]++;
                }
                else {
                    int ok = 0;
                    FORD(j,i+1,1) if (s[j] == c) {
                        if (equals(j-1, i)) {
                            a.x[j][i]++;
                            ok = 1;
                            break;
                        }
                    }
                    if (!ok) a.x[0][i]++;
                }
            }
        }

        p[0] = a;
        FOR(i,1,60) p[i] = p[i-1] * p[i-1];

        Matrix res;
        memset(res.x, 0, sizeof res.x);
        FOR(i,0,n) res.x[i][i] = 1;

        FOR(bit,0,60) if ((k >> bit) & 1) {
            res = res * p[bit];
        }

        cout << res.x[n][0] << endl;
    }
}


