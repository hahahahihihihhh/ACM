/*
    洛谷 P3386 【模板】二分图最大匹配（O(n*e+m)）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXM = 50005;

struct Edge {
    int to, nxt;
} edge[MAXM];
int tot = 1, head[MAXN];
int vis[MAXN], match[MAXN];

inline void add_edge(int u, int v) {
    edge[++tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot;
}

bool Hungary(int u, int tag) {
    //二分图最大匹配（匈牙利算法）
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;

        if (vis[v] == tag)
            continue;               //保证一次递归过程中对象只能被访问一次

        vis[v] = tag;

        if (!match[v] ||
            Hungary(match[v], tag)) { //对象没有被匹配，或者是将要匹配的对象的原配可以有其他匹配
            match[v] = u;      //匹配成功
            return true;
        }
    }

    return false;       //没有匹配成功
}

int main() {
    int n, m, e;
    cin >> n >> m >> e;

    for (int i = 1; i <= e; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    int ans = 0;

    for (int i = 1; i <= n; i++)        //暴力枚举左部点，去与右部点形成匹配
        ans += Hungary(i, i);

    cout << ans << endl;
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