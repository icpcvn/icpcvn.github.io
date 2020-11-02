// Author: Pham Cao Nguyen
// Code submit trong ky thi.

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef pair<int, int> ii;
const int maxn = 5e4 + 5;

struct Tree {
    int N;
    vector<int> G[maxn];
    int child[maxn];
    ll sumDn[maxn], sumUp[maxn];
    ll sqDn[maxn], sqUp[maxn];
    void read() {
        cin >> N;
        for (int i = 1; i < N; ++i) {
            int u, v; cin >> u >> v;
            G[u].push_back(v); G[v].push_back(u);
        }
    }
    void dfs_down(int v, int par) {
        child[v] = 1;
        sumDn[v] = 0, sqDn[v] = 0;
        for (auto u: G[v]) {
            if (u == par) continue;
            dfs_down(u, v);
            child[v] += child[u];
            sumDn[v] += sumDn[u] + child[u];
            sqDn[v] += sqDn[u] + 2 * sumDn[u] + child[u];
        }
    }
    void dfs_up(int v, int par, int cnt, ll sum, ll sq) {
        sumUp[v] = sum;
        sqUp[v] = sq;
        for (auto u: G[v]) {
            if (u == par) continue;
            int cntOut = child[v] - child[u];
            ll sumOut = sumDn[v] - sumDn[u] - child[u];
            ll  sqOut  = sqDn[v] - sqDn[u] - 2 * sumDn[u] - child[u];
            dfs_up(u, v, cnt + cntOut, sum + sumOut + cnt + cntOut, sq + sqOut + 2 * (sumOut + sum) + cntOut + cnt);
        }
    }
    void run() {
        read(); dfs_down(1, 0); dfs_up(1, 0, 0, 0, 0);
    }
    ll sum(int v) { return sumUp[v] + sumDn[v]; }
    ll sq(int v) { return sqUp[v] + sqDn[v]; }
} A, B;

struct line {
    ll a, b;
    ll val(ll x) { return a * x + b; }
};

struct Hull {
    deque<line> q;
    long double intx(line &a, line &b) {
        return (1.0L * b.b - 1.0L * a.b) * 1.0L / (a.a - b.a);
    }
    bool bad(line &a, line &b, line &c) {
        return intx(a, b) > intx(b, c);
    }
    void add(line l) {
        if (q.size() && q.back().a == l.a) {
            l.b = min(l.b, q.back().b);
            q.pop_back();
        }
        int sz = q.size();
        while (q.size() >= 2 && bad(q[sz - 2], q[sz - 1], l)) --sz, q.pop_back();
        q.push_back(l);
    }
    ll query(ll x) {
        while (q.size() > 1 && q[0].val(x) >= q[1].val(x)) q.pop_front();
        return q.front().val(x);
    }
} H;

int id[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    A.run(); B.run();
    for (int i = 1; i <= B.N; ++i) id[i] = i;
    sort(id + 1, id + B.N + 1, [&](int a, int b) { return B.sum(a) > B.sum(b); });
    for (int i = 1; i <= B.N; ++i) {
        int pos = id[i];
        H.add({2 * B.sum(pos), 2 * B.sum(pos) * A.N + A.N * B.sq(pos)});
    }
    ll ans = ll(-1);
    for (int i = 1; i <= A.N; ++i) id[i] = i;
    sort(id + 1, id + A.N + 1, [&](int a, int b) { return A.sum(a) < A.sum(b); });
    for (int i = 1; i <= A.N; ++i) {
        int pos = id[i];
        ans = min(ans, A.sq(pos) * B.N + 2 * A.sum(pos) * B.N + H.query(A.sum(pos)) + 1LL * A.N * B.N);
    }
    ll sum = 0;
    for (int i = 1; i <= A.N; ++i) sum += A.sq(i);
    for (int j = 1; j <= B.N; ++j) sum += B.sq(j);
    //cout << ans << ' ' << sum << endl;
    cout << ans + sum / 2 << endl;
}
