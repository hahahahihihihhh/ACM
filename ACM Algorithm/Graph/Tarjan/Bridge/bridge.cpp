/*
    Leetcode 1192 查找集群内的「关键连接」
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 100010;
//桥 —— 无向图中，某条边去掉后，图不再连通，这条边称之为桥。
vector<pii> ans;  // 存桥
int dfn[MAXN], low[MAXN];
int tme = 0;
vector<int> mp[MAXN];

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++tme;

    for (auto v: mp[u]) {
        if (v == fa)
            continue;

        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[v], low[u]);

            if (low[v] > dfn[u])
                ans.push_back(make_pair(u, v));
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
        if (!dfn[i])
            tarjan(0, 0);

    for (auto c: ans)
        cout << c.first << " " << c.second << "\n";

    return 0;
}

/*
6 7
0 1
1 2
1 3
1 4
2 3
3 4
3 5

3 5
0 1
*/