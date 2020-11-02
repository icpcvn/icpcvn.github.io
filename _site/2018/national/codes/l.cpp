#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct Edge {
  int u, v;
  LL cap, flow;
  Edge() {}
  Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector<Edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;

  Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge(int u, int v, LL cap) {
    if (u != v) {
      E.emplace_back(u, v, cap);
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(v, u, 0);
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k: g[u]) {
        Edge &e = E[k];
        if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }

  LL DFS(int u, int T, LL flow = -1) {
    if (u == T || flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      Edge &e = E[g[u][i]];
      Edge &oe = E[g[u][i]^1];
      if (d[e.v] == d[e.u] + 1) {
        LL amt = e.cap - e.flow;
        if (flow != -1 && amt > flow) amt = flow;
        if (LL pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  LL MaxFlow(int S, int T) {
    LL total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (LL flow = DFS(S, T))
        total += flow;
    }
    return total;
  }
};

const int MAXN = 10000 + 10;
const int MAXL = 20;
const long long INF = (long long)(1e15);

int n;
int V[MAXN], C[MAXN];
int id[MAXN][MAXL];

bool is_prime(int x) {
    for(int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
    return (C[x] != 0);
}

int main() {
    //freopen("input.txt", "r", stdin);

    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> V[i];
    for(int i = 1; i <= n; ++i) cin >> C[i];

    int n_node = n + 1;
    int np = 0;
    for(int i = 2; i <= n; ++i)
        if (is_prime(i)) {
            np++;

            int j = i;
            id[i][0] = 0;
            while (j <= n) {
                id[i][0]++; id[i][ id[i][0] ] = n_node; n_node++;
                j = j * i;
            }
        }

    n_node++;

    Dinic f(n_node);
    int X = 1e4 + 1;
    for(int i = 2; i <= n; ++i)
        if (is_prime(i)) {
            int k = id[i][0];
            f.AddEdge(0, id[i][1], 0 + X);
            for(int j = 1; j <= k; ++j) {
                int cost = j * j * C[i];
                f.AddEdge(id[i][j], ( (j < k) ? id[i][j + 1] : (n_node - 1)), cost + X);
            }
        }

    for(int i = 1; i <= n; ++i) {
        f.AddEdge(0, i, 0 + X);
        f.AddEdge(i, n_node - 1, -V[i] + X);

        int ii = i;
        for(int j = 2; j <= ii; ++j)
            if (ii % j == 0) {
                int k = 0;
                while (ii % j == 0) {
                    k++; ii /= j;
                }
                f.AddEdge(i, id[j][k], INF);
            }
    }

    long long res = - f.MaxFlow(0, n_node - 1) + 1LL * X * (n + np) ;
    cout << res << "\n";
}
