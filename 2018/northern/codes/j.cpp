#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7, mod = 1e9 + 7;
int n;
int a[1 << 17];
set <int> s[1 << 17];
set <int> head;
int t[1 << 17];

void up(int x, int v) {
    for (; x < (1 << 17); x += x & -x) t[x] += v;
}

int find_head(int l) {
    int x = 0, tot = 0;
    for (int k = 16; k >= 0; --k) if (tot + t[x + (1 << k)] < l) {
        tot += t[x + (1 << k)];
        x += (1 << k);
    }
    return x + 1;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], s[i].insert(a[i]), head.insert(i), up(i, 1);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l = find_head(l), r = find_head(r);
        int best = -1;
        auto it = head.find(l);
        vector <int> v;
        int mn = -inf, mx = inf;
        for (; *it != r; ++it) {
            mx = min(mx, *(--s[*it].end()));
            mn = max(mn, *(s[*it].begin()));
            v.push_back(*it);
            if (best == -1 || s[*it].size() > s[best].size()) best = *it;
        }
        mx = min(mx, *(--s[*it].end()));
        mn = max(mn, *(s[*it].begin()));
        v.push_back(*it);
        if (best == -1 || s[*it].size() > s[best].size()) best = *it;
        ++it;
        if (mx + 1 <= mn - 1) {
            auto lt = s[best].upper_bound(mx);
            auto rt = s[best].lower_bound(mn);
            s[best].erase(lt, rt);
        }
        for (auto x: v) if (x != best) {
            for (auto y: s[x]) if (y <= mx || y >= mn) s[best].insert(y);
            s[x].clear();
        }
        s[l].swap(s[best]);
        auto jt = head.find(l);
        for (++jt; jt != it; ++jt) up(*jt, -1);
        jt = head.find(l); ++jt;
        head.erase(jt, it);
    }
    long long ans = 1;
    for (auto x: head) ans = ans * s[x].size() % mod;
    cout << ans << endl;
    return 0;
}