// Author: RR
// O(N), stack

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

#define left left____
int pos[MN], h[MN], st[MN], left[MN], top, sum[MN], water[MN];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        int n; GI(n);
        FOR(i,1,n) GI(pos[i]);
        FOR(i,1,n) {
            GI(h[i]);
            sum[i] = sum[i-1] + h[i];
        }

        top = 0;
        st[0] = 0;
        FOR(i,1,n) {
            while (top && h[st[top]] <= h[i]) --top;
            left[i] = st[top];
            st[++top] = i;
        }

        h[0] = 1000111000;
        pos[0] = -1;
        FOR(i,1,n) {
            int u = left[i];
            water[i] = water[u] + (pos[i] - pos[u]) * h[i] - (sum[i] - sum[u]);
        }

        int q; GI(q);
        while (q--) {
            int k; GI(k);
            int l = 0, r = n, res = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (water[mid] < k) {
                    res = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            printf("%lld\n", res);
        }
    }
}

