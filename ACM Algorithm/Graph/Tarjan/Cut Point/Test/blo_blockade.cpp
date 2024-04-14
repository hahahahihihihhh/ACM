/*
    洛谷 P3469 [POI2008]BLO-Blockade
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;
const int MAXN = 100005;
vector<int> G[MAXN];
int low[MAXN], dfn[MAXN], siz[MAXN];
ll ans[MAXN];
int tme, root = 1, sons;

void dfs0(int u) {
    siz[u] = 1;
    for (auto v: G[u]) {
        if (siz[v]) continue;
        if (u == root) sons++;
        dfs0(v);
        siz[u] += siz[v];
    }
}

void dfs(int u, int fa = 0) {
    dfn[u] = low[u] = ++tme;
    ans[u] = siz[root] - 1;
    int tmp = 0;
    for (auto v: G[u]) {
        if (v == fa) continue;
        if (!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u == root) {
                if (sons >= 2)
                    ans[u] += (ll) siz[v] * (siz[root] - siz[v] - 1 - tmp), tmp += siz[v];
            } else if (low[v] > dfn[u])
                ans[u] += (ll) siz[v] * (siz[root] - siz[v] - 1 - tmp), tmp += siz[v];
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].emplace_back(y), G[y].emplace_back(x);
    }
    dfs0(root);
    dfs(root);
    for (int i = 1; i <= n; i++)
        cout << (ans[i] << 1) << "\n";
}

int main() {
    closeSync;
//    int T;  cin >> T;
//    while (T--)
    solve();
    return 0;
}

/*
5 5
1 2
2 3
1 3
3 4
4 5

8
8
16
14
8
*/