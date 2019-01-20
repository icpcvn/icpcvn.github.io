#include <bits/stdc++.h>

using namespace std;

#define debug(a) cout << #a << ": " << a << endl
#define fto(i, l, r) for(int i = l; i <= r; ++i)

typedef pair<int, int> pii;
typedef long long ll;

const int MOD = 1000000007;

int mul(int a, int b) {return (1LL*a*b)%MOD;}

int power(int x, int n, int MOD) {
    int ans = 1;
    while (n) {
        if (n&1)
            ans = (1LL*ans*x)%MOD;
        x = (1LL*x*x)%MOD;
        n >>= 1;
    }
    return ans;
}

int inv(int x) {
    return power(x, MOD-2, MOD);
}

struct Node {
    int sum, val;
};

vector<Node> t;

void propagate(int id, int l, int r) {
    int &x = t[id].val;
    if (x != 0) {
        int m = (l+r)/2;
        t[2*id].sum = (t[2*id].sum + 1LL*(m-l+1)*x)%MOD;
        t[2*id].val = (t[2*id].val + x)%MOD;
        t[2*id+1].sum = (t[2*id+1].sum + 1LL*(r-m)*x)%MOD;
        t[2*id+1].val = (t[2*id+1].val + x)%MOD;
        x = 0;
    }
}

void update(int id, int l, int r, const int &i, const int &j, const int &x) {
    if (i > r || j < l) return;
    if (i <= l && r <= j) {
        t[id].sum = (t[id].sum + 1LL*(r-l+1)*x)%MOD;
        t[id].val = (t[id].val + x)%MOD;
        return;
    }

    propagate(id, l, r);

    int m = (l+r)/2;
    update(2*id, l, m, i, j, x);
    update(2*id+1, m+1, r, i, j, x);
    t[id].sum = (t[2*id].sum + t[2*id+1].sum)%MOD;
}

int query(int id, int l, int r, const int &i, const int &j) {
    if (i > r || j < l) return 0;
    if (i <= l && r <= j)
        return t[id].sum;

    propagate(id, l, r);

    int m = (l+r)/2;
    return (query(2*id, l, m, i, j) + query(2*id+1, m+1, r, i, j))%MOD;
}

int n, q;

int main() {
    scanf("%d%d", &n, &q);

    t.assign(4*n+1, {0, 0});

    int ans = 0;
    fto(i, 1, q) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int l, r;
            scanf("%d%d", &l, &r);

            int x = inv(r-l+1);
            ans = (ans + 1)%MOD;
            ans = (ans + 2LL*x*query(1, 1, n, l, r))%MOD;
            update(1, 1, n, l, r, x);
        } else {
            printf("%d\n", ans);
        }
    }

    return 0;
}

