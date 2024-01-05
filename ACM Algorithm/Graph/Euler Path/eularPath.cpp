/*
    UOJ #117 欧拉回路（有向图/无向图，模板）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Edge {
    int to;
    int nxt;
} edge[MAXN << 1];
int head[MAXN], tot;
int in[MAXN], out[MAXN];
int stk[MAXN], top;
int vis[MAXN << 1];
int n, m;

inline void add_edge(int u, int v) {
    edge[++tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot;
}

void dfs1(int u) {
    for (int &i = head[u]; i; i = edge[i].nxt) {
        // 当前边优化
        if (vis[i >> 1])
            continue;

        vis[i >> 1] = 1;
        int t = i;
        dfs1(edge[i].to);
        stk[++top] = ((t & 1) ? -(t >> 1) : (t >> 1));
    }
}

void dfs2(int u) {
    for (int &i = head[u]; i; i = edge[i].nxt) {
        if (vis[i])
            continue;

        vis[i] = 1;
        int t = i;
        dfs2(edge[i].to);
        stk[++top] = t;
    }
}

inline bool euler_path(int type, vector<int> &ans) {
    // type ：1（无向图），2（有向图）
    if (type & 1) {
        // 无向图 （不存在奇数度）
        tot = 1;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
            add_edge(v, u);
            in[u]++, in[v]++;
        }

        for (int i = 1; i <= n; i++)
            if (in[i] & 1)
                return false;

        dfs1(edge[tot].to);
    } else {
        // 有向图 （所有点 入度 = 出度）
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
            out[u]++, in[v]++;
        }

        for (int i = 1; i <= n; i++)
            if (in[i] != out[i])
                return false;

        dfs2(edge[tot].to);
    }

    if (top != m)   //  其余联通块还存在边，不能一笔画完回到起点
        return false;

    for (int i = top; i >= 1; i--)
        ans.push_back(stk[i]);

    return true;
}

int main() {
    int type;
    cin >> type;
    cin >> n >> m;

    vector<int> ans;
    cout << (euler_path(type, ans) ? "YES\n" : "NO\n");
    int ed = ans.size() - 1;

    for (int i = 0; i <= ed; i++)
        cout << ans[i] << (i == ed ? "\n" : " ");

    return 0;
}

/*
1
3 3
1 2
2 3
1 3
YES
1 2 -3

2
5 6
2 3
2 5
3 4
1 2
4 2
5 1
YES
4 1 3 5 2 6
*/