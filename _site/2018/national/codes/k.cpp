#include <bits/stdc++.h> 

using namespace std; 

const int MAX_N = 2503; 
const int MOD = 1000000782;
const int MAX_Q = 100005; 

struct element {
    int x1, y1, x2, y2; 
};

int fw[MAX_N][MAX_N]; 
int power[MAX_Q]; 
int query; 
element a[MAX_Q]; 

void add(int &a, int b) {
    (a += b) %= MOD; 
}

void update(int x, int y, int val) {
    for (int i = x; i < MAX_N; i += (i & -i)) {
        for (int j = y; j < MAX_N; j += (j & -j)) {
            add(fw[i][j], val); 
        }
    }
}

void update(int x1, int y1, int x2, int y2, int val) {
    update(x1, y1, val);
    update(x1, y2 + 1, MOD - val);
    update(x2 + 1, y1, MOD - val);
    update(x2 + 1, y2 + 1, val);    
}

int get(int x, int y) {
    int sum = 0; 
    for (int i = x; i > 0; i -= (i & -i)) {
        for (int j = y; j > 0; j -= (j & -j)) {
            add(sum, fw[i][j]);
        }
    }

    return sum; 
}

int main() {
    //freopen("input.txt", "r", stdin); 
    //freopen("output.txt", "w", stdout);

    power[0] = 1; 

  int BASE = 102240;                            

    scanf("%d", &query); 
    for (int i = 1; i <= query; i++) {
        power[i] = 1LL * power[i - 1] * BASE % MOD; 
    }

    for (int i = 1; i <= query; i++) {
        int type; 
        scanf("%d", &type); 
        if (type == 1) {
            scanf("%d %d %d %d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2); 
            a[i].x1 = (a[i].x1 + 1) / 2; 
            a[i].y1 = (a[i].y1 + 1) / 2; 
            a[i].x2 = (a[i].x2 - 1) / 2; 
            a[i].y2 = (a[i].y2 - 1) / 2; 
            int x = power[i];
            update(a[i].x1, a[i].y1, a[i].x2, a[i].y2, x);
        }
        else if (type == 2) {
            int p; 
            scanf("%d", &p); 
            int x = MOD - power[p]; 
            update(a[p].x1, a[p].y1, a[p].x2, a[p].y2, x); 
        }
        else {
            int x1, y1, x2, y2; 
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2); 
            x1 /= 2;
            x2 /= 2;
            y1 /= 2; 
            y2 /= 2;
            int K2 = get(x2, y2); 
            int K1 = get(x1, y1); 

            cout << (K1 == K2 ? 'Y' : 'N');
        }
    }
    return 0; 
}