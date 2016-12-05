// Author: Le Don Khue
// DP O(N^3)

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int f[311][111][111];
int p[311];

int main() {
    int test;
    cin >> test;

    while (test--) {
        int n;
        cin >> n;
        for (int i = 1; i <= 3 * n; i++) {
            cin >> p[i];
        }
        sort(p + 1, p + 3 * n + 1);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= 3 * n; i++) {
            for (int c3 = 0; c3 <= n; c3++)
                for (int c2 = 0; c2 <= c3; c2++) {
                    int c1 = i - c3 - c2;
                    if (c2 >= c1 && c1 >= 0) {

                        bool p1 = (c3 >= c2 && c2 >= c1 - 1 && c1 - 1 >= 0);
                        bool p2 = (c3 >= c2 - 1 && c2 - 1 >= c1);
                        bool p3 = (c3 - 1 >= c2 && c2 >= c1);

                        f[i][c3][c2] = 0;
                        if (p1) f[i][c3][c2] = max(f[i][c3][c2], f[i - 1][c3][c2]);
                        if (p2) f[i][c3][c2] = max(f[i][c3][c2], f[i - 1][c3][c2 - 1] + p[i]);
                        if (p3) f[i][c3][c2] = max(f[i][c3][c2], f[i - 1][c3 - 1][c2]);
                    }
                }
        }
        cout << f[3 * n][n][n] << endl;
    }

    return 0;
}
