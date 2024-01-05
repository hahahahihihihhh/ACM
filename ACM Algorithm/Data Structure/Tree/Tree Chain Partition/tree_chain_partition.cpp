/*
    洛谷 P3384 【模板】轻重链剖分
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

struct TCP {
    //-----需要的变量，函数-----//
    int n;
    int son[MAXN], dep[MAXN], fa[MAXN], siz[MAXN];  //重儿子，深度，父亲，结点大小
    int tim, dfn[MAXN],
        top[MAXN];  //对应时间戳的节点权值（线段树维护），计时器，时间戳，链顶结点
    ll v[MAXN], w[MAXN];  // v为原始点权，w为对应时间戳的点权
    int head[MAXN], tot = 1;
    struct Node {
        int l, r;
        ll sum, lz;
    } node[MAXN << 2];
    struct Edge {
        int to;
        int nxt;
    } edge[MAXN << 1];
    inline void init(int _n) {
        n = _n, tim = 0, tot = 1;

        for (int i = 1; i <= n; i++)
            son[i] = dep[i] = fa[i] = siz[i] = dfn[i] = top[i] = v[i] = w[i] = head[i] = 0;
    }
    inline ll add(ll x, ll MOD) {
        while (x < 0)
            x += MOD;

        return x % MOD;
    }
    inline void add_edge(int u, int v) {
        edge[++tot].to = v;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
    //------ 线段树 -------//
    void build(int l, int r, int rt = 1) {  //建树
        node[rt].l = l, node[rt].r = r;

        if (l == r) {
            node[rt].sum = w[l];
            return;
        }

        int ls = rt << 1, rs = rt << 1 | 1;
        int mid = (l + r) >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        node[rt].sum = (node[ls].sum + node[rs].sum);
    }
    inline void pushdown(int rt) {  //传递lz标记
        if (node[rt].lz) {
            int ls = rt << 1, rs = rt << 1 | 1;
            node[ls].lz = (node[ls].lz + node[rt].lz);
            node[rs].lz = (node[rs].lz + node[rt].lz);
            node[ls].sum = (node[ls].sum + (node[ls].r - node[ls].l + 1) * node[rt].lz);
            node[rs].sum = (node[rs].sum + (node[rs].r - node[rs].l + 1) * node[rt].lz);
            node[rt].lz = 0;
        }
    }
    ll query(int l, int r, int rt = 1) {  //区间查询
        if (l <= node[rt].l && node[rt].r <= r)
            return node[rt].sum;

        int ls = rt << 1, rs = rt << 1 | 1;
        pushdown(rt);
        ll ans = 0;

        if (node[ls].r >= l)
            ans = (ans + query(l, r, ls));

        if (node[rs].l <= r)
            ans = (ans + query(l, r, rs));

        return ans;
    }
    void modify(int l, int r, ll x, int rt = 1) {  //区间修改
        if (l <= node[rt].l && node[rt].r <= r) {
            node[rt].sum = (node[rt].sum + (node[rt].r - node[rt].l + 1) * x);
            node[rt].lz = (node[rt].lz + x);
            return;
        }

        pushdown(rt);
        int ls = rt << 1, rs = rt << 1 | 1;

        if (node[ls].r >= l)
            modify(l, r, x, ls);

        if (node[rs].l <= r)
            modify(l, r, x, rs);

        node[rt].sum = (node[ls].sum + node[rs].sum);
        return;
    }
    //-----轻重链划分-----//
    void dfs1(int u, int
    f) {  //预处理，获得节点深度，节点的父亲节点，节点子树大小，节点重儿子
        dep[u] = dep[f] + 1;
        fa[u] = f;
        siz[u] = 1;
        int maxSize = -1;

        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;

            if (v == f)
                continue;

            dfs1(v, u);
            siz[u] += siz[v];

            if (siz[v] > maxSize)
                son[u] = v, maxSize = siz[v];
        }
    }
    void dfs2(
        int u,
        int ff) {  //划分树链（轻儿子开始，重儿子结束），获得节点时间戳，节点对应于时间戳的权值，节点的顶部节点。
        dfn[u] = ++tim;
        w[tim] = v[u];
        top[u] = ff;

        if (!son[u])
            return;

        dfs2(son[u], ff);

        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;

            if (v == son[u] || v == fa[u])
                continue;

            dfs2(v, v);
        }
    }
    //树上操作//
    inline void mchain(int u, int v, ll k) {  //将 u,v 路径上的所有点权 +k
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);  // u的深度更大

            modify(dfn[top[u]], dfn[u], k);
            u = fa[top[u]];
        }

        if (dfn[u] > dfn[v])
            swap(u, v);

        modify(dfn[u], dfn[v], k);
    }
    inline ll qchain(int u, int v) {  //查询 u,v 路径上的点权和
        ll ans = 0;

        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);  // u的深度更大

            ans = (ans + query(dfn[top[u]], dfn[u]));
            u = fa[top[u]];  //!!!
        }

        if (dfn[u] > dfn[v])
            swap(u, v);

        return (ans + query(dfn[u], dfn[v]));
    }
    inline void mson(int u, ll k) {  // u 子树的所有点权 +k
        modify(dfn[u], dfn[u] + siz[u] - 1, k);
    }
    inline ll qson(int u) {  //查询 u 子树的点权和
        return query(dfn[u], dfn[u] + siz[u] - 1);
    }
    inline void dissection(int r) { // r 为根节点
        dfs1(r, r);   //预处理
        dfs2(r, r);   //划分轻重链
        build(1, n);  //建线段树
    }
} fff;

//主函数//
int main() {
    int n, m, r, p;
    cin >> n >> m >> r >> p; //点数，边数，根节点，模数
    fff.init(n);

    for (int i = 1; i <= n; i++)
        cin >> fff.v[i];  //点权

    for (int i = 1; i <= n - 1; i++) { //建树
        int u, v;
        cin >> u >> v;
        fff.add_edge(u, v), fff.add_edge(v, u);
    }

    fff.dissection(r);  // r为根，剖分

    while (m--) {   //操作
        int opt, x, y, z;
        cin >> opt;

        if (opt == 1) {
            //将 u,v 路径上的所有点权 +k
            cin >> x >> y >> z;
            fff.mchain(x, y, z);
        } else if (opt == 2) {
            //查询 u,v 路径上的点权和
            cin >> x >> y;
            cout << fff.qchain(x, y) % p << endl;
        } else if (opt == 3) {
            //u 子树的所有点权 +k
            cin >> x >> z;
            fff.mson(x, z);
        } else {
            //查询 u 子树的点权和
            cin >> x;
            cout << fff.qson(x) % p << endl;
        }
    }

    return 0;
}

/*
5 5 2 24
7 3 7 8 0
1 2
1 5
3 1
4 1
3 4 2
3 2 2
4 5
1 5 1 3
2 1 3

2
21
*/