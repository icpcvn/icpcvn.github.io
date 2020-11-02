#include <bits/stdc++.h>

using namespace std;

const int K = 14;
const int N = (1 << K) + 10;
const int MOD = 1e9 + 7;

int k, x;
int n;

long long s[N], r[K + 5];
long long psumr[K + 5];

void prepare() {
    cin >> k >> x;
    x--;
    n = 1 << k;
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 1; i <= k; i++) {
        cin >> r[i];
        psumr[i] = psumr[i - 1] + r[i];
    }
}


long long f[K + 1][N][3];

long long solve(){
    long long ans = 0;
    for(int win = 0; win <= k; win++){
        long long limit = s[x] + psumr[win];
        memset(f, 0, sizeof(f));
        for(int i = 0; i < n; i++){
            f[0][i][s[i] > limit] = 1;
        }
        for(int lv = 1; lv <= k; lv++){
            for(int L = 0; L < n; L += (1 << lv)){
                int R = L + (1 << lv);
                int mid = (L + R) / 2;
                long long sumL[3], sumR[3];
                for(int use = 0; use < 3; use++){
                    sumL[use] = 0;
                    for(int i = L; i < mid; i++){
                        sumL[use] = (sumL[use] + f[lv - 1][i][use]) % MOD;           
                    }
                }
                for(int use = 0; use < 3; use++){
                    sumR[use] = 0;
                    for(int i = mid; i < R; i++){
                        sumR[use] = (sumR[use] + f[lv - 1][i][use]) % MOD;           
                    }
                }
                for(int i = L; i < mid; i++) {
                    int take_over = (s[i] + psumr[lv - 1] <= limit) && (s[i] + psumr[lv] > limit);
                    for(int uL = 0; uL < 3; uL++) {
                        for(int uR = 0; uR < 3; uR++) {
                            int newu = uL + uR + take_over;
                            if (newu < 3) {
                                f[lv][i][newu] = (f[lv][i][newu] + f[lv - 1][i][uL] * sumR[uR]) % MOD;
                            }
                        }
                    }
                }
                for(int i = mid; i < R; i++) {
                    int take_over = (s[i] + psumr[lv - 1] <= limit) && (s[i] + psumr[lv] > limit);
                    for(int uL = 0; uL < 3; uL++) {
                        for(int uR = 0; uR < 3; uR++) {
                            int newu = uL + uR + take_over;
                            if (newu < 3) {
                                f[lv][i][newu] = (f[lv][i][newu] + f[lv - 1][i][uR] * sumL[uL]) % MOD;
                            }
                        }
                    }
                }
                if (L <= x && R > x) {
                    if (lv > win) {
                        memset(f[lv][x], 0, sizeof(f[lv][x]));
                    } else {
                        for(int i = L; i < R; i++) if (i != x){
                            memset(f[lv][i], 0, sizeof(f[lv][i]));
                        }
                    }
                }
            }
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < 2; j++)
                ans = (ans + f[k][i][j]) % MOD;
    }
    return ans;
}
int main() {
    prepare();
    cout << solve();
}
