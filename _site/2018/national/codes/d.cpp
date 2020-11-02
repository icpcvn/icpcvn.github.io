#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string temp;
int tc;
vector<int> v;

bool isValid(const vector<int>& k) {
    int d = k[6]*10+k[7];
    int m = k[4]*10+k[5];
    int y = k[0]*1000+k[1]*100+k[2]*10+k[3];
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 2000) return false;
    if (d > 29 && m == 2) return false;
    if (d == 31)
        if (m == 4 || m == 6 || m == 9 || m == 11) 
            return false;
    if (d == 29 && m == 2 && (y%4!=0 || (y%100==0 && y%400!=0))) 
        return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> tc;
    getline(cin,temp);
    for (int i = 0; i < tc; i++) {
        getline(cin,temp);
        v.clear();
        for (int j = 0; j < (int)temp.size(); j++) {
            if ('0' <= temp[j] && temp[j] <= '9') {
                v.push_back(temp[j]-'0');
            }
        }
        int res = 0;
        sort(v.begin(),v.end());
        vector<int> ed;
        do {
            if (isValid(v)) {
                if ((int)ed.size() == 0) { ed = v; }
                res++;
            }
        } while (next_permutation(v.begin(),v.end()));
        cout << res;
        if ((int)ed.size() != 0) {
            cout << " ";
            cout << ed[6] << ed[7] << " ";
            cout << ed[4] << ed[5] << " ";
            cout << ed[0] << ed[1] << ed[2] << ed[3] << endl;
        } else { cout << endl; }
    }
    return 0;
}