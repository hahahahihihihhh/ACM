/*
    牛客 第45届国际大学生程序设计竞赛（ICPC）亚洲区域赛（昆明） M_Stone-Games
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1000005;
const int LIM = 1e9;
#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

int s[MAXN];
int root[MAXN];
struct Node {
    int l, r;
    ll sum;
} node[MAXN * 40];
int tot = 0;

void insert(int l, int r, int pre, int &now, int x) {// 插入一个数
    node[++tot] = node[pre];
    now = tot;
    node[now].sum += x;

    if (l == r)
        return;
    int mid = l + r >> 1;
    if (x <= mid)
        insert(l, mid, node[pre].l, node[now].l, x);
    else
        insert(mid + 1, r, node[pre].r, node[now].r, x);

    return;
}

ll query(int l, int r, int L, int R, ll x) {// 查询 l —— r 区间的数之和
    if (l == r)
        return node[R].sum - node[L].sum;
    int mid = l + r >> 1;
    if (x <= mid)
        return query(l, mid, node[L].l, node[R].l, x);
    else
        return query(mid + 1, r, node[L].r, node[R].r, x) + node[node[R].l].sum - node[node[L].l].sum;
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        insert(1, LIM, root[i - 1], root[i], s[i]);
    }
    ll ans = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if (l > r) swap(l, r);
        ans = 0;
        while (1) {
            ll newans = query(1, LIM, root[l - 1], root[r], ans + 1);
            if (newans == ans)
                break;
            ans = newans;
        }
        cout << ++ans << "\n";
    }
    return;
}

int main() {
    closeSync;
    // int T;cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
5 5
1 4 2 1 6
2 4
1 5
3 5
1 4
3 4

8
15
4
9
4
*/