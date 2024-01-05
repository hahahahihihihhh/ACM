/*
	洛谷 P2163 [SHOI2007]园丁的烦恼（二维数点）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 500005;

struct Node {
    int x, y, id, sit;
    bool operator<(const Node &a) const {
        return y < a.y;
    }
} node[MAXN << 2];
int cnt = 0;

struct Tree {
    int x, y;
    bool operator<(const Tree &a) const {
        return y < a.y;
    }
} tree[MAXN];

inline int lowbit(int x) { return x & -x; }

int ans[MAXN];
int t[10000005];
int n, m;
int mx = 0;

inline int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
        res += t[x];
    return res;
}

inline void add(int x) {
    for (; x <= mx; x += lowbit(x))
        t[x]++;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        tree[i] = {x, y};
    }
    sort(tree + 1, tree + n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a++, b++;
        c++, d++;
        node[++cnt] = {a - 1, b - 1, i, 1};
        node[++cnt] = {c, b - 1, i, -1};
        node[++cnt] = {a - 1, d, i, -1};
        node[++cnt] = {c, d, i, 1};
        mx = max(mx, c);
    }
    sort(node + 1, node + cnt + 1);
    int tk = 1;
    for (int i = 1; i <= cnt; i++) {
        while (tk <= n && tree[tk].y <= node[i].y) {
            add(tree[tk].x);
            tk++;
        }
        ans[node[i].id] += node[i].sit * ask(node[i].x);
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";

    return;
}

int main() {
    closeSync;
    solve();
    return 0;
}

/*
3 1
0 0 
0 1
1 0
0 0 1 1

3
*/
 
 