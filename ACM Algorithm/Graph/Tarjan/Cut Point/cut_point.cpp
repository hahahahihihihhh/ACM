/*
    洛谷 P3388 【模板】割点（割顶）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
//割点 —— 无向图（有向图也可但算法不一样）中，删去某一点后图G（V，E）被划分为两个及以上的子图，则称该点为割点
int cut[MAXN], dfn[MAXN], low[MAXN];  // cut[i] == 1 , 是割点
int tme, root;
vector<int> mp[MAXN];

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++tme;
    int flag = 0;

    for (auto v: mp[u]) {
        if (v == fa)
            continue;

        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u] && (u != root || ++flag != 1))
                cut[u] = 1;
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            root = i, tarjan(i, 0);

    int ans = 0;

    for (int i = 1; i <= n; i++)
        if (cut[i])
            ans++;

    cout << ans << "\n";

    for (int i = 1; i <= n; i++)
        if (cut[i])
            cout << i << " ";

    cout << "\n";
    return 0;
}

/*
6 7
1 2
1 3
1 4
2 5
3 5
4 5
5 6

1
5
*/