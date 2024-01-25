/*
    洛谷 P6577 【模板】二分图最大权完美匹配（O(n^3)）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 505;
const ll INF = 1e18;

struct KM {
    int n;
    bool vx[MAXN], vy[MAXN];
    ll d[MAXN];
    int matchx[MAXN], matchy[MAXN], pre[MAXN];
    ll lx[MAXN], ly[MAXN];
    ll w[MAXN][MAXN];
    queue<int> q;

    KM(int _n) {
        n = _n;
        for (int x = 1; x <= n; x++) for (int y = 1; y <= n; y++) w[x][y] = -INF;
    }

    inline void add_edge(int x, int y, ll v) {
        w[x][y] = max(w[x][y], v);
    }

    inline bool check(int y) {
        vy[y] = true;
        if (matchy[y]) {
            vx[matchy[y]] = true;
            q.push(matchy[y]);
            return false;
        }
        while (y) {
            matchy[y] = pre[y];
            swap(y, matchx[pre[y]]);
        }
        return true;
    }

    inline void bfs(int st) {
        while (!q.empty()) q.pop();
        vx[st] = true;
        q.push(st);
        while (true) {
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int y = 1; y <= n; y++) {
                    if (!vy[y]) {
                        if (d[y] >= lx[x] + ly[y] - w[x][y])
                            pre[y] = x;
                        if (lx[x] + ly[y] - w[x][y] == 0 && check(y))
                            return;
                        else if (lx[x] + ly[y] - w[x][y] <= d[y])
                            d[y] = lx[x] + ly[y] - w[x][y];
                    }
                }
            }
            ll delta = INF;
            for (int y = 1; y <= n; y++)
                if (!vy[y])
                    delta = min(delta, d[y]);
            for (int i = 1; i <= n; i++) {
                if (vx[i]) lx[i] -= delta;
                if (vy[i]) ly[i] += delta;
                else d[i] -= delta;
            }
            for (int y = 1; y <= n; y++)
                if (!vy[y] && d[y] == 0 && check(y))
                    return;
        }
    }

    inline ll solve() {
        for (int i = 1; i <= n; i++) {
            ll mx = -INF;
            for (int j = 1; j <= n; j++)
                mx = max(mx, w[i][j]);
            lx[i] = mx;
        }
        for (int x = 1; x <= n; x++) {
            memset(vx, 0, sizeof vx);
            memset(vy, 0, sizeof vy);
            for (int y = 1; y <= n; y++) d[y] = INF;
            bfs(x);
        }

        ll ans = 0;
        for (int x = 1; x <= n; x++)
            ans += w[x][matchx[x]];
        return ans;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    KM fff(n);
    for (int i = 1; i <= m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        fff.add_edge(a, b, w);
    }
    cout << fff.solve() << "\n";
    for (int y = 1; y <= n; y++) cout << fff.matchy[y] << (y == n ? "\n" : " ");
    return 0;
}

/*
5 7
5 1 19980600
4 2 19980587
1 3 19980635
3 4 19980559
2 5 19980626
1 2 -15484297
4 5 -17558732

99903007
5 4 1 3 2
*/