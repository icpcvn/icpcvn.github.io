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

int n, g, k;
const int MN = 2011;
int cost[MN][MN], a[MN], dp[MN][MN], sum[MN], sum2[MN];

int getSum(int l, int r) {
    return sum[r] - sum[l-1];
}

int getSum2(int l, int r) {
    return sum2[r] - sum2[l-1];
}

void init1() {

    FOR(i,1,n) {
        FOR(j,i,n) {
            int mid = i + (j - i + 1) / 2;

            cost[i][j] =
                a[mid] * (mid - i + 1LL) - getSum(i, mid)
                + getSum(mid, j) - a[mid] * (j - mid + 1LL);
        }
    }
}

void init2() {
    FOR(i,1,n) {
        FOR(j,i,n) {
            int A = j - i + 1;
            int B = -2 * getSum(i, j);

            int approx_v = -B / (2 * A);
            cost[i][j] = 1e18;

            FOR(v,approx_v - 2, approx_v + 2) {
                int cur = getSum2(i, j) + A * v * v - 2 * getSum(i, j) * v;
                cost[i][j] = min(cost[i][j], cur);
            }
        }
    }
}

void compute(int i, int L, int R, int optL, int optR) {
    if (L > R) return ;

    int mid = (L + R) >> 1, savek = optL;
    dp[i][mid] = 1e18;
    FOR(k,optL,min(mid-1, optR)) {
        int cur = dp[i-1][k] + cost[k+1][mid];
        if (cur < dp[i][mid]) {
            dp[i][mid] = cur;
            savek = k;
        }
    }
    compute(i, L, mid-1, optL, savek);
    compute(i, mid+1, R, savek, optR);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    cin >> n >> g >> k;
    FOR(i,1,n) cin >> a[i];

    FOR(i,1,n) sum[i] = sum[i-1] + a[i];
    FOR(i,1,n) sum2[i] = sum2[i-1] + a[i] * a[i];

    if (k == 1) init1();
    else init2();

    FOR(i,0,n) FOR(j,0,n) dp[i][j] = 1e18;

    FOR(i,1,n) dp[1][i] = cost[1][i];

    FOR(i,2,g) {
        compute(i, 1, n, 0, n);
    }

    cout << dp[g][n] << endl;
    return 0;
}

