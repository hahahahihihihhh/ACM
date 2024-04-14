/*
    洛谷 P3376 【模板】网络最大流（一般图：O(n^2m)，二分图：O(m*sqrt(n))）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 205;
const int MAXM = 5005;
const ll INF = 1e18;

struct NF {
    struct Edge {
        int to;
        ll w;
        int nxt;
    } edge[MAXM << 1];
    int head[MAXN], tot = 1;
    int depth[MAXN], cur[MAXN];
    int n, s, t;

    void init(int _n, int _s, int _t) {  //初始化
        n = _n, s = _s, t = _t;
    }

    void add_edge(int u, int v, ll w) {  //加边
        edge[++tot].to = v;
        edge[tot].w = w;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }

    bool bfs() {  //分层
        for (int i = 1; i <= n; i++)
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

                if (edge[i].w > 0 && !depth[v]) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }

        return false;
    }

    ll dfs(int u, ll dist) { // dist: 该条路径当前最大允许流量
        if (u == t)
            return dist;  //到达汇点后，成功流出流量即是该条路径最大允许流量

        ll sum = 0;

        for (int i = cur[u]; i && dist; i = edge[i].nxt) {  //多方向增广
            cur[u] = i;                                     //当前弧优化
            int v = edge[i].to;

            if (depth[v] == depth[u] + 1 && edge[i].w) {  //可以往下增广
                int d = dfs(v, min(dist, edge[i].w));

                if (d == 0)
                    depth[v] = 0;  //增广失败，删除该点

                edge[i].w -= d;    //增广成功
                edge[i ^ 1].w += d;
                sum += d;   //成功流出的流量增加
                dist -= d;  //最大允许流量减少
            }
        }

        return sum;  //成功流出的流量总和
    }

    ll dinic() {
        ll ans = 0;

        while (bfs()) {
            for (int i = 1; i <= n; i++)
                cur[i] = head[i];

            ans += dfs(s, INF);
        }

        return ans;
    }

} fff;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    fff.init(n, s, t);

    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        fff.add_edge(u, v, w);
        fff.add_edge(v, u, 0);
    }

    cout << fff.dinic() << endl;
    return 0;
}

/*
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40

50
*/