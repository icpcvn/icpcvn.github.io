// Author: RR
// O(N)

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

const int MN = 100111;
int n, m, a[MN], sum[MN];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> m;
        FOR(i,1,n) {
            cin >> a[i];
            sum[i] = sum[i-1] + a[i];
        }
        int res = 0;
        FOR(i,1,n) if (a[i] == m) {
            int left = i, right = i;
            while (left > 1 && a[left-1] > a[i]) --left;
            while (right < n && a[right+1] > a[i]) ++right;

            res = max(res, sum[right] - sum[left-1]);
        }
        cout << res << endl;
    }
}

