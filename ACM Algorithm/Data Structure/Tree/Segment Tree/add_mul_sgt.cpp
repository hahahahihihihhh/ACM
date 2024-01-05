/*
    洛谷 P3373 【模板】线段树2
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

ll p;
struct SGT {    // 乘法线段树
    struct Node {
        int l, r;
        ll sum;
        ll mlz, plz;
    } node[MAXN << 2];
    ll a[MAXN];

    inline void pushdown(int rt) {
        //标记下移动
        int ls = rt << 1, rs = rt << 1 | 1;
        ll k1 = node[rt].mlz, k2 = node[rt].plz;

        node[ls].sum = (node[ls].sum * k1 + k2 * (node[ls].r - node[ls].l + 1)) % p; //先乘后加
        node[ls].mlz = (node[ls].mlz * k1) % p;
        node[ls].plz = (node[ls].plz * k1 + k2) % p; //将要加上的量也需要被乘

        node[rs].sum = (node[rs].sum * k1 + k2 * (node[rs].r - node[rs].l + 1)) % p;
        node[rs].mlz = (node[rs].mlz * k1) % p;
        node[rs].plz = (node[rs].plz * k1 + k2) % p;

        node[rt].mlz = 1;
        node[rt].plz = 0;
    }
    void build(int l, int r, int rt = 1) {
        //建树
        node[rt].l = l;
        node[rt].r = r;
        node[rt].plz = 0;
        node[rt].mlz = 1;

        if (l == r) {
            node[rt].sum = a[l] % p;
            return;
        }

        int mid = (l + r) >> 1;
        int ls = rt << 1, rs = rt << 1 | 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        node[rt].sum = (node[ls].sum + node[rs].sum) % p;
        return;
    }
    void add(int l, int r, ll k, int rt = 1) {
        //区间加法
        int ls = rt << 1, rs = rt << 1 | 1;

        if (node[rt].l >= l && node[rt].r <= r) {
            node[rt].sum = (node[rt].sum + (node[rt].r - node[rt].l + 1) * k) % p;
            node[rt].plz = (node[rt].plz + k) % p;
            return;
        }

        pushdown(rt);

        if (node[ls].r >= l)
            add(l, r, k, ls);

        if (node[rs].l <= r)
            add(l, r, k, rs);

        node[rt].sum = (node[ls].sum + node[rs].sum) % p;
        return;
    }
    void mul(int l, int r, ll k, int rt = 1) {
        //区间乘法
        int ls = rt << 1, rs = rt << 1 | 1;

        if (node[rt].l >= l && node[rt].r <= r) {
            node[rt].sum = (node[rt].sum * k) % p;
            node[rt].mlz = (node[rt].mlz * k) % p;
            node[rt].plz = (node[rt].plz * k) % p; //乘法会修改将要加上的量
            return;
        }

        pushdown(rt);

        if (node[ls].r >= l)
            mul(l, r, k, ls);

        if (node[rs].l <= r)
            mul(l, r, k, rs);

        node[rt].sum = (node[ls].sum + node[rs].sum) % p;
        return;
    }
    ll query(int l, int r, int rt = 1) {
        //区间查询
        int ls = rt << 1, rs = rt << 1 | 1;

        if (l <= node[rt].l && node[rt].r <= r)
            return node[rt].sum;

        pushdown(rt);
        ll ans = 0;

        if (node[ls].r >= l)
            ans += query(l, r, ls);

        if (node[rs].l <= r)
            ans += query(l, r, rs);

        return ans % p;
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m >> p;

    for (int i = 1; i <= n; i++)
        cin >> fff.a[i];

    fff.build(1, n);

    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;

        if (opt == 1) {
            ll k;
            cin >> k;
            fff.mul(x, y, k);
        } else if (opt == 2) {
            ll k;
            cin >> k;
            fff.add(x, y, k);
        } else
            cout << fff.query(x, y) << "\n";
    }

    return 0;
}

/*
5 5 38
1 5 4 2 3
2 1 4 1
3 2 5
1 2 4 2
2 3 5 5
3 1 4

17
2
*/