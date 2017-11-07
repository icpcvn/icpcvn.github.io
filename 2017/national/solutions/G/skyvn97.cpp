// Author: Pham Van Hanh
// Disjoint set + BFS

#include<bits/stdc++.h>
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
template<class T>
    T Abs(const T &x) {
        return (x<0?-x:x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

class DisjointSet {
	private:
	vector<int> label; //label[x] stores the root of x if x is not root, otherwise it stores -(size of x's set).
	public:
	DisjointSet(){}
	DisjointSet(int n) {
		label.assign(n+7,-1); //label should contains at least n+1 elements, as x is 1-indexed.
		//At first, each node is a seperate set of size 1.
	}
	int find(int x) { //find the root of set which contains x.
		if (label[x]<0) return (x); //x is root iff label[x] is negative.
		label[x]=find(label[x]);
		return (label[x]); //find the root of x by recursion.
	}
	bool join(int a,int b) { // join the sets which contains a and b. Return false iff a and b are already in the same set.
		int x=find(a);
		int y=find(b);
		if (x==y) return (false); //A set contains both a and b.
		if (label[x]>label[y]) swap(x,y); //label[x]>label[y] means size(x)<size(y).
		//We speed up the disjoint set by joinning the smaller set to the bigger set
		label[x]+=label[y];
		label[y]=x; //Update the label of x and y.
		return (true);
	}
	int getSize(int x) { //return the size of set which contains x.
		return (-label[find(x)]);
	}
};


struct Edge {
    int u, v, c;

    Edge() {
        u = v = c = 0;
    }

    void input(void) {
        scanf("%d%d%d", &u, &v, &c);
    }

    int other(int x) const {
        assert(u == x || v == x);
        return u ^ v ^ x;
    }

    bool operator < (const Edge &e) const {
        return c < e.c;
    }
};

#define MAX   200200
const string NO_ANSWER = "Poor girl";

Edge edges[MAX];
vector<int> adj[MAX];
int dist[MAX];
int n, m, alpha;

void loadGraph(void) {
    scanf("%d%d%d", &n, &m, &alpha);
    FOR(i, 1, m) edges[i].input();
    sort(edges + 1, edges + m + 1);
    FOR(i, 1, m) {
        adj[edges[i].u].push_back(i);
        adj[edges[i].v].push_back(i);
    }
}

int findEdge(void) {
    DisjointSet dsu(n);
    FOR(i, 1, m) if (!dsu.join(edges[i].u, edges[i].v)) return i;
    return -1;
}

int bfs(int block) {
    int s = edges[block].u;
    int t = edges[block].v;

    memset(dist, -1, sizeof dist);
    queue<int> q;
    dist[s] = 0; q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        FORE(it, adj[u]) if (*it != block && edges[*it].c < edges[block].c) {
            int v = edges[*it].other(u);
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    assert(dist[t] >= 0);
    return dist[t];
}

void process(void) {
    int id = findEdge();
    if (id < 0) {
        cout << NO_ANSWER << endl;
        return;
    }

    int tmp = bfs(id);
    cout << 1LL * edges[id].c * edges[id].c + alpha * (tmp + 1) << endl;
}

int main(void) {
    loadGraph();
    process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/

