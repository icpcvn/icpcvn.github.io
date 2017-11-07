// Author: PTIT
// Segment tree O(Q*logN)

#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FO(i,a,b) for(int i=a;i<b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define FOD(i,a,b) for(int i=a;i>b;i--)
#define fi first
#define se second
#define pb push_back
#define mp make_pair


using namespace std;

typedef pair<int,int>II;

const long double PI = 2*acos(0.0);
const long double eps = 1e-15;
const int infi = 1e9;
const LL Linfi = (LL) 1e18;
const LL MOD = 1000000007;
#define maxn 200005

int n, m;
struct node{
    LL sum, lazy[4];
};

LL sum[4][maxn];
node tree[maxn*4];

LL find_val(int k, LL x){
    if(k == 0) return (-1LL*x*x*x + 6*x*x - 11*x + 6) % MOD;
    if(k == 1) return (3*x*x - 12*x + 11) % MOD;
    if(k == 2) return -3*x + 6;
    return 1;
}

void add(LL &a, LL b){
    a = (a+b) % MOD;
    if(a < 0) a += MOD;
}

void down(int i, int l, int r){
    int mid = (l+r)/2, c1 = i*2, c2 = i*2+1;
    FOR(k,0,3){
        add(tree[c1].lazy[k], tree[i].lazy[k]);
        add(tree[c2].lazy[k], tree[i].lazy[k]);

        add(tree[c1].sum, tree[i].lazy[k]*(sum[k][mid] - sum[k][l-1] + MOD));
        add(tree[c2].sum, tree[i].lazy[k]*(sum[k][r] - sum[k][mid] + MOD));
        tree[i].lazy[k] = 0;
    }
}

void update(int i, int l, int r, int u, int v, int flag){
    if(l > v || r < u) return;
    if(u <= l && r <= v){
        FOR(k,0,3){
            LL val = find_val(k, u) * flag;
            add(tree[i].sum, val*(sum[k][r] - sum[k][l-1] + MOD));
            add(tree[i].lazy[k], val);
        }
        return;
    }
    int mid = (l+r)/2;
    down(i, l, r);
    update(i*2, l, mid, u, v, flag);
    update(i*2+1, mid+1, r, u, v, flag);
    tree[i].sum = (tree[i*2].sum + tree[i*2+1].sum) % MOD;
}

LL get(int i, int l, int r, int u, int v){
    if (l > v || r < u) return 0;
    if (u <= l && r <= v) return tree[i].sum;
    int mid = (l + r) / 2;
    down(i, l, r);
    return (get(i*2, l, mid, u, v) + get(i*2+1, mid+1, r, u, v)) % MOD;
}

void solve(){
    int cmd, u, v;
    while(m--){
        cin >> cmd >> u >> v;
        if(cmd == 1){
            update(1, 1, n, u, v, 1);
        }
        else if(cmd == 2){
            update(1, 1, n, u, v, -1);
        }
        else if(cmd == 0){
            LL ans = get(1, 1, n, u, v);
            cout << ans << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    #endif
    cin >> n >> m;
    FOR(i,1,n) {
        sum[0][i] = sum[0][i-1] + 1;
        sum[1][i] = (sum[1][i-1] + i) % MOD;
        sum[2][i] = (sum[2][i-1] + 1LL*i*i) % MOD;
        sum[3][i] = (sum[3][i-1] + 1LL*i*i*i) % MOD;
    }

    solve();

    return 0;
}

