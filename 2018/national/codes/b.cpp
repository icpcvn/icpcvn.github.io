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

#define MAX   10

class Solver {
private:
    struct Result {
        int turn, info, a, b;
        Result(int _turn = 0, int _info = 0, int _a = 0, int _b = 0) {
            turn = _turn; info = _info; a = _a; b = _b;
        }
    };

    int length;
    vector<int> matches[2 * MAX][MAX][MAX];

    Result matchResult(int mask) {
        int sa = 0, sb = 0;
        int na = length, nb = length;
        int j = 2 * length;
        REP(i, length * 2) {
            j--;
            if (i % 2 == 0) {
                na--;
                if (BIT(mask, j)) sa++;
            } else {
                nb--;
                if (BIT(mask, j)) sb++;
            }

            int subMatch = mask >> j;
            if (sa > sb + nb) return Result(i + 1, subMatch, sa, sb);
            if (sb > sa + na) return Result(i + 1, subMatch, sa, sb);
        }
        return Result(2 * length, mask, sa, sb);
    }

    void prepare(void) {
        cerr << "PREPARING..." << endl;
        REP(mask, MASK(2 * length)) {
            Result result = matchResult(mask);
            matches[result.turn][result.a][result.b].push_back(result.info);
        }
        REP(turn, 2 * length + 1) REP(sa, length + 1) REP(sb, length + 1) {
            vector<int> &cur = matches[turn][sa][sb];
            if (cur.empty()) continue;
            sort(ALL(cur));
            cur.resize(unique(ALL(cur)) - cur.begin());
        }
    }

    bool onlyMatch(int turn, int sa, int sb, int subMatch, int subTurn) {
        int minMask = subMatch << (turn - subTurn);
        int maxMask = minMask ^ (MASK(turn - subTurn) - 1);
        vector<int> &cur = matches[turn][sa][sb];
        int L = lower_bound(ALL(cur), minMask) - cur.begin();
        int R = upper_bound(ALL(cur), maxMask) - cur.begin();
        assert(L < R);
        return R - L == 1;
    }

public:
    Solver() {
        length = 0;
    }

    Solver(int length) {
        this->length = length;
        REP(i, 2 * length + 1) REP(j, length + 1) REP(k, length + 1)
            matches[i][j][k].clear();
        prepare();
    }

    pair<int, int> solve(int mask) {
        Result result = matchResult(mask);
        mask = result.info;

        FOR(i, 0, result.turn) {
            int subMatch = mask >> (result.turn - i);
            if (onlyMatch(result.turn, result.a, result.b, subMatch, i)) return make_pair(result.turn, i);
        }
        return make_pair(result.turn, result.turn);
    }
};

const string WIN = "E";
Solver solver[MAX];

void prepare(void) {
    FOR(i, 1, MAX - 1) solver[i] = Solver(i);
}

void process(void) {
    int n; cin >> n;
    int mask = 0;
    REP(i, 2 * n) {
        string input; cin >> input;
        mask = (mask << 1) ^ (input == WIN);
    }
    pair<int, int> res = solver[n].solve(mask);
    printf("%d %d\n", res.fi, res.se);
}

int main(void) {
#ifdef SKY
    freopen("tmp.txt", "r", stdin);
#endif // SKY
    ios::sync_with_stdio(false);
    prepare();
    int t; cin >> t;
    REP(love, t) process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/