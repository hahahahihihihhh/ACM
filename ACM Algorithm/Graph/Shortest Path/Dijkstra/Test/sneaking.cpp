/*
    Atcoder ZONe-Energy-Programming-Contest E_Sneaking
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
const int MAXN = 505;
const ll INF = 1e18;
typedef pair<ll, int> pli;

int r, c;
int A[MAXN][MAXN], B[MAXN][MAXN];
ll dis[MAXN * MAXN];
int vis[MAXN * MAXN];
int pre[MAXN * MAXN];
vector<pli> G[MAXN * MAXN];

inline int getid(int x, int y) {
    return (x - 1) * (c) + (y - 1);
}

inline void dij(int st) {
    pre[st] = -1;
    for (int i = 0; i <= r * c; i++)
        vis[i] = 0, dis[i] = INF;
    priority_queue<pli, vector<pli>, greater<pli>> q;
    dis[st] = 0;
    q.push({dis[st], st});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto c: G[u]) {
            int v = c.second;
            ll w = c.first;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                q.push({dis[v], v});
            }
        }
        if (pre[u] > u && (pre[u] - u) % c == 0) continue;
        ll w = 2;
        for (int v = u - c; v >= 0; v -= c, w++) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                q.push({dis[v], v});
            }
        }
    }
}

inline void solve() {
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c - 1; j++) {
            cin >> A[i][j];
            int u = getid(i, j), v = getid(i, j + 1);
            G[u].push_back({A[i][j], v});
            G[v].push_back({A[i][j], u});
        }
    for (int i = 1; i <= r - 1; i++)
        for (int j = 1; j <= c; j++) {
            cin >> B[i][j];
            int u = getid(i, j), v = getid(i + 1, j);
            G[u].push_back({B[i][j], v});
        }
    dij(getid(1, 1));
    cout << dis[getid(r, c)] << "\n";
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
7 11
42 77 94 76 40 66 43 28 66 23
27 34 41 31 83 13 64 69 81 82
23 81 0 22 39 51 4 37 84 43
62 37 82 86 26 67 45 78 85 2
79 18 72 62 68 84 69 88 19 48
0 27 21 51 71 13 87 45 39 11
74 57 32 0 97 41 87 96 17 98
69 58 76 32 51 16 38 68 86 82 64
53 47 33 7 51 75 43 14 96 86 70
80 58 12 76 94 50 59 2 1 54 25
14 14 62 28 12 43 15 70 65 44 41
56 50 50 54 53 34 16 3 2 59 88
27 85 50 79 48 86 27 81 78 78 64

498
*/