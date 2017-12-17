// Author: Nguyen Diep Xuan Quang
// Code submit trong contest

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point;
#define debug(a) cout << #a << ": " << a << endl
#define fto(i, l, r) for(int i = l; i <= r; ++i)
#define fdto(i, r, l) for(int i = r; i >= l; --i)
#define ff first
#define ss second
#define X real()
#define Y imag()
#define mp make_pair
#define pb push_back
#define ll long long
#define maxN 1000005

int p[maxN];

int Fib(int n, int MOD) {
    int a = 1%MOD, b = 1%MOD, c;
    fto(i, 1, n) {
        c = (a+b)%MOD;
        a = b;
        b = c;
    }
    return c;
}

void upd(vector<int> &cnt, int n, int sign) {
    while (n > 1) {
        cnt[p[n]] += sign;
        n /= p[n];
    }
}

int C(int n, int k, int MOD) {
    vector<int> p(n+1, 0);
    fto(i, k+1, n) upd(p, i, 1);    
    fto(i, 1, n-k) upd(p, i, -1);
    
//  fto(i, 1, n) printf("%d ", p[i]);
//  puts("");
    
    int res = 1%MOD;
    fto(i, 1, n) {
        fto(x, 1, p[i]) res = (1LL*res*i)%MOD;
    }
    return res;
}

int main() {
    p[1] = 1;
    for(int i = 2; i < maxN; ++i) {
        for(int j = i; j < maxN; j += i) {
            if (!p[j]) p[j] = i;
        }       
    }
    
    int nTest; scanf("%d", &nTest);
    
    fto(i, 1, nTest) {
        int n, MOD; scanf("%d%d", &n, &MOD);
        
        int ans = Fib(n, MOD);
//      debug(C(n, n/2, MOD));
        if (n%2 == 0) ans = (ans+C(n, n/2, MOD)-((n/2+1)%MOD)+MOD)%MOD;
        
        printf("%d\n", ans);
    }

    return 0; 
}
