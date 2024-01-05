/*
    洛谷 P3379 【模板】最近公共祖先（LCA）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

struct TL {
    int fa[MAXN];
    int tot1 = 1, tot2 = 1;
    int rt;
    int head1[MAXN], head2[MAXN];
    int vis[MAXN], ans[MAXN];
    struct Query {
        int to;
        int nxt;
        int num;
    } query[MAXN << 1];

    struct Node {
        int to;
        int nxt;
    } node[MAXN << 1];

    inline void init(int n, int _rt) {
        tot1 = tot2 = 1;
        rt = _rt;

        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            head1[i] = head2[i] = vis[i] = 0;
        }
    }

    inline void add_edge(int x, int y) {
        //链式前向星 x->y
        node[++tot1].to = y;
        node[tot1].nxt = head1[x];
        head1[x] = tot1;
    }
    inline void add_query(int x, int y, int i) {
        query[++tot2].to = y;
        query[tot2].nxt = head2[x];
        head2[x] = tot2;
        query[tot2].num = i; //第i次询问
    }
    //并查集
    int tfind(int x) {
        return fa[x] == x ? x : fa[x] = tfind(fa[x]);
    }
    inline void tunion(int x, int y) {
        fa[tfind(x)] = tfind(y);
    }

    void tarjan(int u) {
        //后序遍历
        vis[u] = 1;

        for (int i = head1[u]; i; i = node[i].nxt) {
            int v = node[i].to;

            if (vis[v])
                continue;

            tarjan(v);
            tunion(v, u);
        }

        for (int i = head2[u]; i; i = query[i].nxt) {
            if (vis[query[i].to])   //该节点存在询问并且询问的节点已经访问过
                ans[query[i].num] = tfind(query[i].to);
        }
    }
} fff;

int main() {
    int n, m, r;
    cin >> n >> m >> r;
    fff.init(n, r);

    for (int i = 1; i <= n - 1; i++) {
        //树
        int u, v;
        cin >> u >> v;
        fff.add_edge(u, v);
        fff.add_edge(v, u);
    }

    for (int i = 1; i <= m; i++) {
        //离线
        int u, v;
        cin >> u >> v;
        fff.add_query(u, v, i);
        fff.add_query(v, u, i);
    }

    fff.tarjan(fff.rt);

    for (int i = 1; i <= m; i++)
        cout << fff.ans[i] << endl;

    return 0;
}

/*
5 5 4
3 1
2 4
5 1
1 4
2 4
3 2
3 5
1 2
4 5

4
4
1
4
4
*/