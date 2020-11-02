/*input
2
*/
#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define fi first
#define se second
#define mp make_pair
#define __builtin_popcount __builtin_popcountll
#define int long long
#define bit(x,y) ((x>>y)&1LL)
#define loop(i,l,r) for(int i=(int)l; i<=(int)r; i++)
#define rloop(i,l,r) for(int i=(int)l; i>=(int)r; i--)
//const int N=;
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &a) {
    return os << '(' << a.first << ", " << a.second << ')';
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &a) {
    os << '[';
    for (unsigned int i = 0; i < a.size(); i++)
        os << a[i] << (i < a.size() - 1 ? ", " : "");
    os << ']';
    return os;
}

#define rand rd
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int mod = 1e9; int half = mod / 2;
int n;

struct Grader {
    vector<int> point; int cntAsk = 0;
    void init() {
        loop(i, 1, n) {
            point.push_back(rd() % mod);
        }
    }
    int ask(int l, int r) {
        assert(0 <= l && l < mod); assert(0 <= r && r < mod); cntAsk++; assert(cntAsk <= 30);
        int ret = 0;
        if (l <= r) {
            for (auto it : point) if (l <= it && it <= r) ret++;
        }
        else {
            for (auto it : point) if (l <= it || it <= r) ret++;
        }
        return ret;
    }
    void yes(int x) {
        cntAsk++;
        assert(cntAsk <= 30);
        int ret = 0;
        int l = x; int r = (x + half - 1) % mod;
        if (l <= r) {
            for (auto it : point) if (l <= it && it <= r) ret++;
        }
        else {
            for (auto it : point) if (l <= it || it <= r) ret++;
        }
        assert(ret == n / 2);
        cout << x << endl;
    }
} gra;

int ask(int l, int r) {
    int rec;
#ifdef UncleGrandpa
    rec = gra.ask(l, r);
#else
    cout << "QUERY" << sp << l << sp << r << endl;
    cin >> rec;
#endif
    return rec;
}

void yes(int l) {
#ifdef UncleGrandpa
    gra.yes(l);
#else
    cout << "YES" << sp << l << endl;
#endif
    exit(0);
}

void solve(int l, int r) {
    int mid;
    if (r <= l)
        yes(l);
    if (l <= r) mid = (l + r) / 2;
    else mid = (l + r + mod) / 2;
    mid %= mod;
    int rec = ask(mid, (mid + half - 1) % mod);
    if (rec == n / 2) yes(mid);
    else if (rec < n / 2) solve(mid + 1, r);
    else solve(l, mid - 1);
}

signed main() {
#ifndef UncleGrandpa
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#endif
    cin >> n;
#ifdef UncleGrandpa
    gra.init();
#endif
    solve(0, mod - 1);
}