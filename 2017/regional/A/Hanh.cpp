// Author: Pham Vanh Hanh - skyvn97

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
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
template<class T>
    T Abs(const T &x) {
        return (x<0?-x:x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

#define MAX   2000200
const int MOD = (int)1e9 + 7;

int frac[MAX], finv[MAX];

int inverse(int x) {
    int res = 1;
    int mul = x;
    int k = MOD - 2;
    while (k > 0) {
        if (k & 1) res = 1LL * res * mul % MOD;
        mul = 1LL * mul * mul % MOD;
        k >>= 1;
    }
    assert(1LL * res * x % MOD == 1);
    return res;
}

void prepare(void) {
    frac[0] = finv[0] = 1;
    FOR(i, 1, MAX - 1) {
        frac[i] = 1LL * frac[i - 1] * i % MOD;
        finv[i] = inverse(frac[i]);
    }
}

int comb(int k, int n) {
    if (k > n) return 0;
    assert(n < MAX);
    return 1LL * frac[n] * finv[k] % MOD * finv[n - k] % MOD;
}

int countDivide(int n, int sum) {
    if (sum < 0) return 0;
    if (n == 0) return sum == 0 ? 1 : 0;
    return comb(n - 1, sum + n - 1);
}

int solve(int n, int sum, int lim) {
    int res = 0;
    FOR(k, 0, n) {
        int sign = k % 2 ? MOD - 1 : 1;
        int numGroup = comb(k, n);
        int numWay = sum >= (lim + 1LL) * k ? countDivide(n, sum - (lim + 1) * k) : 0;
        res = (res + 1LL * sign * numGroup % MOD * numWay) % MOD;
    }
    return res;
}

int main(void) {
    prepare();
    int n, m, d;
    while (cin >> n >> m >> d)
        cout << solve(m + 1, n, d) << endl;
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/

