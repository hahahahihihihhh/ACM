/*
    洛谷 P3385 【模板】负环
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 10005;
const ll INF = 1e18;

struct SPFA {
    struct Edge {
        int to;
        ll w;
        int nxt;
    } edge[MAXN << 1];
    int n;
    int head[MAXN], tot = 1;
    ll dis[MAXN];
    int inq[MAXN], circle[MAXN];

    inline void add_edge(int u, int v, ll w) {
        edge[++tot].to = v;
        edge[tot].w = w;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
    void init(int _n) {
        n = _n;
        tot = 1;

        for (int i = 1; i <= n; i++)
            dis[i] = INF, inq[i] = circle[i] = head[i] = 0;
    }
    bool spfa(int st) {        //  spfa的队列优化算法，注：可以有负权，判负环，数据量大时比dij慢
        queue<int> q;
        dis[st] = 0;
        q.push(st);
        circle[st] = 1;
        inq[st] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;

            for (int i = head[u]; i; i = edge[i].nxt) {
                int v = edge[i].to;

                if (dis[u] + edge[i].w < dis[v]) {
                    dis[v] = dis[u] + edge[i].w;

                    if (!inq[v]) {
                        circle[v] = circle[u] + 1;

                        if (circle[v] > n) {
                            return true;
                        }

                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }

        return false;
    }

} fff;

void solve() {
    int n, m;
    cin >> n >> m;
    fff.init(n);

    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        fff.add_edge(u, v, w);

        if (w >= 0)
            fff.add_edge(v, u, w);
    }

    if (fff.spfa(1))
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}

/*
2
3 4
1 2 2
1 3 4
2 3 1
3 1 -3
3 3
1 2 3
2 3 4
3 1 -8

NO
YES
*/
