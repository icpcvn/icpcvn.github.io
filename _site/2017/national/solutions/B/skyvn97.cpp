// Author: skyvn97
// Brute force + greedy

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

const char chdir[] = "v^<>";
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Center {
    int row, col, value;

    Center(int r = 0, int c = 0, int v = 0) {
        row = r; col = c; value = v;
    }

    int distan(int x, int y) const {
        return Abs(row - x) + Abs(col - y);
    }
};

#define MAX_SIZE   15
#define MAX_CELL   77

#define EMPTY_CELL   '.'
#define BLOCKED_CELL   '#'

int numRow, numCol, numCenter;
char board[MAX_SIZE][MAX_SIZE];
Center centers[MAX_CELL];
int fillBy[MAX_SIZE][MAX_SIZE][4];

bool inside(int x, int y) {
    return 0 <= x && x < numRow && 0 <= y && y < numCol;
}
int distan(int x1, int y1, int x2, int y2) {
    return Abs(x1 - x2) + Abs(y1 - y2);
}

struct SolutionFoundException {};

class State {
private:
    struct SolutionUnavailableException {};

    char board[MAX_SIZE][MAX_SIZE];
    int limit[MAX_CELL][4], range[MAX_CELL][4];

    void calcLimit(void) {
        REP(i, numCenter) {
            int need = getNeed(i);
            REP(j, 4) {
                int cx = centers[i].row + dx[j] * (range[i][j] + 1);
                int cy = centers[i].col + dy[j] * (range[i][j] + 1);
                limit[i][j] = range[i][j];
                while (limit[i][j] < range[i][j] + need && inside(cx, cy) && board[cx][cy] == EMPTY_CELL) {
                    limit[i][j]++;
                    cx += dx[j]; cy += dy[j];
                }
            }
        }
    }

    void fillCell(int centerID, int dir, int dist) {
        int cx = centers[centerID].row;
        int cy = centers[centerID].col;
        assert(range[centerID][dir] < dist);
        assert(dist <= limit[centerID][dir]);
        FOR(i, 1, dist) {
            int x = cx + dx[dir] * i;
            int y = cy + dy[dir] * i;
            assert(inside(x, y));
            assert(board[x][y] == EMPTY_CELL || board[x][y] == chdir[dir]);
            board[x][y] = chdir[dir];
        }
        range[centerID][dir] = dist;
        calcLimit();
    }

    int getAllow(int centerID) {
        int res = 0;
        REP(i, 4) res += limit[centerID][i] - range[centerID][i];
        return res;
    }
    int getNeed(int centerID) {
        int res = centers[centerID].value;
        REP(i, 4) res -= range[centerID][i];
//        if (res < 0) printf("FAIL %d %d\n", centers[centerID].row, centers[centerID].col);
        assert(res >= 0);
        return res;
    }

    int getFillCandidate(int x, int y, int dir) {
        if (fillBy[x][y][dir] < 0) return -1;
        int tmp = fillBy[x][y][dir];
        return limit[tmp][dir] >= centers[tmp].distan(x, y) ? tmp : -1;
    }

    int countFillCandidate(int x, int y) {
        int res = 0;
        REP(i, 4) if (getFillCandidate(x, y, i) >= 0) res++;
        return res;
    }

    void autoFill(void) {
        calcLimit();
        while (true) {
            bool cont = false;
            REP(i, numRow) REP(j, numCol) if (board[i][j] == EMPTY_CELL) {
                int tmp = countFillCandidate(i, j);
                if (tmp == 0) throw SolutionUnavailableException();
                if (tmp == 1) {
                    int dir = -1, centerID = -1;
                    REP(k, 4) {
                        centerID = getFillCandidate(i, j, k);
                        if (centerID >= 0) {
                            dir = k;
                            break;
                        }
                    }
                    assert(dir >= 0);
                    fillCell(centerID, dir, centers[centerID].distan(i, j));
                    cont = true;
                }
            }

            REP(i, numCenter) {
                int need = getNeed(i);
                int allow = getAllow(i);
                if (allow < need) throw SolutionUnavailableException();
                REP(j, 4) if (allow - (limit[i][j] - range[i][j]) < need) {
                    int delta = need - (allow - (limit[i][j] - range[i][j]));
                    fillCell(i, j, range[i][j] + delta);
                    cont = true;
                }
            }

            if (!cont) break;
        }
    }

