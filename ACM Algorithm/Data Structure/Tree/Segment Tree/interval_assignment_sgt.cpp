/*
    atcoder abc196 E_Filters（区间赋值线段树）
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
const int MAXN = 200005;

ll a[MAXN];
int opt[MAXN];
pii X[MAXN];
int rec[MAXN];
ll dig[MAXN];
ll ans[MAXN];

struct SGT {    // 区间赋值线段树
    struct Node {
        int l, r;
        ll sum, lz;
    } node[MAXN << 2];

    inline void pushup(int rt) {
        int ls = rt << 1, rs = rt << 1 | 1;
        node[rt].sum = node[ls].sum + node[rs].sum;
    }
    inline void pushdown(int rt) {
        if (node[rt].lz) {  // lz = 0 代表未被赋值状态
            int ls = rt << 1, rs = rt << 1 | 1;
            node[ls].sum = (node[ls].r - node[ls].l + 1) * node[rt].lz;
            node[rs].sum = (node[rs].r - node[rs].l + 1) * node[rt].lz;
            node[ls].lz = node[rs].lz = node[rt].lz;
            node[rt].lz = 0;
        }
    }
    void build(int l, int r, int rt = 1) {
        // 建树
        node[rt].l = l, node[rt].r = r;

        if (l == r) {
            node[rt].sum = dig[l];
            node[rt].lz = 0;
            return;
        }

        int mid = (l + r) >> 1;
        int ls = rt << 1, rs = rt << 1 | 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(rt);
    }
    void modify(int l, int r, ll k, int rt = 1) {
        // 区间赋值
        if (l <= node[rt].l && node[rt].r <= r) {
            node[rt].sum = (node[rt].r - node[rt].l + 1) * k;
            node[rt].lz = k;
            return;
        }

        pushdown(rt);
        int ls = rt << 1, rs = rt << 1 | 1;

        if (node[ls].r >= l)
            modify(l, r, k, ls);

        if (node[rs].l <= r)
            modify(l, r, k, rs);

        pushup(rt);
    }
    ll query(int l, int r, int rt = 1) {
        // 区间查询
        if (l <= node[rt].l && node[rt].r <= r)
            return node[rt].sum;

        pushdown(rt);
        int ls = rt << 1, rs = rt << 1 | 1;
        ll ans = 0;

        if (node[ls].r >= l)
            ans += query(l, r, ls);

        if (node[rs].l <= r)
            ans += query(l, r, rs);

        return ans;
    }
} fff;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i] >> opt[i];

    int q;
    cin >> q;

    for (int i = 1; i <= q; i++) {
        cin >> X[i].first;
        X[i].second = i;
    }

    sort(X + 1, X + q + 1);

    for (int i = 1; i <= q; i++) {
        rec[i] = X[i].second;
        dig[i] = X[i].first;
    }

    fff.build(1, q);
    ll tmp = 0;

    for (int i = 1; i <= n; i++) {
        if (opt[i] == 1)
            tmp += a[i];
        else if (opt[i] == 2) {
            int r = lower_bound(dig + 1, dig + q + 1, a[i] - tmp) - dig - 1;
            int l = 1;

            if (l <= r) {
                fff.modify(l, r, a[i] - tmp);

                for (int j = l; j <= r; j++)
                    dig[j] = a[i] - tmp;
            }
        } else {
            int l = upper_bound(dig + 1, dig + q + 1, a[i] - tmp) - dig;
            int r = q;

            if (l <= r) {
                fff.modify(l, r, a[i] - tmp);

                for (int j = l; j <= r; j++)
                    dig[j] = a[i] - tmp;
            }
        }
    }

    for (int i = 1; i <= q; i++)
        ans[rec[i]] = fff.query(i, i) + tmp;

    for (int i = 1; i <= q; i++)
        cout << ans[i] << "\n";

    return 0;
}

/*
3
-10 2
10 1
10 3
5
-15 -10 -5 0 5

0
0
5
10
10
*/