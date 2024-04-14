/*
    洛谷 P3366 【模板】最小生成树
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;
const ll INF = 1e18;

struct Kruskal {
    struct Edge {
        int u, v;
        ll w;

        bool operator<(const Edge &x) const {
            return w > x.w;
        }
    };

    int n;
    priority_queue<Edge> q;
    int fa[MAXN], rnk[MAXN];

    inline void init(int _n) {
        n = _n;
        q = {};

        for (int i = 1; i <= n; i++)
            fa[i] = i, rnk[i] = 0;
    }

    inline int tfind(int x) {
        return fa[x] = x == fa[x] ? x : tfind(fa[x]);
    }

    inline void tunion(int x, int y) {
        int xf = tfind(x), yf = tfind(y);

        if (rnk[xf] < rnk[yf]) {
            fa[xf] = yf;
        } else {
            if (rnk[xf] == rnk[yf])
                rnk[xf]++;

            fa[yf] = xf;
        }
    }

    inline ll kruskal() {
        int cnt = 0;
        ll ans = 0;

        while (!q.empty()) {
            Edge cur = q.top();
            q.pop();

            if (tfind(cur.u) != tfind(cur.v)) {
                tunion(cur.u, cur.v);
                cnt++;
                ans += cur.w;
            }

            if (cnt == n - 1)
                break;
        }

        return cnt == n - 1 ? ans : INF;
    }

} fff;

int main() {
    int n, m;
    cin >> n >> m;
    fff.init(n);

    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        fff.q.push({u, v, w});
    }

    ll ans = fff.kruskal();

    if (ans == INF)
        cout << "orz\n";
    else
        cout << ans << "\n";

    return 0;
}

/*
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3

7
*/