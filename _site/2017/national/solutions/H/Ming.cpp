#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
int n;
long long a[1005];

int solve(void) {
    long long p[1005];
    for (int i = 0; i < n; ++i) p[i] = a[i];
    int ret = 0;
    int mul = 1;
    for (int i = 0; i < 60; ++i) mul = 1LL * (mod + 1) / 2 * mul % mod; //mul = 2^(-b)
    for (int b = 60; b >= 0; --b) {
        int all = 0, sum = 1, dif = 1, independent = 1;
        for (int i = 0; i < n; ++i) {
            if (p[i] >> b & 1) {
                ++all;
                sum = ((p[i] + 1) % mod * sum) % mod;
                dif = (((1LL << b + 1) - p[i] - 1) % mod * dif) % mod;
            }
            else independent = ((p[i] + 1) % mod * independent) % mod;
        }

        sum = 1LL * (mod + 1) / 2 * (sum + dif) % mod;
        if (all % 2 == 0) { //exclude K == M
            int prod = 1;
            for (int i = 0; i < n; ++i) if (p[i] >> b & 1) prod = ((p[i] + 1 - (1LL << b)) % mod * prod) % mod;
            sum = (sum + mod - prod) % mod;
        }

        ret = (ret + 1LL * mul * sum % mod * independent) % mod;
        if (all % 2 == 1) break; //K == M does not exist
        for (int i = 0; i < n; ++i) p[i] %= (1LL << b);
        mul = mul * 2 % mod;
        if (b == 0) ++ret; //A[1] = A[2] = ... = 0
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int ans = solve();
    for (int i = 0; i < n; ++i) --a[i];
    ans = (ans + 1LL * (n - 1) * solve()) % mod;
    for (int i = 0; i < n; ++i) {
        ++a[i];
        ans = (ans + mod - solve()) % mod;
        --a[i];
    }
    cout << ans << endl;
}
