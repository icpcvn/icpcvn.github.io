// Author: RR
// O(N^2 + Q)

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
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

const string EMPTY = "EMPTY";
const string ERR = "ERR";
const string OK = "OK";
const string DOT = "...";
#define endl "\n"

void printAtMost10(const vector<string>& ls) {
    if (SZ(ls) <= 10) {
        for(auto s : ls) cout << s << endl;
    }
    else {
        REP(i,5) cout << ls[i] << endl;
        cout << DOT << endl;
        FOR(i,SZ(ls)-5,SZ(ls)-1) cout << ls[i] << endl;
    }
}

struct Node {
    string name;
    Node* parent;
    map<string, Node*> children;

    bool hasChild(string name) {
        return children.count(name);
    }

    void printSz() {
        if (!cached_sz) calculateSz();
        cout << sz << endl;
    }

    void printLs() {
        if (children.empty()) {
            cout << EMPTY << endl;
            return ;
        }

        if (!cached_ls) calculateLs();
        printAtMost10(ls);
    }

    void printTree() {
        if (children.empty()) {
            cout << EMPTY << endl;
            return ;
        }

        if (!cached_tree) calculateTree();
        printAtMost10(tree);
    }

    int calculateSz() {
        sz = 1;
        for(auto p : children)
            sz += p.second->calculateSz();
        cached_sz = 1;
        return sz;
    }

    void calculateLs() {
        cached_ls = 1;
        ls.clear();
        for(auto p : children)
            ls.push_back(p.first);
    }

    void calculateTree() {
        cached_tree = 1;
        tree.clear();
        dfs(tree);
    }

    void dfs(vector<string> &all) {
        all.push_back(name);
        for(auto p : children)
            p.second->dfs(all);
    }

    void invalidateCache() {
        cached_sz = 0;
        cached_ls = 0;
        cached_tree = 0;
    }


    // ------ INTERNAL CACHE -------
    bool cached_sz;
    int sz;

    bool cached_ls;
    vector<string> ls;

    bool cached_tree;
    vector<string> tree;
};

const int MKDIR = 1;
const int RM = 2;
const int CD = 3;
const int SZ = 4;
const int LS = 5;
const int TREE = 6;
const int UNDO = 7;

struct Command {
    int id;
    string arg;

    void read() {
        string s; cin >> s;
        if (s == "MKDIR") id = MKDIR;
        if (s == "RM") id = RM;
        if (s == "CD") id = CD;
        if (s == "SZ") id = SZ;
        if (s == "LS") id = LS;
        if (s == "TREE") id = TREE;
        if (s == "UNDO") id = UNDO;
        
        if (id == MKDIR || id == RM || id == CD) {
            cin >> arg;
        }
    }
};

Node* createNode(string name, Node* parent) {
    Node* res = new Node();
    res->cached_sz = res->cached_ls = res->cached_tree = 0;
    res->name = name;
    res->parent = parent;
    res->children.clear();

    if (parent) {
        parent->children[name] = res;
    }
    return res;
}

void invalidateAncestors(Node* cur) {
    while (cur) {
        cur->invalidateCache();
        cur = cur->parent;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        int q; cin >> q;
        stack<Command> history;
        stack<Node*> backup;

        Node* root = createNode("root", NULL);
        Node* cur = root;

        while (q--) {
            Command c; c.read();
            if (c.id == MKDIR) {
                if (cur->hasChild(c.arg)) cout << ERR << endl;
                else {
                    cout << OK << endl;
                    createNode(c.arg, cur);

                    history.push(c);
                    backup.push(NULL);

                    invalidateAncestors(cur);
                }
            }
            else if (c.id == RM) {
                if (!cur->hasChild(c.arg)) cout << ERR << endl;
                else {
                    cout << OK << endl;

                    history.push(c);
                    backup.push(cur->children[c.arg]);

                    cur->children.erase(c.arg);

                    invalidateAncestors(cur);
                }
            }
            else if (c.id == CD) {
                Node* next = NULL;
                if (c.arg == "..") next = cur->parent;
                else if (cur->hasChild(c.arg)) next = cur->children[c.arg];

                if (!next) cout << ERR << endl;
                else {
                    cout << OK << endl;

                    history.push(c);
                    backup.push(cur);

                    cur = next;
                }
            }
            else if (c.id == SZ) {
                cur->printSz();
            }
            else if (c.id == LS) {
                cur->printLs();
            }
            else if (c.id == TREE) {
                cur->printTree();
            }
            else {
                assert(c.id == UNDO);
                if (history.empty()) {
                    cout << ERR << endl;
                }
                else {
                    cout << OK << endl;

                    auto c = history.top(); history.pop();
                    auto d = backup.top(); backup.pop();

                    if (c.id == MKDIR) {
                        cur->children.erase(c.arg);
                        invalidateAncestors(cur);
                    }
                    else if (c.id == RM) {
                        cur->children[c.arg] = d;
                        invalidateAncestors(cur);
                    }
                    else {
                        assert(c.id == CD);
                        cur = d;
                    }
                }
            }
        }
        cout << endl;
    }
}

