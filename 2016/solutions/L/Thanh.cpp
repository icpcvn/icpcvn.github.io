// Author: Le Yen Thanh

#include <bits/stdc++.h>
#define pb push_back
#define sqr(x) (x)*(x)
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))
#define oo 1000000007

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

ll dp[1<<20],ans[22];
int n,m,q,a[22][111111];

int main(){
//    freopen("L.in","r",stdin);
//    freopen("L2.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&q);
        for(int i=0; i<n; ++i) for(int j=1; j<=m; ++j) scanf("%d",&a[i][j]);
        ll sum=0;
        reset(dp,0);
        for(int j=1; j<=m; ++j){
            vector<pii> b;
            for(int i=0; i<n; ++i) b.pb(pii(a[i][j],i));
            sort(b.begin(),b.end(),greater<pii>());
            sum += b[0].first;
            int mask=0;
            for(int i=0; i<n-1; ++i){
                mask |= 1<<b[i].second;
                int dec = b[i].first - b[i+1].first;
                dp[mask] += dec;
            }
        }
        for(int i=1; i<=n; ++i) ans[i]=0;
        for(int i=n-1; i>=0; --i)
            for(int mask=1; mask < (1<<n); ++mask){
                if(mask>>i&1)
                    dp[mask] += dp[mask ^ (1<<i)];
                ans[n-__builtin_popcount(mask)]=max(ans[n-__builtin_popcount(mask)], dp[mask]);
            }
        for(int i=1; i<=q; ++i){
            int v;
            scanf("%d",&v);
            printf("%lld\n",sum-ans[i]);
        }
    }
}
