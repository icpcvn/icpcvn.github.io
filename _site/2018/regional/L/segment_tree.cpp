// Author: team trie

#include <bits/stdc++.h>
#define maxn 20010
#define cmax 1000000007
#define el '\n'
#define pb push_back
#define mp make_pair
#define IOS ios_base::sync_with_stdio(false); cin.tie(NULL)
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Ford(i, a, b) for(int i = (a); i >= (b); i--)
#define next _next
using namespace std;

typedef long long ll;
typedef pair <int, int> ptq;

string st, s[20010];
int n, num;
int m;

int next[510][26];

struct query
{
    int l, r, k, id;
    int ans;
} q[300010];

int R[maxn];

bool cmp(query a, query b)
{
    return (a.l < b.l || (a.l == b.l && a.r < b.r));
}

bool cmpAns(query a, query b)
{
    return a.id < b.id;
}

void initNext()
{
    For(i, 0, 25) next[m][i] = m;
    Ford(i, m - 1, 0)
    {
        For(c, 0, 25) next[i][c] = next[i+1][c];
        next[i][(int)(st[i] - 'a')] = i;
    }
}

void initLeft(int l)
{
    For(i, 1, n)
    {
        int id = l - 1;
        for(int j = 0; j < s[i].size(); j++)
        {
            id = next[id][s[i][j] - 'a'];
            if (j < (int)s[i].size() - 1)
                id++;
            if (id >= m) break;
        }
        R[i] = min(id + 1, m + 1);
    }
}

ptq x[maxn];
int t[maxn*4];

#define mid ((lo + hi)>>1)
void update(int i, int lo, int hi, int u)
{
    if (lo > u || hi < u)
        return;
    if (lo == hi)
    {
        t[i]++;
        return;
    }
    update(i * 2, lo, mid, u);
    update(i * 2 + 1, mid + 1, hi, u);
    t[i] = t[i*2] + t[i*2+1];
}

int get(int i, int lo, int hi, int k)
{
    if (t[i] < k)
        return -1;
    if (lo == hi)
    {
        return lo;
    }
    if (t[i*2] >= k)
        return get(i * 2, lo, mid, k);
    return get(i * 2 + 1, mid + 1, hi, k - t[i*2]);
}

int main()
{
    IOS;
    cin >> st;
    m = st.size();
    cin >> n >> num;
    For(i, 1, n)
    {
        cin >> s[i];
    }
    sort(s + 1, s + n  + 1);

    For(i, 1, num)
    {
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].id = i;
    }
    sort(q + 1, q + num + 1, cmp);

    initNext();

    int curR;

    for(int i = 1; i <= num; i++)
    {
        if (i == 1 || q[i].l != q[i-1].l)
        {
            initLeft(q[i].l);
            curR = 0;
            For(i, 1, n)
            {
                x[i].first = R[i];
                x[i].second = i;
            }
            sort(x + 1, x + n + 1);
            For(i, 1, 4 * n)
                t[i] = 0;
        }
        while (curR < n && x[curR + 1].first  <= q[i].r)
        {
            ++curR;
            update(1, 1, n, x[curR].second);
        }
        q[i].ans =  get(1, 1, n, q[i].k);
    }

    sort(q + 1, q + num + 1, cmpAns);

    For(i, 1, n)
    {
        if (s[i].size() > 10)
        {
            s[i] = s[i].substr(0, 10);
        }
    }

    For(i, 1, num)
    {
        if (q[i].ans == -1)
            cout << "NO SUCH WORD" << el;
        else cout << s[q[i].ans] << endl;
    }


}
