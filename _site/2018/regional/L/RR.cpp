#include "bits/stdc++.h"

using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

const string NO_SUCH_WORD = "NO SUCH WORD";

template<class num_t>
struct OrderedTree {
    int n;
    vector<num_t> a;
    num_t tot;
    vector<num_t> x;

    void init(int _n) {
        n = _n;
        a.resize(n);
        for (int i = 0; i < n; i++) a[i] = 0;
        tot = 0;
        x.resize(n + 1);
        for (int i = 0; i <= n; i++) x[i] = 0;
    }

    void upd(int p, num_t val, num_t cnt) {
        assert(0 <= p && p < n);
        a[p] = val, tot += cnt;
        for (p++; p <= n; p += p & -p) {
            x[p] += cnt;
        }
    }

    num_t find_by_order(num_t k) {
        assert(0 <= k && k <= tot);
        if (!k) return -1;
        int p = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (p + (1 << i) <= n && x[p + (1 << i)] < k) {
                k -= x[p + (1 << i)];
                p += 1 << i;
            }
        }
        return a[p];
    }
};

struct Query {
    int left, right;
    int k;
};

istream& operator >> (istream& cin, Query& q) {
    cin >> q.left >> q.right >> q.k;
    return cin;
}

struct Test {
    string bigString;
    vector<string> dict;
    vector<Query> queries;
};

istream& operator >> (istream& cin, Test& t) {
    cin >> t.bigString;
    int nDict, nQuery;
    cin >> nDict >> nQuery;
    REP(i,nDict) {
        string s; cin >> s;
        t.dict.push_back(s);
    }
    REP(i,nQuery) {
        Query q; cin >> q;
        t.queries.push_back(q);
    }
    return cin;
}

struct Next {
    vector<vector<int>> next;

    Next(const string& s) {
        next.resize('z' - 'a' + 1);
        int len = SZ(s);
        FOR(c,'a','z') {
            next[c - 'a'].resize(len + 1);
            next[c - 'a'][len] = len;

            FORD(i,len-1,0) {
                if (s[i] == c) next[c - 'a'][i] = i;
                else next[c - 'a'][i] = next[c - 'a'][i + 1];
            }
        }
    }
};

void solve(const Test& test) {
    vector<string> res;
    res.resize(SZ(test.queries));

    int len = SZ(test.bigString);
    vector< vector< vector< pair<int,int> > > > queriesAt(len, vector< vector< pair<int,int> > > (len, vector< pair<int,int> > ()));
    REP (i, SZ(test.queries)) {
        auto q = test.queries[i];

        int left = q.left - 1;
        int right = q.right - 1;

        queriesAt[left][right].emplace_back(i, q.k);
    }

    Next next(test.bigString);
    vector< vector< vector<int> > > appearsAt(len, vector< vector<int> > (len, vector<int>()));

    auto words = test.dict;
    sort(ALL(words));

    REP (i, SZ(words)) {
        string word = words[i];

        for (int left = 0; left < len; left++) {
            int at = left;
            for (char c : word) {
                at = next.next[c - 'a'][at];
                if (at >= len) {
                    at = len + 1;
                    break;
                }
                ++at;
            }
            --at;

            if (at < len) {
                appearsAt[left][at].push_back(i);
                assert(at - left + 1 >= SZ(word));
            }
        }
    }

    REP(left,len) {
        OrderedTree<int> all;
        all.init(SZ(words));

        FOR(right,left,len-1) {
            for (int id : appearsAt[left][right]) {
                all.upd(id, id, 1);
            }

            for (auto q : queriesAt[left][right]) {
                int qid = q.first;
                int k = q.second;

                if (k > all.tot) {
                    res[qid] = NO_SUCH_WORD;
                    continue;
                }

                int sid = all.find_by_order(k);
                res[qid] = words[sid].substr(0, 10);
            }
        }
    }
    for (auto s : res) cout << s << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    Test test; cin >> test;
    solve(test);
    return 0;
}
