/*
    洛谷 P3381 【模板】最小费用最大流（O(n*m*k)，k为最大流）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 5005;
const int MAXM = 50005;
const ll INF = 1e18;

struct MCMF {
    int n, s, t;
    ll maxFlow, minCost;
    int head[MAXN], tot = 1;
    int last[MAXN], pre[MAXN], inq[MAXN];
    ll flow[MAXN], dis[MAXN];
    struct Edge {
        int to;
        ll flow;
        ll cost;
        int nxt;
    } edge[MAXM << 1];
    void add_edge(int u, int v, ll f, ll c) {
        edge[++tot].to = v;
        edge[tot].flow = f;
        edge[tot].cost = c;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
    void init(int _n, int _s, int _t) { //点数，边数，源点，汇点
        n = _n, s = _s, t = _t;
        maxFlow = minCost = 0LL;
    }
    bool spfa(int s, int t) {
        for (int i = 1; i <= n; i++)  //以cost为边权寻找最短增广路
            flow[i] = dis[i] = INF;

        queue<int> q;
        q.push(s);
        dis[s] = 0, inq[s] = 1, pre[t] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;

            for (int i = head[u]; i; i = edge[i].nxt) {
                int v = edge[i].to;

                if (edge[i].flow > 0 && dis[v] > dis[u] + edge[i].cost) {  //成功找到增广路
                    dis[v] = dis[u] + edge[i].cost;
                    flow[v] = min(flow[u], edge[i].flow);
                    pre[v] = u;   //记录该点的上一个点，方便回溯。
                    last[v] = i;  //记录该点的上一条边，方便回溯

                    if (!inq[v]) {
                        inq[v] = 1;
                        q.push(v);
                    }
                }
            }
        }

        return pre[t] != -1;
    }
    void dinic() {
        while (spfa(s, t)) {
            int now = t;
            maxFlow += flow[t];           //最大流增加
            minCost += flow[t] * dis[t];  //最小费用 = 流量 * 单位时间最小的流量费用

            while (now != s) {            //回溯，构建残量网络
                edge[last[now]].flow -= flow[t];
                edge[last[now] ^ 1].flow += flow[t];
                now = pre[now];
            }
        }
    }
} fff;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    fff.init(n, s, t);

    for (int i = 1; i <= m; i++) {
        int u, v, f, c;
        cin >> u >> v >> f >> c;
        fff.add_edge(u, v, f, c);
        fff.add_edge(v, u, 0, -c);
    }

    fff.dinic();
    cout << fff.maxFlow << " " << fff.minCost << endl;
    return 0;
}

/*
4 5 4 3
4 2 30 2
4 3 20 3
2 3 20 1
2 1 30 9
1 3 40 5

50 280
*/
