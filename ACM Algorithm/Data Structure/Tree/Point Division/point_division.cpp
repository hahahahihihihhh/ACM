/*
    洛谷 P3806 【模板】点分治1
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;
const int MAXK = 10000005;

struct Edge {
    int to;
    int w;
    int nxt;
} edge[MAXN << 1];
int n, m;
int q[MAXN], ans[MAXN];
int tot = 1, head[MAXN];
int rt, sum, siz[MAXN], maxp[MAXN];
int dis[MAXN], tmp[MAXN], cnt = 0;
bool vis[MAXN], judge[MAXK];

inline void add_edge(int u, int v, int w) {
    edge[++tot].to = v;
    edge[tot].w = w;
    edge[tot].nxt = head[u];
    head[u] = tot;
}
inline void findrt(int u, int fa) {//找重心（寻找一个节点，使得以该节点为根节点时，其最大子树最小）
    siz[u] = 1, maxp[u] = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa || vis[v]) continue;
        findrt(v, u);
        maxp[u] = max(maxp[u], siz[v]);
        siz[u] += siz[v];
    }
    maxp[u] = max(maxp[u], sum - siz[u]);
    if (maxp[u] < maxp[rt])
        rt = u;
}
inline void getdis(int u, int fa) {//获得以u为子树的所有节点到根节点的距离
    tmp[++cnt] = dis[u];
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (vis[v] || v == fa) continue;
        dis[v] = dis[u] + edge[i].w;
        getdis(v, u);
    }
}
void solve(int u) {//处理根节点
    vector<int> ve;
    for (int i = head[u]; i; i = edge[i].nxt) {
        cnt = 0;    //!! cnt 为计数器
        int v = edge[i].to;
        if (vis[v]) continue;
        dis[v] = edge[i].w;
        getdis(v, u);        //tmp 存储当前v为根节点的子树所能产生的所有距离
        for (int j = 1; j <= cnt; j++)
            for (int k = 1; k <= m; k++)
                if (tmp[j] <= q[k])
                    ans[k] |= judge[q[k] - tmp[j]];//judge[x] 表示之前的子树所产生的到根节点u距离为x的节点是否存在
        for (int j = 1; j <= cnt; j++) {
            if (tmp[j] > MAXK - 5)      //不可能了
                continue;
            judge[tmp[j]] = true;      //目前变之前
            ve.push_back(tmp[j]);      //方便重置 judge
        }
    }
    for (auto c : ve)   //重置 judge
        judge[c] = false;
}
void divide(int u) {//点分治
    vis[u] = judge[0] = true;      //vis[u] 表示u节点是否已经被删除
    solve(u);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (vis[v]) continue;
        maxp[rt = 0] = sum = siz[v];
        findrt(v, 0);
        findrt(rt, 0);
        divide(rt);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= m; i++)
        cin >> q[i];
    maxp[rt = 0] = sum = n;   //初始化
    findrt(1, 0);        //找重心
    findrt(rt, 0);       //更新重心为根节点时其余节点的size
    divide(rt);         //从根节点开始分治
    for (int i = 1; i <= m; i++)
        cout << (ans[i] ? "AYE\n" : "NAY\n");   // ! ans[i]
}
int main() {
    //clock_t c1 = clock();

    solve();

    //cerr << "Time:" << clock() - c1 << "ms" <<endl;
    return 0;
}

/*
2 1
1 2 2
2

AYE
*/