/*
    洛谷 P3379 【模板】最近公共祖先（LCA）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int LIM = 20;

struct ML {
    int dep[MAXN];
    int f[MAXN][LIM + 5];  // f[i][j] i头上的第2^j个父亲
    int head[MAXN], tot = 1;
    struct Edge {
        int to;
        int nxt;
    } Edge[MAXN << 1];

    void add_edge(int x, int y) {  // x->y 链式前向星
        Edge[++tot].to = y;
        Edge[tot].nxt = head[x];
        head[x] = tot;
    }
    void dfs(int u, int fa) {  //求每个点的深度，并打f表
        //前序遍历
        dep[u] = dep[fa] + 1;
        f[u][0] = fa;
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int i = head[u]; i; i = Edge[i].nxt) {
            int v = Edge[i].to;
            if (v == fa)  //双向变单向
                continue;
            dfs(v, u);
        }
    }
    void init(int s) { dfs(s, 0); }
    int lca(int x, int y) {
        if (dep[x] < dep[y])
            swap(x, y);
        for (int i = LIM; i >= 0; i--) {  // x跳到与y同一层，特判跳到同一个点
            if (dep[f[x][i]] >= dep[y])
                x = f[x][i];
            if (x == y)  // x是y的儿子
                return x;
        }
        for (int i = LIM; i >= 0; i--) {  // x,y一起跳，且不能相遇
            if (f[x][i] != f[y][i]) {
                x = f[x][i];
                y = f[y][i];
            }
        }
        return f[x][0];
    }
} fff;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= n - 1; i++) {
        //树
        int u, v;
        cin >> u >> v;
        fff.add_edge(u, v);
        fff.add_edge(v, u);
    }
    fff.init(s);
    for (int i = 1; i <= m; i++) {
        //在线
        int u, v;
        cin >> u >> v;
        cout << fff.lca(u, v) << endl;
    }
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