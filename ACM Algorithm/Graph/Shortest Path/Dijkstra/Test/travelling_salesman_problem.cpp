/*
    Codeforces Round712 E_Travelling-Salesman-Problem
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const int MAXN = 100005;
const ll INF = 1e18;
#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

pll cp[MAXN];

struct E {
    int to;
    ll w;

    bool operator<(const E &x) const {
        return w > x.w;
    }
};

int n;
int vis[MAXN];
ll dis[MAXN];

inline void dij(int st) {
    for (int i = 1; i <= n; i++) dis[i] = INF;
    priority_queue<E> q;
    q.push({st, 0});
    dis[st] = 0;
    while (!q.empty()) {
        int u = q.top().to;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        if (u > 1 && dis[u - 1] > dis[u]) {
            dis[u - 1] = dis[u];
            q.push({u - 1, dis[u - 1]});
        }
        int v = lower_bound(cp + 1, cp + n + 1, make_pair(cp[u].first + cp[u].second, INF)) - cp - 1;
        if (v >= 1 && dis[v] > dis[u]) {
            dis[v] = dis[u];
            q.push({v, dis[v]});
        }
        ll cst = cp[v + 1].first - cp[u].first - cp[u].second;
        if (v + 1 <= n && dis[v + 1] > dis[u] + cst) {
            dis[v + 1] = dis[u] + cst;
            q.push({v + 1, dis[v + 1]});
        }
    }
    return;
}

inline void solve() {
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> cp[i].first >> cp[i].second;
        ans += cp[i].second;
    }
    sort(cp + 1, cp + n + 1);
    dij(1);

    cout << (ans + dis[n]) << "\n";
    return;
}

int main() {
    closeSync;
    // int T;
    // cin >> T;
    // while (T--)
    solve();

    return 0;
}

/*
6
4 2
8 4
3 0
2 3
7 1
0 1

13
*/