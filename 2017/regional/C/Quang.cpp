// Author: Nguyen Diep Xuan Quang
// Code submit trong ky thi.

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point;
#define fto(i, l, r) for(int i = l; i <= r; ++i)
#define fdto(i, r, l) for(int i = r; i >= l; --i)
#define ff first
#define ss second
#define X real()
#define Y imag()
#define mp make_pair
#define pb push_back
#define ll long long

const int MAX_N = 1005; 
int n; 
int a[MAX_N]; 
vector <pair <int, int> > save;

priority_queue <int, vector <int>, greater <int> > pq;  
stack <int> S; 

int main() {
    //freopen("input.txt", "r", stdin); 
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]); 
    }
    
    for (int i = n; i >= 2; i--) {
        if ((int) S.size() < a[i] - 1) {
            cout << "NO"; 
            return 0; 
        }
        
        for (int j = 1; j <= a[i] - 1; j++) {
            S.pop(); 
        }
        
        S.push(i); 
    }
    
    cout << ((int) S.size() == a[1] ? "YES" : "NO"); 
    return 0; 
}
