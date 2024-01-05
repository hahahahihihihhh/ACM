/*
    Atcoder abc197 F_construct-a-palindrome
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 1005;
const int LIM = 30;

map<pii, int> mp;
int n, m;
vector<int> G[MAXN][LIM];
struct Node {
    int u, v;
    int stp;
};
int vis[MAXN][MAXN];
int ans = INF;

inline void bfs(int st, int ed) {// 双向 BFS
    queue<Node> q;
    q.push({st, ed, 0});
    vis[st][ed] = vis[ed][st] = 1;
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        int u = cur.u, v = cur.v;
        if (mp.count({u, v})) {
            ans = min(ans, cur.stp + (u != v));
            continue;
        }
        for (int i = 0; i <= 'z' - 'a'; i++) {
            for (auto uu : G[u][i]) {
                for (auto vv : G[v][i]) {
                    if (vis[uu][vv] == 0) {
                        vis[uu][vv] = vis[vv][uu] = 1;
                        q.push({uu, vv, cur.stp + 2});
                    }
                }
            }
        }
    }
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        G[u][c - 'a'].push_back(v);
        G[v][c - 'a'].push_back(u);
        mp[{u, v}] = mp[{v, u}] = 1;
    }
    for (int i = 1; i <= n; i++)
        mp[{i, i}] = 1;

    bfs(1, n);
    cout << (ans == INF ? -1 : ans) << endl;

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
8 8
1 2 a
2 3 b
1 3 c
3 4 b
4 5 a
5 6 c
6 7 b
7 8 a

10
*/

