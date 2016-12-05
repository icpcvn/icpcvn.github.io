// Author: RR
// O(N^2 + Q)

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <stack>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define endl "\n"
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

namespace Util {
    bool is_alpha(char c) {
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        return false;
    }
    bool is_valid_name(string s) {
        for (char c : s)
            if (!is_alpha(c)) return false;
        return true;
    }
};

enum Keyword {
    MKDIR,
    RM,
    SZ,
    CD,
    LS,
    TREE,
    UNDO
};

struct Command {
    Keyword keyword;
    string arg;

    void read() {
        string s;
        cin >> s;
        if (s == "MKDIR") {
            keyword = Keyword :: MKDIR;
            cin >> arg;
            assert(Util::is_valid_name(arg));
        }
        else if (s == "RM") {
            keyword = Keyword :: RM;
            cin >> arg;
            assert(Util::is_valid_name(arg));
        }
        else if (s == "CD") {
            keyword = Keyword :: CD;
            cin >> arg;
            assert(arg == ".." || Util::is_valid_name(arg));
        }
        else if (s == "SZ") {
            keyword = Keyword :: SZ;
        }
        else if (s == "LS") {
            keyword = Keyword :: LS;
        }
        else if (s == "TREE") {
            keyword = Keyword :: TREE;
        }
        else {
            assert(s == "UNDO");
            keyword = Keyword :: UNDO;
        }
    }
};

struct Dir {
    int sz;
    string name;
    map<string,Dir*> children;
    Dir* parent;
    Dir* last_child; // last child in DFS order. used for TREE command.
} *sentinel, *root;

void init_dir() {
    sentinel = new Dir();
    sentinel->sz = 0;
    sentinel->parent = sentinel;
    sentinel->children.clear();
    sentinel->name = "sentinel";
    sentinel->last_child = sentinel;

    root = new Dir();
    root->sz = 1;
    root->parent = sentinel;
    root->children.clear();
    root->name = "root";
    root->last_child = root;
}

void update_ancestors(Dir* cur, int update) {
    // update size of all ancestors
    while (cur != sentinel) {
        cur->sz += update;
        if (!cur->children.empty()) {
            auto it = cur->children.end(); --it;
            cur->last_child = it->second->last_child;
        }
        else {
            // no children
            cur->last_child = cur;
        }
        cur = cur->parent;
    }
}

Dir* create_dir(string name, Dir* parent) {
    Dir* res = new Dir();
    res->sz = 0;
    res->parent = parent;
    res->children.clear();
    res->name = name;
    res->last_child = res;

    assert(parent != sentinel);

    parent->children[name] = res;

    update_ancestors(res, +1);
    return res;
}

void ERR() {
    cout << "ERR" << endl;
}

void OK() {
    cout << "OK" << endl;
}

void print_vector(const vector<string>& out) {
    if (out.empty()) cout << "EMPTY" << endl;
    else if (SZ(out) <= 10) {
        for(auto s : out) cout << s << endl;
    }
    else {
        REP(i,5) cout << out[i] << endl;
        cout << "..." << endl;
        FOR(i,SZ(out)-5,SZ(out)-1) cout << out[i] << endl;
    }
}

vector<string> out;
void dfs(Dir* cur) {
    out.push_back(cur->name);
    for (auto p : cur->children) {
        dfs(p.second);
    }
}

struct PreviousState {
    Dir* cd_trace;
    Dir* removed;
    string added;
};

