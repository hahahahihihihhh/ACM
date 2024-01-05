/*
	牛客 牛客练习赛47 E_DongDong数颜色（求区间内不同数的个数，树状树组，离线求解）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const int MAXN = 200005;

struct Q {
    int l, r, id;
    bool operator<(const Q &x) const {
        return r < x.r;
    }
} q[MAXN];

struct Edge {
    int to;
    int nxt;
} edge[MAXN << 1];

int head[MAXN], tot = 1;
int c[MAXN];
int in[MAXN], out[MAXN], tme = 0;  // 记录搜入的时间戳与搜出的时间戳
int cc[MAXN], pos[MAXN];
int ans[MAXN];
int n, m;

inline void add_edge(int u, int v) {
    edge[++tot].nxt = head[u];
    edge[tot].to = v;
    head[u] = tot;
}

inline void dfs0(int u, int fa) {
    in[u] = ++tme;
    cc[tme] = c[u];
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs0(v, u);
    }
    out[u] = ++tme;
    cc[tme] = c[u];
}

int t[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int k) {
    int N = n << 1;
    for (; x <= N; x += lowbit(x))
        t[x] += k;
}
inline int ask(int x) {
    int sum = 0;
    for (; x; x -= lowbit(x))
        sum += t[x];
    return sum;
}
inline int query(int l, int r) {
    return ask(r) - ask(l - 1);
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs0(1, 1);

    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        q[i] = {in[x], out[x], i};
    }

    sort(q + 1, q + m + 1);    // 按照右端点进行排序

    int tk = 1;
    for (int i = 1; i <= m; i++) {
        while (tk <= q[i].r) {
            if (pos[cc[tk]])
                add(pos[cc[tk]], -1);
            pos[cc[tk]] = tk;
            add(pos[cc[tk]], 1);
            tk++;
        }
        ans[q[i].id] = query(q[i].l, q[i].r);
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";

    return;
}

int main() {
    closeSync;
//	int T;	cin >> T;
//	while (T--)
    solve();
    return 0;
}

/*
4 3
1 1 2 3
1 2
2 3
1 4
1
2
4

3
2
1
*/ 
