#include <bits/stdc++.h>

using namespace std;

int main() {
    int ntests;
    cin >> ntests;
    string fi = "Chikapu", se = "Bash";
    while (ntests --) {
        string s; cin >> s;
        int n = s.length();
        if (s[0] != s[n - 1]) {
            cout << ((n % 2 == 0) ? se : fi) << "\n";
        }
        else {
            cout << ((n % 2 == 1) ? se : fi) << "\n";
        }
    }
}
