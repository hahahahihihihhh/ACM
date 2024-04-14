/*
    洛谷 P5960 【模板】差分约束算法（SPFA实现，O(n*m)）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;

vector<pii> G[MAXN];
int dist[MAXN], inq[MAXN], cnt[MAXN];
int n, m;

bool spfa(int st) {
    queue<int> q;

    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    q.push(st);
    dist[st] = 0, inq[st] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;

        for (auto [v, w]: G[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                if (!inq[v]) {
                    q.push(v);
                    cnt[v]++, inq[v] = 1;

                    if (cnt[v] == n + 1)
                        return false;
                }
            }
        }
    }

    return true;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int v, u, w;
        cin >> v >> u >> w;         // Eu - Ev <= Ew 
        G[u].emplace_back(v, w);
    }

    for (int i = 1; i <= n; i++)
        G[0].emplace_back(i, 0);

    if (!spfa(0)) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cout << dist[i] << (i == n ? "\n" : " ");

    return 0;
}

/*
3 3
1 2 3
2 3 -2
1 3 1

0 -2 0
*/