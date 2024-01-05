/*
    POJ 1195 Mobile-phones
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1050;

inline int lowbit(int x) {
    return x & -x;
}

struct BIT_2D {
    ll a[MAXN][MAXN];  // 存输入的数，后变为2维度前缀和
    ll t1[MAXN][MAXN], t2[MAXN][MAXN], t3[MAXN][MAXN], t4[MAXN][MAXN];  // 维护 +v , +j*v , +i*v , +i*j*v
    int n, m;
    inline void init(int _n, int _m) {
        n = _n, m = _m;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j],
                    t1[i][j] = t2[i][j] = t3[i][j] = t4[i][j] = 0;
    }
    inline ll ask(int x, int y) {  // 单点查询
        ll ans = a[x][y];

        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                ans += (x + 1) * (y + 1) * t1[i][j] - (x + 1) * t2[i][j] - (y + 1) * t3[i][j] + t4[i][j];

        return ans;
    }
    inline void add(int x, int y, ll v) {  // 单点修改
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                t1[i][j] += v, t2[i][j] += y * v, t3[i][j] += x * v, t4[i][j] += x * y * v;
    }
    inline void query(int x1, int y1, int x2, int y2, ll v) {  // 区域修改
        add(x1, y1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
        add(x2 + 1, y2 + 1, v);
    }
    inline ll modify(int x1, int y1, int x2, int y2) {  // 区域查询
        return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
    }
} fff;

int main() {
    int opt, n, m;
    cin >> opt >> n;
    m = n;
    fff.init(n, m);

    while (cin >> opt) {
        if (opt == 3)
            break;

        if (opt == 1) {
            int x, y, v;
            cin >> x >> y >> v;
            x++, y++;
            fff.query(x, y, x, y, v);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1++, y1++, x2++, y2++;
            cout << fff.modify(x1, y1, x2, y2) << "\n";
        }
    }

    return 0;
}

/*
0 4
1 1 2 3
2 0 0 2 2
1 1 1 2
1 1 2 -1
2 1 1 2 3
3

3
4
*/