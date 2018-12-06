// Author: Nguyen Xuan Tung

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int n, q;
string s;
vector<string> t;
vector<int> ans(300001, -1);
vector<tuple<int, int, int>> que[501];

void solve(int start) {
      vector<int> ptr(n);
      vector<int> bucket[26];
      for (int i = 0; i < n; i++) {
            int a = t[i][0] - 'a';
            bucket[a].push_back(i);
      }

      int petr = start;

      indexed_set<int> st;

      for (auto [r, k, i]: que[start]) {
            for (; petr <= r; petr++) {
                  int c = s[petr] - 'a';

                  vector<int> tmp = bucket[c];
                  bucket[c].clear();
                  for (auto u: tmp) {
                        ptr[u]++;

                        if (ptr[u] == t[u].size()) st.insert(u);
                        else {
                              int a = t[u][ptr[u]] - 'a';
                              bucket[a].push_back(u);
                        }
                  }
            }

            if (k < st.size()) {ans[i] = *st.find_by_order(k);}
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> s >> n >> q;
      for (int i = 0; i < n; i++) {
            string x; cin >> x;
            t.push_back(x);
      }
      sort(t.begin(), t.end());
      for (int i = 0; i < q; i++) {
            int l, r, k; cin >> l >> r >> k; l--; r--; k--;
            que[l].emplace_back(r, k, i);
      }
      for (int i = 0; i < s.size(); i++) {
            sort(que[i].begin(), que[i].end());
      }

      for (int i = 0; i < s.size(); i++) {
            solve(i);
      }

      for (int i = 0; i < q; i++) {
            if (ans[i] == -1) {cout << "NO SUCH WORD\n";}
            else {
                  int ss = ans[i];
                  for (int j = 0; j < min(10, (int)t[ss].size()); j++) {
                        cout << t[ss][j];
                  }
                  cout << '\n';
            }
      }
}
