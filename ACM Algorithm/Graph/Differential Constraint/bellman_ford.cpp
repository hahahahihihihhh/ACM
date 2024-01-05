/*
    P5960 【模板】差分约束算法（Bellman_Ford实现 O(n*m)，常数小）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, w;
} E[MAXN];
int dist[MAXN];
int n, m;

inline bool bellman_ford(int st) {
    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    dist[st] = 0;

    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m; j++)
            dist[E[j].v] = min(dist[E[j].v], dist[E[j].u] + E[j].w);

    for (int j = 1; j <= m; j++)
        if (dist[E[j].v] > dist[E[j].u] + E[j].w)
            return false;

    return true;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++)        // Eu - Ev <= Ew
        cin >> E[i].v >> E[i].u >> E[i].w;

    if (bellman_ford(1)) {
        for (int i = 1; i <= n; i++)
            cout << dist[i] << (i == n ? "\n" : " ");

        return 0;
    }

    cout << "NO\n";
    return 0;
}

/*
3 3
1 2 3
2 3 -2
1 3 1

0 1061109565 1061109567
*/
