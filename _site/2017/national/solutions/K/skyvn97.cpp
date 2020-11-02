// Author: Pham Van Hanh

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

#define SQR(x) (1LL * (x) * (x))

struct Point {
    int x, y;

    Point(int _x = 0, int _y = 0) {
        x = _x; y = _y;
    }

    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }

    long long operator % (const Point &a) const {
        return 1LL * x * a.y - 1LL * a.x * y;
    }

    long long cross(const Point &a, const Point &b) const {
        return (a - *this) % (b - *this);
    }

    long long modul(void) const {
        return SQR(x) + SQR(y);
    }

    Point compress(void) const {
        int t = __gcd(Abs(x), Abs(y));
        return Point(x / t, y / t);
    }

    bool operator < (const Point &a) const {
        return y == a.y ? x < a.x : y < a.y;
    }

    bool operator == (const Point &a) const {
        return x == a.x && y == a.y;
    }
};
istream& operator >> (istream &is, Point &p) {
    return is >> p.x >> p.y;
}
ostream& operator << (ostream &os, const Point &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

Point center;

bool compareCCW(const Point &a, const Point &b) {
    long long tmp = center.cross(a, b);
    if (tmp != 0) return tmp > 0;
    return (a - center).modul() < (b - center).modul();
}

vector<Point> convexHull(vector<Point> points) {
    sort(ALL(points));
    center = points[0];
    sort(points.begin() + 1, points.end(), compareCCW);

    vector<Point> cv;
    FORE(it, points) {
        while (cv.size() >= 2 && cv[cv.size() - 2].cross(cv.back(), *it) <= 0) cv.pop_back();
        cv.push_back(*it);
    }

    return cv;
}

bool onSegment(const Point &a, const Point &b, const Point &c) {
    return (b - a).compress() == (c - a).compress() && (a - b).compress() == (c - b).compress();
}

bool insideConvexHull(const vector<Point> &cv, const Point &p) {
    vector<Point> points = cv;
    points.push_back(p);
    points = convexHull(points);
    return find(ALL(points), p) == points.end();
}

int countInside(const vector<Point> &cv, const vector<Point> &points) {
    int res = 0;
    FORE(it, points) if (insideConvexHull(cv, *it)) res++;
    return res;
}

#define MAX   1111

vector<Point> readInput(void) {
    vector<Point> res;
    int n; cin >> n;
    REP(love, n) {
        res.push_back(Point());
        cin >> res.back();
    }

    return res;
}

long long process(void) {
    vector<Point> boys = readInput();
    vector<Point> girls = readInput();

    vector<Point> cv = convexHull(boys);

    if (cv.size() < 3) return 0;
    if (cv.size() > 3) return countInside(cv, girls);

    Point A = cv[0], B = cv[1], C = cv[2];
    bool ab = false, bc = false, ca = false, inside = false;

    FORE(it, boys) {
        if (*it == A || *it == B || *it == C) continue;
        else if (onSegment(A, B, *it)) ab = true;
        else if (onSegment(B, C, *it)) bc = true;
        else if (onSegment(C, A, *it)) ca = true;
        else inside = true;
    }

    if (inside) return countInside(cv, girls);
    assert(ab || bc || ca);
    if (ab && bc && ca) return countInside(cv, girls);
    if (ca && ab) {
        boys.erase(find(ALL(boys), A));
        return countInside(convexHull(boys), girls);
    }
    if (ab && bc) {
        boys.erase(find(ALL(boys), B));
        return countInside(convexHull(boys), girls);
    }
    if (bc && ca) {
        boys.erase(find(ALL(boys), C));
        return countInside(convexHull(boys), girls);
    }
    return 0;
}

int main(void) {
#ifdef SKY
    freopen("tmp.txt", "r", stdin);
#endif // SKY

    cout << process() << endl;
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/

