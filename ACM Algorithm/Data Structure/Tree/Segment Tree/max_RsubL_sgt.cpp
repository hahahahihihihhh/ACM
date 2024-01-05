/*
    牛客 2021年度训练联盟热身训练赛3 L_Traveling-Merchant（线段树查询区间 l - r 中 max(a[y] - a[x]),min(a[y] - a[x]), (l <= x <= y <= r)）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int DATE = 7;
typedef long long ll;

struct Node {
    int l, r;
    ll allmax;
    ll allmin;
    ll submax;
    ll submin;
} node[DATE + 5][MAXN << 2];

ll a[DATE + 5][MAXN];
ll v[MAXN], d[MAXN];
int sign[DATE + 5] = {0, 1, 2, 3, 2, 1, 0};

inline Node uni(Node l, Node r) {
    Node ans;
    ans.l = l.l, ans.r = r.r;
    ans.allmax = max(l.allmax, r.allmax);
    ans.allmin = min(l.allmin, r.allmin);
    ans.submax = max({l.submax, r.submax, r.allmax - l.allmin});
    ans.submin = min({l.submin, r.submin, r.allmin - l.allmax});
    return ans;
}

void build(int day, int l, int r, int rt = 1) {
    node[day][rt].l = l;
    node[day][rt].r = r;

    if (l == r) {
        node[day][rt].allmax = node[day][rt].allmin = a[day][l];
        node[day][rt].submax = 0;
        node[day][rt].submin = 0;
        return;
    }

    int ls = rt << 1, rs = rt << 1 | 1;
    int mid = (l + r) >> 1;
    build(day, l, mid, ls);
    build(day, mid + 1, r, rs);
    node[day][rt] = uni(node[day][ls], node[day][rs]);
}

Node query(int day, int l, int r, int rt = 1) {
    if (l <= node[day][rt].l && node[day][rt].r <= r)
        return node[day][rt];

    int ls = rt << 1, rs = rt << 1 | 1;

    if (l > node[day][ls].r)
        return query(day, l, r, rs);

    if (r < node[day][rs].l)
        return query(day, l, r, ls);

    return uni(query(day, l, r, ls), query(day, l, r, rs));

}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> v[i] >> d[i];

    for (int day = 0; day < DATE; day++) {
        for (int i = 1; i <= n; i++) {
            // 第一个是星期day 的情况下
            a[day][i] = v[i] + sign[((i - 1) % 7 + day) % 7] * d[i];
        }

        build(day, 1, n);
    }

    int q;
    cin >> q;

    for (int i = 1; i <= q; i++) {
        int s, t;
        cin >> s >> t;
        int day = (-((s - 1) % 7) + 7) % 7;
        ll ans = 0;

        if (s < t)
            ans = query(day, s, t).submax;
        else {
            day = (day + 6) % 7;
            ans = -query(day, t, s).submin;
        }

        cout << ans << "\n";
    }

    return 0;
}

/*
5
1 2
2 1
5 0
4 -1
7 -2
5
1 5
5 1
3 1
4 5
5 4

4
2
2
1
0
*/