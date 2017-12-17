// Author: Pham Cao Nguyen
// Code submit trong ky thi.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
const int maxn = 1e5 + 5;
const int magic = 200;

struct state {
    int pos[maxn], moved[maxn];
    int max_time, min_time;
    vector<int> affected;
    vector<pair<int, vector<int> > > queries;
    
    void reset() {
        for (auto u: affected) pos[u] = u, moved[u] = 0;
        affected.clear();
    }

    void redo_queries(int max_time = 1e9) {
        reset();
        for (int x = 0; x < queries.size(); ++x) {
            auto &u = queries[x].second;
            if (queries[x].first > max_time) break;
            int first = get(u[0]);
            for (int i = 0; i + 1 < u.size(); ++i) {
                get(u[i]) = get(u[i + 1]);
            }
            get(u.back()) = first;
        }
    }
    
    void add_query(vector<int> &x, int T) {
        queries.push_back({T, x});
        sort(queries.begin(), queries.end());
        redo_queries();
    }
    
    int& get(int p) {
        if (!moved[p]) moved[p] = 1, affected.push_back(p);
        return pos[p];
    }
    
    int ask(int p, int mx_time) {
        if (mx_time >= max_time) return pos[p];
        redo_queries(mx_time); 
        int ans = pos[p];
        redo_queries();
        return ans;
    }

} Block[maxn / magic + 1];

int N, M, Q;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> Q;
    int sz = 0;
    for (int i = 1; (i - 1) * magic + 1 <= M; ++i) {
        ++sz;
        Block[i].max_time = min(M, i * magic);
        Block[i].min_time = (i - 1) * magic + 1;
        for (int j = 1; j <= N; ++j) Block[i].pos[j] = j;
    }
    while (Q--) {
        int typ; cin >> typ;
        if (typ == 0) {
            int k, x; cin >> k >> x;
            vector<int> q(k);
            for (auto &u: q) cin >> u;
            int id = (x - 1) / magic + 1;
            Block[id].add_query(q, x);
        } else {
            int d, x; cin >> d >> x;
            for (int i = sz; i >= 1; --i) {
                if (Block[i].min_time > x) continue;
                //cout << i << ' ' << Block[i].ask(d, x) << endl;
                d = Block[i].ask(d, x);
            }
            printf("%d\n", d);
        }
    }
}
