#include <bits/stdc++.h>

using namespace std;


struct BIT{
    vector<int> b;
    void build(int n){
        b.resize(n + 1, 0);
    }
    void add(int x, int val){
        assert(x > 0);
        while (x < b.size()){
            b[x] += val;
            x+= x & -x;
        }
        
    }
    int get(int x){
        x = min(x, int(b.size()) - 1);
        if (x < 0) return 0;
        int ans = 0;
        while (x){
            ans += b[x];
            x-= x&-x;
        }
        return ans;
    }
    int getpoint(int x){
        if (x == 0) return 0;
        return get(x) - get(x - 1);
    }
};
struct node{
    node* link[26];
    BIT b;
    int sub;
    node(){
        sub = 0;
        for(int i = 0; i < 26; i++) link[i] = NULL;
    }
   
};
node* root;
const int N = 3e5 + 10;
int n;
string s[N];

void prepare(){
    root = new node();
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = 1; i <= n; i++){
        node * cur = root;
        cur->sub++;
        for(auto ch : s[i]) {
            int dir = ch - 'a';
            if (cur->link[dir] == NULL){
                cur->link[dir] = new node();
            }
            cur = cur->link[dir];
            cur->sub++;
        }
    }
    queue<node*> q;
    q.push(root);
    while (!q.empty()){
        node* cur = q.front();
        q.pop();
        cur->b.build(cur->sub);
        cur->sub = 0;
        for(int i = 0; i < 26; i++) if (cur->link[i] != NULL)
            q.push(cur->link[i]);
    }
}
long long solve() {
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        node* cur = root;
        vector<node*> a;
        a.push_back(cur);
        for(auto ch : s[i]) {
            int dir = ch - 'a';
            cur = cur -> link[dir];
            a.push_back(cur);
        }
        int n1 = s[i].length();
        int appear = a[n1]->sub;
        a[n1]->sub++;
        if (appear == 0) {
            ans += n1;
        }else{
            int cans = n1;
            int same = 0;
            for(int j = s[i].length() - 1; j >= 1; j--){
                for(int u1 = 0; u1 < s[i][j] - 'a'; u1++){
                    if (a[j]->link[u1] != NULL){
                        same += a[j]->link[u1]->b.getpoint(appear);
                    }
                }
                if (a[j]->sub != 0){
                    same += (a[j] -> sub) == appear;
                }
                int cost =  j + (a[j]->b.get(n) - a[j]->b.get(appear)) + same + 1;
                cans = min(cans, cost);
            }
            ans += cans;
        }
        for(int j = 0; j <= n1; j++) {
            a[j]->b.add(appear + 1, 1);
            if (appear != 0)
                a[j]->b.add(appear, -1);
        }
    }
    return ans;
}
int main() {
    prepare();
    cout << solve();
}
