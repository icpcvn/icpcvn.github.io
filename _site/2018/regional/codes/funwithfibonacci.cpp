#include <bits/stdc++.h>

using namespace std;

const int maxm = 1e7 + 7;
int d[maxm];
long long pi[maxm];
vector <int> good_mod;
vector <int> in;
vector <vector <int> > circles[10];
vector <int> g[10];
vector <int> id[10];
vector <int> cc[10];

int fib(long long n, int mod) {
    long long x = 0, y = 1;
    for (int i = 59; i >= 0; --i) {
        long long ox = x, oy = y;
        y = (ox * ox + oy * oy) % mod;
        x = ox * (oy + oy - ox + mod) % mod;
        if (n >> i & 1) y = (y + x) % mod, x = (y - x + mod) % mod;
    }
    return x;
}

long long cal(long long n, long long k, int m) {
    if (m == 1) return 0;
    if (k == 1) return fib(n, m);
    if (pi[m] != m) return fib(cal(n, k - 1, pi[m]), m);
    int idm = lower_bound(good_mod.begin(), good_mod.end(), m) - good_mod.begin();
    int cur = fib(n, m);
    --k;
    while (!~cc[idm][cur]) {
        cur = g[idm][cur];
        --k;
        if (k == 0) return cur;
    }
    int pos = cc[idm][cur], idx = id[idm][cur];
    idx = (idx + k) % circles[idm][pos].size();
    return circles[idm][pos][idx];
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 1; i < maxm; ++i) d[i] = i;
    for (int i = 2; i < maxm; ++i) {
        if (d[i] == i) {
            if (i == 2) pi[i] = 3;
            else if (i == 5) pi[i] = 20;
            else if (i % 10 == 1 || i % 10 == 9) pi[i] = i - 1;
            else pi[i] = 2 * (i + 1);
            for (int j = i + i; j < maxm; j += i) d[j] = i;
        }
        else {
            int t = d[i], m = 1, x = i;
            while (x % t == 0) x /= t, m *= t;
            if (x == 1) pi[i] = t * pi[i/t];
            else pi[i] = pi[m] / __gcd(pi[m], pi[x]) * pi[x];
        }
        if (pi[i] == i) {
            int idm = good_mod.size();
            good_mod.push_back(i);
            id[idm].assign(i, -1);
            cc[idm].assign(i, -1);
            g[idm].assign(i, 0);
            in.assign(i, 0);

            g[idm][0] = 0, g[idm][1] = 1;
            in[0] = in[1] = 1;
            for (int j = 2; j < i; ++j) g[idm][j] = (g[idm][j-1] + g[idm][j-2]) % i, ++in[g[idm][j]];
            queue <int> q;
            for (int j = 0; j < i; ++j) if (!in[j]) q.push(j);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                int v = g[idm][u];
                --in[v];
                if (!in[v]) q.push(v);
            }
            for (int j = 0; j < i; ++j) if (in[j]) {
                int x = j;
                circles[idm].push_back(vector <int> ());
                while (in[x]) {
                    cc[idm][x] = circles[idm].size() - 1;
                    id[idm][x] = circles[idm].back().size();
                    circles[idm].back().push_back(x);
                    in[x] = 0;
                    x = g[idm][x];
                }
            }
        }
    }

    int ntest; cin >> ntest;
    while (ntest--) {
        long long n, k, m;
        cin >> n >> k >> m;
        cout << cal(n, k, m) << endl;
    }
    return 0;
}