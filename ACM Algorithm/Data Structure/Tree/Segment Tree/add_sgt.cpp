/*
    洛谷 P3372 【模板】线段树1
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 500005;

struct SGT {    // 加法线段树
    ll a[MAXN];
    struct Node {
        int l, r;
        ll lz, sum;
    } node[MAXN << 2];

    inline void pushdown(int rt) {
        if (node[rt].lz != 0) {
            int ls = rt << 1, rs = rt << 1 | 1;
            node[ls].lz += node[rt].lz;
            node[rs].lz += node[rt].lz;
            node[ls].sum += node[rt].lz * (node[ls].r - node[ls].l + 1);
            node[rs].sum += node[rt].lz * (node[rs].r - node[rs].l + 1);
            node[rt].lz = 0;
        }
    }
    inline void pushup(int rt) {
        node[rt].sum = node[rt << 1].sum + node[rt << 1 | 1].sum; //修改需回溯
    }
    inline void build(int l, int r, int rt = 1) {
        //建树
        int ls = rt << 1, rs = rt << 1 | 1;
        node[rt].lz = 0;
        node[rt].l = l, node[rt].r = r;

        if (l == r) {
            node[rt].sum = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        node[rt].sum = node[ls].sum + node[rs].sum;
    }
    ll query(int l, int r, int rt = 1) {
        //区间求和
        int ls = rt << 1, rs = rt << 1 | 1;

        if (l <= node[rt].l && r >= node[rt].r)
            return node[rt].sum;

        pushdown(rt); //查询向下找不需回溯

        if (node[rt].r < l || node[rt].l > r)
            return 0;

        ll s = 0;

        if (node[ls].r >= l)
            s += query(l, r, ls);

        if (node[rs].l <= r)
            s += query(l, r, rs);

        return s;
    }
    void modify(int l, int r, ll k, int rt = 1) {
        //区间修改
        int ls = rt << 1, rs = rt << 1 | 1;

        if (l <= node[rt].l && r >= node[rt].r) {
            node[rt].sum += (node[rt].r - node[rt].l + 1) * k;
            node[rt].lz += k;
            return;
        }

        pushdown(rt); //向下

        if (l <= node[ls].r)
            modify(l, r, k, ls);

        if (r >= node[rs].l)
            modify(l, r, k, rs);

        pushup(rt);
        return;
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> fff.a[i];

    fff.build(1, n);

    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        ll k;
        cin >> opt >> x >> y;

        if (opt == 1) {
            cin >> k;
            fff.modify(x, y, k);
        } else
            cout << fff.query(x, y) << "\n";
    }

    return 0;
}

/*
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4

11
8
20
*/