// Author: RR
// Trong code nay, phan cat 2 tam giac O-A(i)-A(i+1) va O-B(i)-B(i+1) minh xet 
// truong hop. De code don gian hon co the dung phuong phap cat da giac nhu da
// mo ta trong Editorial.

#include <sstream>
#include <fstream>
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }


const int MAX_COORDINATES = 1000;

#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    double operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << '(' << p.x << ',' << p.y << ')';
    return cout;
}

struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a, double b, double c) : a(a), b(b), c(c) {} 

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && cmp(l1.c*l2.a, l2.c*l1.a) == 0
                && cmp(l1.c*l2.b, l1.b*l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

void closestPoint(Line l, Point p, Point &ans) {
    if (fabs(l.b) < EPS) {
        ans.x = -(l.c) / l.a; ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {
        ans.x = p.x; ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, - (l.b*p.x - l.a*p.y));
    assert(areIntersect(l, perp, ans));
}

void reflectionPoint(Line l, Point p, Point &ans) {
    Point b;
    closestPoint(l, p, b);
    ans = p + (b - p) * 2;
}

typedef vector< Point > Polygon;

int sign(double x) {
    if (cmp(x, 0) == 0) return 0;
    if (x < 0) return -1;
    return 1;
}

// Area, perimeter, centroid
double signed_area(Polygon p) {
    double area = 0;
    for(int i = 0; i < SZ(p); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
double area(const Polygon &p) {
    return fabs(signed_area(p));
}

// Cut a polygon with a line. Returns one half.
// To return the other half, reverse the direction of Line l (by negating l.a, l.b)
// The line must be formed using 2 points
Polygon polygon_cut(const Polygon& P, Line l) {
    Polygon Q;
    for(int i = 0; i < SZ(P); ++i) {
        Point A = P[i], B = (i == SZ(P)-1) ? P[0] : P[i+1];
        if (ccw(l.A, l.B, A) != -1) Q.push_back(A);
        if (ccw(l.A, l.B, A)*ccw(l.A, l.B, B) < 0) {
            Point p; areIntersect(Line(A, B), l, p);
            Q.push_back(p);
        }
    }
    return Q;
}

bool order(Point A, Point B, Point C) {
    return min(A, C) <= B && B <= max(A, C);
}

double tri_intersect(Point O, Point A1, Point A2, Point B1, Point B2) {
    // Tam giac dien tich 0.
    if (ccw(O, A1, A2) == 0) return 0.0;
    if (ccw(O, B1, B2) == 0) return 0.0;

    // Dam bao thu' tu dinh nguoc chieu kim dong ho: O -> B2 -> B1; O -> A2 -> A1; O -> B1 -> A1.
    if (ccw(O, A1, A2) == RE_TRAI) swap(A1, A2);
    if (ccw(O, B1, B2) == RE_TRAI) swap(B1, B2);
    if (ccw(O, A1, B1) == RE_TRAI) {
        swap(A1, B1);
        swap(A2, B2);
    }

    // 2 tam giac ko giao nhau.
    if (ccw(O, B1, A2) == RE_TRAI || ccw(O, B1, A2) == 0) return 0.0;

    if (ccw(O, A2, B2) != RE_PHAI) {
        // O -> A2 -> B2 -> B1 -> A1

        bool b1_inside = ccw(A2, A1, B1) != RE_PHAI;
        bool b2_inside = ccw(A2, A1, B2) != RE_PHAI;

        if (b1_inside && b2_inside) return area(Polygon {O, B1, B2});
        if (!b1_inside && !b2_inside) {
            Point X, Y;
            assert(areIntersect(Line(O, B1), Line(A1, A2), X));
            assert(areIntersect(Line(O, B2), Line(A1, A2), Y));

            return area(Polygon {O, X, Y});
        }

        if (b2_inside) swap(B1, B2);
        Point X, Y;
        assert(areIntersect(Line(B1, B2), Line(A1, A2), X));
        assert(areIntersect(Line(O, B2), Line(A1, A2), Y));

        return area(Polygon {O, B1, X, Y});
    } else {
        Polygon all;
        all.push_back(O);

        bool b1_inside = ccw(A2, A1, B1) != RE_PHAI;
        if (b1_inside) all.push_back(B1);
        else {
            Point X;
            assert(areIntersect(Line(O, B1), Line(A1, A2), X));
            all.push_back(X);
        }

        Point X;
        if (areIntersect(Line(B1, B2), Line(A1, A2), X)) {
            if (order(B1, X, B2) && order(A1, X, A2)) {
                all.push_back(X);
            }
        }

        bool ok = false;
        if (areIntersect(Line(B1, B2), Line(O, A2), X)) {
            if (order(B1, X, B2) && order(O, X, A2)) {
                ok = true;
                all.push_back(X);
            }
        }
        if (!ok) {
            all.push_back(A2);
        }
        return area(all);
    }
    assert(false);
}

double common_area(Polygon a, Polygon b) {
    if (sign(signed_area(a)) < 0) reverse(ALL(a));
    if (sign(signed_area(b)) < 0) reverse(ALL(b));

    double res = 0.0;
    Point O(-MAX_COORDINATES - 1, -MAX_COORDINATES - 1);

    REP(ia,SZ(a)) {
        Point A1 = a[ia];
        Point A2 = a[(ia + 1) % SZ(a)];
        Polygon tri_a {O, A1, A2};
        int sign_a = sign(signed_area(tri_a));

        REP(ib, SZ(b)) {
            Point B1 = b[ib];
            Point B2 = b[(ib + 1) % SZ(b)];
            Polygon tri_b {O, B1, B2};
            int sign_b = sign(signed_area(tri_b));

            res += sign_a * sign_b * tri_intersect(O, A1, A2, B1, B2);
        }
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(12) << boolalpha;

    int n;
    cin >> n;
    Polygon a(n);
    REP(i,n) cin >> a[i];

    Point A, B; cin >> A >> B;
    Line lAB(A, B), lBA(B, A);

    // Step 1: Cut polygon into 2 pieces: left & right
    Polygon left = polygon_cut(a, lAB);
    Polygon right = polygon_cut(a, lBA);

    if (cmp(area(left), 0) == 0 || cmp(area(right), 0) == 0) {
        cout << 0.0 << endl;
        return 0;
    }

    // Step 2: reflect left through line d.
    Polygon ref(SZ(left));
    REP(i,SZ(left)) {
        reflectionPoint(lAB, left[i], ref[i]);
    }

    // Step 3: get common area.
    cout << common_area(ref, right) << endl;

    return 0;
}

