// Author: Nguyen Dinh Quang Minh

#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int R, W, d;
int ft[2000006], rv[2000006];

int pw(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) r = 1ll * r * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return r;
}
int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return 1ll * ft[n] * rv[k] % mod * rv[n-k] % mod;
}

int main(void) {
    cin >> R >> W >> d; ++W; ++d;
    int n = R + W;
    ft[0] = 1;
    for (int i = 1; i <= n; ++i) ft[i] = 1ll * ft[i-1] * i % mod;
    rv[n] = pw(ft[n], mod - 2);
    for (int i = n; i >= 1; --i) rv[i-1] = 1ll * rv[i] * i % mod;
    int ans = 0;
    for (int i = 0, m = W + R - 1; i <= W && m >= 0; ++i, m -= d) {
        int add = 1ll * comb(W, i) * comb(m, W - 1) % mod;
        if (i & 1) ans = (ans + mod - add) % mod;
        else ans = (ans + add) % mod;
    }
    cout << ans << endl;
}
