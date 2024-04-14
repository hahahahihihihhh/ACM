/*
    洛谷 P3386 【模板】二分图最大匹配（O(m*sqrt(n))）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXM = MAXN * MAXN;
const int INF = 0x3f3f3f3f;

struct BM {
    int head[MAXN], tot = 1;
    int cur[MAXN], depth[MAXN];
    int match[MAXN];  // 存放匹配
    int n, m, s, t;
    struct Edge {
        int to;
        int w;
        int nxt;
    } edge[MAXM << 1];

    void init(int _n, int _m) {   // 左部点，右部点
        n = _n;
        m = _m;

        for (int i = 1; i <= n; i++)
            match[i] = 0;

        tot = 1;

        for (int i = 1; i <= n + m + 2; i++)
            head[i] = 0;
    }

    void add_edge(int u, int v, int w) {
        edge[++tot].to = v;
        edge[tot].nxt = head[u];
        edge[tot].w = w;
        head[u] = tot;
    };

    void build() {  //建立超级源点以及超级汇点，进行连边
        s = n + m + 1;
        t = n + m + 2;

        for (int i = 1; i <= n; i++) {
            add_edge(s, i, 1);
            add_edge(i, s, 0);
        }

        for (int i = n + 1; i <= n + m; i++) {
            add_edge(i, t, 1);          // 多重匹配的话，改为该点的最多匹配次数
            add_edge(t, i, 0);
        }
    }

    bool bfs() {
        for (int i = 1; i <= n + m + 2; i++)
            depth[i] = 0;

        depth[s] = 1;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == t)
                return true;

            for (int i = head[u]; i; i = edge[i].nxt) {
                int v = edge[i].to;

                if (edge[i].w && !depth[v]) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }

        return false;
    }

    int dfs(int u, int contr) {
        if (u == t)
            return contr;

        int sum = 0;

        for (int i = cur[u]; i && contr; i = edge[i].nxt) {
            cur[u] = i;  //当前弧剪枝
            int v = edge[i].to;

            if (edge[i].w && depth[v] == depth[u] + 1) {
                int d = dfs(v, min(contr, edge[i].w));

                if (d > 0) {
                    if (v != t && u != s)  //可以匹配
                        match[u] = v;

                    edge[i].w -= d;
                    edge[i ^ 1].w += d;
                    contr -= d;
                    sum += d;
                } else
                    depth[v] = 0;  //最优化剪枝
            }
        }

        return sum;
    }

    int dinic() {
        int ans = 0;

        while (bfs()) {
            for (int i = 1; i <= n + m + 2; i++)
                cur[i] = head[i];

            ans += dfs(s, INF);
        }

        return ans;
    }
} fff;

int main() {
    int n, m, e;
    cin >> n >> m >> e;
    fff.init(n, m);

    while (e--) {
        int u, v;
        cin >> u >> v;
        v = n + v;
        fff.add_edge(u, v, 1);
        fff.add_edge(v, u, 0);
    }

    fff.build();
    cout << fff.dinic() << endl;
    return 0;
}

/*
4 2 7
3 1
1 2
3 2
1 1
4 2
4 1
1 1

2
*/