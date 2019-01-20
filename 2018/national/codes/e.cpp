#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define ALL(v) (v).begin(), (v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x > y + eps) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x + eps < y) {
            x = y;
            return true;
        } else return false;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

#define MAX   1000100
#define SQRT   1515
#define LENGTH   20

int result[MAX], pw[MAX][LENGTH + 3];

int gcd(int a, int b) {
    while (true) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (a > b) a %= b; else b %= a;
    }
}

int getSum(int p, int q, int k) {
    long long res = 0;
    REP(i, k + 1) {
        res += 1LL * pw[p][i] * pw[q][k - i];
        if (res >= MAX) return MAX;
    }
    return res;
}

void prepare(void) {
    FOR(i, 1, MAX - 1) {
        pw[i][0] = 1;
        FOR(j, 1, LENGTH) pw[i][j] = min(1LL * MAX, 1LL * pw[i][j - 1] * i);
    }

    int numPair = 0;
    FOR(k, 2, LENGTH) FOR(q, 1, SQRT) {
        if (pw[q][k] >= MAX) break;
        FOR(p, q + 1, SQRT) {
            int sum = getSum(p, q, k);
            if (sum >= MAX) break;
            if (gcd(p, q) > 1) continue;
            numPair++;
            result[sum]++;
        }
    }
    int cnt = 0;
    FOR(i, 1, MAX - 1) if (result[i] > 0) cnt++;
    cerr << cnt << endl;

    cerr << numPair << endl;
    FORD(i, MAX - 1, 1) for (int j = 2 * i; j < MAX; j += i) result[j] += result[i];
}

int solve(int n) {
    if (n < 3) return 1;
    int numOne = 1;
    int numTwo = n % 2 == 0 ? n / 2 - 1 : n / 2;
    return numOne + numTwo + result[n];
}

int main(void) {
    prepare();
    int input; scanf("%d", &input);
    while (scanf("%d", &input) == 1) printf("%d ", solve(input)); printf("\n");
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/