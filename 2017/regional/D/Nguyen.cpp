// Author: Pham Cao Nguyen
// Code submit trong ky thi.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
const int maxn = 1e5 + 5;

int N, M, Q;
vector<char> A[maxn];

int next(int i, int j) {
    if (A[i][j] == '/') {
        if (j == 1 || A[i][j - 1] == '\\') return -1;
        return j - 1;
    } else {
        if (j == M || A[i][j + 1] == '/') return -1;
        return j + 1;
    }
}

namespace trau {
    void update(int u, int v, char c) {
        A[u][v] = c;
    }
    int ask(int j) {
        int i = 1;
        while (i <= N) {
            int nx = next(i, j);
            if (nx == -1) return -1;
            j = nx; ++i;
        }
        return j;
    }
};

namespace khong_trau {
    int sz;
    vector<int> nx[maxn];
    vector<int> rows;
    int dfs(int i, int j, int mx_row) {
        if (i == mx_row) return j;
        if (nx[i][j]) return nx[i][j];
        int p = next(i, j);
        if (p == -1) return nx[i][j] = -1;
        return nx[i][j] = dfs(i + 1, p, mx_row);
    }
    void init() {
        sz = sqrt(M * N);
        sz = (sz + M - 1) / M;
        for (int i = 1; i <= N; i += sz) rows.push_back(i);
        rows.push_back(N + 1);
        for (int i = 1; i <= N; ++i) nx[i].assign(M + 1, 0);
        for (int i = 0; i + 1 < rows.size(); ++i) {
            for (int j = 1; j <= M; ++j) dfs(rows[i], j, rows[i + 1]);
        }
    }
    void update(int u, int v, char c) {
        A[u][v] = c;
        int pos = upper_bound(rows.begin(), rows.end(), u) - rows.begin() - 1;
        for (int i = rows[pos]; i < rows[pos + 1]; ++i) {
            for (int j = 1; j <= M; ++j) nx[i][j] = 0;
        }
        for (int j = 1; j <= M; ++j) dfs(rows[pos], j, rows[pos + 1]);
    }
    int ask(int j) {
        for (int i = 0; i + 1 < rows.size(); ++i) {
            if (nx[rows[i]][j] == -1) return -1;
            j = nx[rows[i]][j];
        }
        return j;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> Q;
    for (int i = 1; i <= N; ++i) {
        A[i].assign(M + 1, 0);
        for (int j = 1; j <= M; ++j) cin >> A[i][j];
    }
    if (N <= sqrt(100000)) {
        while (Q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int x, y; cin >> x >> y;
                char c = (A[x][y] == '/' ? '\\' : '/');
                trau::update(x, y, c);
            } else {
                int x; cin >> x;
                printf("%d\n", trau::ask(x));
            }
        }
    } else {
        khong_trau::init();
        while (Q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int x, y; cin >> x >> y;
                char c = (A[x][y] == '/' ? '\\' : '/');
                khong_trau::update(x, y, c);
            } else {
                int x; cin >> x;
                printf("%d\n", khong_trau::ask(x));
            }
        }
    }
}
