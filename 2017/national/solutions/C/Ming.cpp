#include <bits/stdc++.h>

using namespace std;

const int Mod = 1e9 + 7;

long long mod(long long x) { return x % Mod; }

long long pw10[20];

int sod(long long x) {
    int ret = 0;
    while (x) ret += x % 10, x /= 10;
    return ret;
}

struct data {
    long long apos, anum, aans;
    data() {}
    data(long long a, long long b, long long c) { apos = a, anum = b, aans = c; }
};

void update(long long &cur_pos, long long &cur_num, long long &cur_ans, data d) {
    cur_pos += d.apos;
    cur_num = d.anum;
    cur_ans = (cur_ans + d.aans) % Mod;
}

map <long long, data> memo[20][1005];
void jump(long long &cur_pos, long long &cur_num, long long &cur_ans, int target, int add) {
    map <long long, data> :: iterator it = memo[target][add].find(cur_num);
    if (it != memo[target][add].end()) {
        update(cur_pos, cur_num, cur_ans, it->second);
        return;
    }
    if (target == 0) {
        data d = data(1, cur_num + sod(cur_num) + add, cur_num + sod(cur_num) + add);
        memo[target][add][cur_num] = d;
        update(cur_pos, cur_num, cur_ans, d);
        return;
    }

    long long q = cur_num / pw10[target];
    int new_add = add + sod(q);
    long long jump_pos = 0, jump_num = cur_num % pw10[target], jump_ans = 0;
    while (jump_num < pw10[target]) jump(jump_pos, jump_num, jump_ans, target - 1, new_add);

    data d = data(jump_pos, q * pw10[target] + jump_num, (jump_ans + mod(q) * mod(pw10[target]) % Mod * mod(jump_pos)) % Mod);
    memo[target][add][cur_num] = d;
    update(cur_pos, cur_num, cur_ans, d);
}

int main(void) {
    pw10[0] = 1;
    for (int i = 1; i <= 16; ++i) pw10[i] = pw10[i-1] * 10;
    int T; cin >> T;
    while (T--) {
        long long cur_pos = 1, cur_num = 1, cur_ans = 1;
        long long target_pos;
        cin >> target_pos;
        for (int i = 16; i >= 0; --i) {
            while (true) {
                long long old_pos = cur_pos, old_num = cur_num, old_ans = cur_ans;
                jump(cur_pos, cur_num, cur_ans, i, 0);
                if (cur_pos > target_pos) {
                    cur_pos = old_pos;
                    cur_num = old_num;
                    cur_ans = old_ans;
                    break;
                }
            }
        }
        cout << cur_ans << endl;
    }
}
