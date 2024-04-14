/*
    洛谷 P3387 【模板】缩点
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

struct SP {
    int n, cnt, tme, tot;
    int dfn[MAXN], low[MAXN], instack[MAXN], stk[MAXN], scc[MAXN];
    ll w[MAXN], ww[MAXN], dp[MAXN];  // 点权
    int degree[MAXN];
    vector<int> mp[MAXN];
    vector<int> newmp[MAXN];

    void init(int _n) {
        cnt = tme = tot = 0;
        n = _n;

        for (int i = 1; i <= n; i++)
            degree[i] = dp[i] = ww[i] = dfn[i] = low[i] = instack[i] = stk[i] = scc[i] = 0;
    }

    inline void add_edge(int u, int v) {
        mp[u].push_back(v);
    }

    void tarjan(int u) {
        low[u] = dfn[u] = ++tme;
        instack[u] = 1;
        stk[++tot] = u;

        for (auto v: mp[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            int cur;
            cnt++;

            do {
                cur = stk[tot--];
                instack[cur] = 0;
                scc[cur] = cnt;
            } while (cur != u);
        }
    }

    void shrink_point() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);

        for (int i = 1; i <= n; i++) {
            int u = i;

            for (auto v: mp[i]) {
                if (scc[u] != scc[v]) {
                    newmp[scc[u]].push_back(scc[v]);
                    degree[scc[v]]++;
                }
            }

            ww[scc[u]] += w[u];
        }
    }

    int tpSort() {
        queue<int> q;

        for (int i = 1; i <= cnt; i++)
            if (!degree[i]) {
                q.push(i);
                dp[i] = ww[i];
            }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto v: newmp[u]) {
                degree[v]--;
                dp[v] = max(dp[v], dp[u] + ww[v]);

                if (!degree[v]) {
                    q.push(v);
                }
            }
        }

        ll ans = 0;

        for (int i = 1; i <= n; i++)
            ans = max(ans, dp[i]);

        return ans;
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;
    fff.init(n);

    for (int i = 1; i <= n; i++) {
        cin >> fff.w[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        fff.add_edge(u, v);
    }

    fff.shrink_point();
    cout << fff.tpSort() << endl;
    return 0;
}

/*
2 2
1 1
1 2
2 1

2
*/