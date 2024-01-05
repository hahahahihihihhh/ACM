/*
    P4779 【模板】单源最短路径（标准版）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;
const int MAXM = 200005;
const ll INF = 1e18;

struct Dij {
    struct Node {
        int to;
        ll w;
        bool operator<(const Node &x) const {
            return w > x.w;
        }
    };
    struct Edge {
        int to;
        ll w;
        int nxt;
    } edge[MAXM];
    int vis[MAXN];
    ll dis[MAXN];
    int head[MAXN], tot = 1;

    inline void add_edge(int u, int v, ll w) {
        edge[++tot].to = v;
        edge[tot].w = w;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
    inline void init(int n) {
        tot = 1;

        for (int i = 1; i <= n; i++)
            head[i] = vis[i] = 0, dis[i] = INF;
    }
    inline void dij(int st) {
        priority_queue<Node> q;
        q.push({st, 0});
        dis[st] = 0;

        while (!q.empty()) {
            int u = q.top().to;
            q.pop();

            if (vis[u])
                continue;

            vis[u] = 1;

            for (int i = head[u]; i; i = edge[i].nxt) {
                int v = edge[i].to;
                ll w = edge[i].w;

                if (dis[v] > w + dis[u]) {
                    dis[v] = w + dis[u];
                    q.push({v, dis[v]});
                }
            }
        }
    }

} fff;

int main() {
    int n, m, st;
    cin >> n >> m >> st;
    fff.init(n);

    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        fff.add_edge(u, v, w);
    }

    fff.dij(st);

    for (int i = 1; i <= n; i++)
        cout << fff.dis[i] << (i == n ? "\n" : " ");

    return 0;
}

/*
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

0 2 4 3
*/