void dfs_xuoi(Dir* cur) {
    out.push_back(cur->name);
    if (SZ(out) == 5) throw 1;

    for (auto p : cur->children) {
        dfs_xuoi(p.second);
    }
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        init_dir();
        Dir* cur = root;

        int q; cin >> q;

        stack<Command> history;
        stack<PreviousState> backup;

        while (q--) {
            Command command; command.read();
            if (command.keyword == Keyword :: MKDIR) {
                // check if dir with same name exists
                if (cur->children.count(command.arg)) {
                    ERR();
                    continue;
                }

                OK();
                auto p = create_dir(command.arg, cur);

                history.push(command);

                PreviousState state;
                state.added = command.arg;
                backup.push(state);
            }
            else if (command.keyword == Keyword :: RM) {
                // check if dir contains child directory
                if (!cur->children.count(command.arg)) {
                    ERR();
                    continue;
                }

                OK();
                auto removed_dir = cur->children[command.arg];
                int removed_sz = removed_dir->sz;

                history.push(command);
                PreviousState state;
                state.removed = removed_dir;
                backup.push(state);

                cur->children.erase(command.arg);
                update_ancestors(cur, -removed_sz);
            }
            else if (command.keyword == Keyword :: CD) {
                if (command.arg == "..") {
                    // Move up
                    if (cur->parent == sentinel) {
                        ERR();
                        continue;
                    }
                    OK();

                    history.push(command);
                    PreviousState state;
                    state.cd_trace = cur;
                    backup.push(state);

                    cur = cur->parent;
                }
                else {
                    if (!cur->children.count(command.arg)) {
                        ERR();
                        continue;
                    }
                    OK();

                    history.push(command);
                    PreviousState state;
                    state.cd_trace = cur;
                    backup.push(state);

                    cur = cur->children[command.arg];
                }
            }
            else if (command.keyword == Keyword :: SZ) {
                cout << cur->sz << endl;
            }
            else if (command.keyword == Keyword :: LS) {
                if (cur->children.size() <= 10) {
                    out.clear();
                    for(auto p : cur->children) {
                        out.push_back(p.second->name);
                    }
                    print_vector(out);
                }
                else {
                    out.clear();
                    for(auto p : cur->children) {
                        out.push_back(p.second->name);
                        if (SZ(out) == 5) break;
                    }
                    print_vector(out);
                    cout << "..." << endl;

                    out.clear();
                    auto p = cur->children.end();
                    while (true) {
                        --p;
                        out.push_back(p->second->name);
                        if (SZ(out) == 5) break;
                    }
                    reverse(out.begin(), out.end());
                    print_vector(out);
                }
            }
            else if (command.keyword == Keyword :: TREE) {
                if (cur->sz == 1) {
                    cout << "EMPTY" << endl;
                    continue;
                }
                if (cur->sz <= 10) {
                    out.clear();
                    dfs(cur);
                    print_vector(out);
                }
                else {
                    out.clear();
                    try {
                        dfs_xuoi(cur);
                    } catch (...) {
                    }
                    print_vector(out);
                    cout << "..." << endl;

                    set<Dir*> printed;

                    auto p = cur->last_child;
                    out.clear();
                    while (SZ(out) < 5) {
                        // when we print a node, we assume that all its descendants are already printed.
                        out.push_back(p->name);
                        printed.insert(p);

                        // since all descendants and current node is printed, we must go up.
                        p = p->parent;

                        // now we can go down again. Find first child that is not printed.
                        auto it = p->children.end();

                        bool ok = false;
                        while (it != p->children.begin()) {
                            --it;
                            if (!printed.count(it->second)) {
                                ok = true;
                                break;
                            }
                        }

                        // if some child is not printed, go to its deepest child.
                        if (ok) {
                            p = it->second->last_child;
                        }
                    }
                    reverse(out.begin(), out.end());
                    print_vector(out);
                }
            }
            else {
                assert(command.keyword == Keyword :: UNDO);

                if (history.empty()) {
                    ERR();
                    continue;
                }
                OK();

                auto last = history.top(); history.pop();
                auto state = backup.top(); backup.pop();

                if (last.keyword == Keyword :: MKDIR) {
                    cur->children.erase(last.arg);
                    update_ancestors(cur, -1);
                }
                else if (last.keyword == Keyword :: RM) {
                    cur->children[last.arg] = state.removed;
                    update_ancestors(cur, +state.removed->sz);
                }
                else {
                    assert(last.keyword == Keyword :: CD);
                    cur = state.cd_trace;
                }
            }
        }

        cout << endl;
    }
}
