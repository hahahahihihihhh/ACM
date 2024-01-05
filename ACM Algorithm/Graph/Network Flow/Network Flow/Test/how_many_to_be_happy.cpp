/*
    牛客 2021年度训练联盟热身训练赛第四场 E_How-Many-to-Be-Happy?
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const ll INF = 1e18;
const int MAXN = 105;
const int MAXM = 505;

struct E {
    int u, v;
    ll w;
    bool operator<(const E &x) const { return w < x.w; }
} e[MAXM];

struct NF {
    struct Edge {
        int to;
        ll w;
        int nxt;
    } edge[MAXM << 2];
    int head[MAXN], tot = 1;
    int depth[MAXN], cur[MAXN];
    int n, s, t;

    void init(int _n, int _s, int _t) {  //初始化
        n = _n, s = _s, t = _t;
        tot = 1;
        for (int i = 1; i <= n; i++) head[i] = 0;
    }
    void add_edge(int u, int v, ll w) {  //加边
        edge[++tot].to = v;
        edge[tot].w = w;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
    bool bfs() {  //分层
        for (int i = 1; i <= n; i++) depth[i] = 0;
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
    ll dfs(int u, ll dist)  // dist: 该条路径当前最大允许流量
    {
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
            for (int i = 1; i <= n; i++) cur[i] = head[i];
            ans += dfs(s, INF);
        }
        return ans;
    }

} fff;

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    sort(e + 1, e + m + 1);
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        fff.init(n, e[i].u, e[i].v);
        for (int j = 1; e[j].w < e[i].w; j++) {
            fff.add_edge(e[j].u, e[j].v, 1);
            fff.add_edge(e[j].v, e[j].u, 0);
            fff.add_edge(e[j].v, e[j].u, 1);
            fff.add_edge(e[j].u, e[j].v, 0);
        }
        ans += fff.dinic();
    }
    cout << ans << "\n";
    return;
}

int main() {
    closeSync;
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
7 9 
1 2 8 
1 3 3 
2 3 6 
4 2 7 
4 5 1 
5 6 9 
6 7 3 
7 4 2 
4 6 2

3

4 4
1 2 1
2 3 1
3 4 1
1 4 1

0
*/

