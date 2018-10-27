#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
const int maxn = 2000;
int p[40000006];
int n;
int a[200005];
int id[2005], m;
bitset <310> f[200005];
map <int, vector <int> > vec;
int mark[200005];

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 1; i <= maxn * maxn; ++i) p[i] = i;
    for (int i = 2; i <= maxn; ++i) if (p[i] == i) {
        id[i] = m++;
        for (int j = i * i; j <= maxn * maxn; j += i) p[j] = i;
    }
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        int tmp = a[i];
        while (tmp > 1) {
            int d = p[tmp];
            if (d > maxn) vec[d].push_back(i);
            else f[i].flip(id[d]);
            tmp /= d;
        }
    }
    int rnk = 0;
    for (auto v: vec) {
        vector <int> &cur = v.second;
        for (int i = 1; i < cur.size(); ++i) f[cur[i]] ^= f[cur[0]];
        mark[cur[0]] = 1;
        ++rnk;
    }
    int sz = 0;
    for (int i = 1; i <= n; ++i) if (!mark[i]) f[sz++] = f[i];
    while (true) {
        int id = -1, b = -1;
        for (int i = 0; i < sz; ++i) if (f[i].any()) {
            id = i;
            for (int j = 0; j < m; ++j) if (f[i].test(j)) {
                b = j;
                break;
            }
            break;
        }
        if (id == -1) break;
        swap(f[id], f[sz-1]);
        --sz;
        for (int i = 0; i < sz; ++i) if (f[i].test(b)) f[i] ^= f[sz];
        ++rnk;
    }
    int ans = 1;
    for (int i = 0; i < n - rnk; ++i) ans = 2 * ans % mod;
    ans = (ans + mod - 1) % mod;
    cout << ans << endl;
    return 0;
}