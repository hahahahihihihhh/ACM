/*
    ZOJ The-18th-Zhejiang-Provincial-Collegiate-Programming-Contest D_Shortest-Path-Query
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 100005;
const int LIM = 17;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
const ll INF = 1e18;

struct E {
    int u, v;
    ll w;
};
int cnt = 1;
int ep[MAXN];
vector<int> v[MAXN];
vector<E> e[MAXN];
vector<pli> G[MAXN];
int vis[MAXN];
ll dis[MAXN];
map<pii, ll> mp;
int trie[MAXN][2];

inline void insV(int x) {
    bitset<LIM> X(x);
    int now = 1, stx = -1;
    for (int i = LIM - 1; i >= 0; i--) {
        if (X[i] == 1) {
            stx = i;
            break;
        }
    }
    for (int i = stx; i >= 0; i--) {
        if (trie[now][X[i]]) now = trie[now][X[i]];
        else {
            trie[now][X[i]] = ++cnt;
            now = cnt;
        }
        v[now].push_back(x);
    }
    ep[now] = x;
}

inline void insE(E eg) {
    bitset<LIM> X(eg.u), Y(eg.v); // u < v
    int now = 1, stx = -1, sty = -1;
    for (int i = LIM - 1; i >= 0; i--) {
        if (X[i] == 1) {
            stx = i;
            break;
        }
    }
    for (int i = LIM - 1; i >= 0; i--) {
        if (Y[i] == 1) {
            sty = i;
            break;
        }
    }
    while (stx >= 0 && sty >= 0) {
        if (X[stx] != Y[sty]) break;
        now = trie[now][X[stx]];
        e[now].push_back(eg);
        stx--, sty--;
    }
}

inline void dij(int i) {
    if (!ep[i]) return;
    for (auto c : v[i]) {
        dis[c] = INF;
    }
    for (auto c : e[i]) {
        G[c.u].push_back({c.w, c.v});
        G[c.v].push_back({c.w, c.u});
    }
    priority_queue<pli, vector<pli>, greater<pli>> q;
    int st = ep[i];
    dis[st] = 0;
    q.push({dis[st], st});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto c : G[u]) {
            int v = c.second;
            ll w = c.first;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
    for (auto c : v[i]) {
        mp[{st, c}] = dis[c];
        dis[c] = 0;
        vis[c] = 0;
        G[c].clear(), G[c].resize(0);
    }
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[1].push_back({u, v, w});
    }

    for (int i = 1; i <= n; i++)
        insV(i);

    for (int i = 1; i <= m; i++)
        insE(e[1][i - 1]);

    for (int i = 2; i <= cnt; i++)
        dij(i);

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        bitset<LIM> X(u), Y(v);
        int stx = 0, sty = 0;
        for (int i = LIM - 1; i >= 0; i--) {
            if (X[i] == 1) {
                stx = i;
                break;
            }
        }
        for (int i = LIM - 1; i >= 0; i--) {
            if (Y[i] == 1) {
                sty = i;
                break;
            }
        }
        int ca = 0;
        ll ans = INF;
        while (stx >= 0 && sty >= 0) {
            if (X[stx] != Y[sty]) break;
            ca = ca * 2 + X[stx];
            ans = min(ans, mp[{ca, u}] + mp[{ca, v}]);
            stx--, sty--;
        }
        cout << (ans >= INF ? -1 : ans) << "\n";
    }
}

int main() {
    closeSync;
    // init();
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
5 6
1 2 4
1 3 2
1 4 5
1 5 8
2 4 3
2 5 2
4
2 3
1 4
1 5
4 5

6
5
6
5

3 1
1 2 100
3
1 2
1 3
2 3

100
-1
-1
*/