    void checkSolutionExist(void) {
        REP(i, numRow) REP(j, numCol) if (board[i][j] == EMPTY_CELL && countFillCandidate(i, j) == 0)
            throw SolutionUnavailableException();
        REP(i, numCenter) {
            int need = getNeed(i);
            int allow = getAllow(i);
            if (allow < need) throw SolutionUnavailableException();
        }
    }

    void checkSolutionFound(void) {
        REP(i, numRow) REP(j, numCol) if (board[i][j] == EMPTY_CELL) return;
        REP(i, numRow) printf("%s\n", board[i]);
        throw SolutionFoundException();
    }

    int findNextCell(void) {
        int best = -1;
        int maxDist = -1;
        REP(i, numRow) REP(j, numCol) if (board[i][j] == EMPTY_CELL) {
            int minDist = MAX_CELL;
            REP(k, 4) {
                int tmp = getFillCandidate(i, j, k);
                if (tmp < 0) continue;
                minimize(minDist, centers[tmp].distan(i, j));
            }
            if (maxDist < minDist) {
                maxDist = minDist;
                best = i * numCol + j;
            }
        }
        return best;
    }

public:
    State(char input[][MAX_SIZE] = NULL) {
        memset(board, 0, sizeof board);
        memset(limit, 0, sizeof limit);
        memset(range, 0, sizeof range);
        if (input == NULL) return;

        REP(i, numRow) REP(j, numCol) board[i][j] = input[i][j];
    }

    State manualFill(int centerID, int dir, int dist) {
        State res = *this;
        res.fillCell(centerID, dir, dist);
        res.autoFill();
        res.checkSolutionExist();
        res.checkSolutionFound();
        return res;
    }

    void backtrack(bool isRoot) {
        if (isRoot) {
            try {
                autoFill();
                checkSolutionExist();
                checkSolutionFound();
            } catch (SolutionUnavailableException e) {
                return;
            }
        }

        int cell = findNextCell();
        int row = cell / numCol;
        int col = cell % numCol;

        REP(i, 4) {
            int tmp = getFillCandidate(row, col, i);
            if (tmp < 0) continue;
            int dist = centers[tmp].distan(row, col);

            State newState;
            try {
                newState = manualFill(tmp, i, dist);
            } catch (SolutionUnavailableException e) {
                continue;
            }
            newState.backtrack(false);
        }
    }

    void printState(void) const {
        printf("___STATE___\n");
        REP(i, numRow) printf("%s\n", board[i]);
        REP(i, numCenter) if (centers[i].row == 1 && centers[i].col == 7) {
            printf("At cell %d, %d:\n", centers[i].row, centers[i].col);
            REP(j, 4) printf("\tdir %c: %d over %d\n", chdir[j], range[i][j], limit[i][j]);
        }
        printf("___END___\n");
    }
};

void init(void) {
    scanf("%d%d", &numRow, &numCol);
    REP(i, numRow) scanf("%s", board[i]);
    REP(i, numRow) REP(j, numCol) if ('1' <= board[i][j] && board[i][j] <= '9')
        centers[numCenter++] = Center(i, j, board[i][j] - '0');

    memset(fillBy, -1, sizeof fillBy);
    REP(i, numCenter) REP(j, 4) FOR(k, 1, MAX_CELL) {
        int x = centers[i].row + dx[j] * k;
        int y = centers[i].col + dy[j] * k;
        if (!inside(x, y) || board[x][y] != EMPTY_CELL) break;
        fillBy[x][y][j] = i;
    }

}

void process(void) {
    State start(board);
    try {
        start.backtrack(true);
    } catch (SolutionFoundException e) {
        return;
    }

    cout << "SOLUTION NOT FOUND" << endl;
}

int main(void) {
#ifdef SKY
    freopen("tmp.txt", "r", stdin);
#endif // SKY
    init();
    process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/

