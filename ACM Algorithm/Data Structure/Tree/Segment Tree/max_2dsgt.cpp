/*
    atcoder abc228 F_Stamp-Game（二维线段树，区间最大/最小值，单点修改，O(nmlognlogm)）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
typedef long long ll;
const ll INF = 1e18;
const int MAXN = 1005;
/*
初始化调用build(1,n); n为宽，初始值全为 0
update(int x,int y,int val); 将点x，y处的值修改为val;
queryMax(x1, x2, y1, y2);
queryMin(x1, x2, y1, y2);
x1 <= x2 y1 <= y2，表示矩形区域; 所有的坐标都是闭区间S
x1, x2, y1, y2分别表示上界，下界，左界， 右界
*/
int n, m;
ll mat[MAXN][MAXN], sum[MAXN][MAXN], val[MAXN][MAXN];
int locx[MAXN], locy[MAXN];     // 值在竖轴上的节点编号，值在横轴上的节点编号

struct SGT2d {
    struct Nodey {
        int l, r;
        ll Max;
    };

    struct Nodex {
        int l, r;
        Nodey sty[MAXN << 2];
        void build(int l, int r, int rt = 1) {
            sty[rt].l = l, sty[rt].r = r;

            if (l == r) {
                locy[l] = rt;
                return;
            }

            int mid = (l + r) >> 1;
            build(l, mid, ls(rt));
            build(mid + 1, r, rs(rt));
        }
        ll queryMax(int l, int r, int rt = 1) {
            if (sty[rt].l >= l && sty[rt].r <= r)
                return sty[rt].Max;

            int mid = (sty[rt].l + sty[rt].r) >> 1;
            ll res = -INF;

            if (l <= mid)
                res = max(res, queryMax(l, r, ls(rt)));

            if (r > mid)
                res = max(res, queryMax(l, r, rs(rt)));

            return res;
        }
    } stx[MAXN << 2];

    void build(int l, int r, int rt = 1) {
        stx[rt].l = l, stx[rt].r = r;
        stx[rt].build(1, m);    // 宽

        if (l == r) {
            locx[l] = rt;
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, ls(rt));
        build(mid + 1, r, rs(rt));
    }

    ll queryMax(int x1, int x2, int y1, int y2, int rt = 1) {
        if (stx[rt].l >= x1 && stx[rt].r <= x2)
            return stx[rt].queryMax(y1, y2);

        int mid = (stx[rt].l + stx[rt].r) >> 1;
        ll res = -INF;

        if (x1 <= mid)
            res = max(res, queryMax(x1, x2, y1, y2, ls(rt)));

        if (x2 > mid)
            res = max(res, queryMax(x1, x2, y1, y2, rs(rt)));

        return res;
    }

    void update(int x, int y, ll val) {
        int tx = locx[x], ty = locy[y];
        stx[tx].sty[ty].Max = val;

        for (int i = tx; i; i >>= 1)
            for (int j = ty; j; j >>= 1) {
                if (i == tx && j == ty)
                    continue;

                if (j == ty)
                    stx[i].sty[j].Max = max(stx[i << 1].sty[j].Max, stx[(i << 1) | 1].sty[j].Max);
                else
                    stx[i].sty[j].Max = max(stx[i].sty[j << 1].Max, stx[i].sty[(j << 1) | 1].Max);
            }
    }
} fff;

inline void solve() {
    cin >> n >> m;
    int h1, h2, w1, w2;
    cin >> h1 >> w1 >> h2 >> w2;
    fff.build(1, n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
        }

    int h = min(h2, h1), w = min(w2, w1);

    for (int i = 1; i + h - 1 <= n; i++)
        for (int j = 1; j + w - 1 <= m; j++)
            fff.update(i,
                       j,
                       sum[i + h - 1][j + w - 1] - sum[i - 1][j + w - 1] - sum[i + h - 1][j - 1] + sum[i - 1][j - 1]);

    ll mx = -INF;

    for (int i = 1; i + h1 - 1 <= n; i++)
        for (int j = 1; j + w1 - 1 <= m; j++)
            mx = max(mx,
                     sum[i + h1 - 1][j + w1 - 1] - sum[i - 1][j + w1 - 1] - sum[i + h1 - 1][j - 1] + sum[i - 1][j - 1]
                         - fff.queryMax(i, i + h1 - 1 - h + 1, j, j + w1 - 1 - w + 1));

    cout << mx << "\n";
    return;
}

int main() {
    closeSync;
    //  int T;  cin >> T;
    //  while (T--)
    solve();
    return 0;
}

/*
3 4 2 3 3 1
3 1 4 1
5 9 2 6
5 3 5 8

19
*/
 