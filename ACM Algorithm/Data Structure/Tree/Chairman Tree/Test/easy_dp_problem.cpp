/*
    ZOJ 2020浙江省省赛 E_Easy-DP-Problem
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
typedef long long ll;

struct CT {
    struct Node {
        int l, r;
        int sumN;
        ll sumV;
    } node[MAXN * 40];
    int root[MAXN], a[MAXN];
    int cnt;
    vector<int> v;

    inline void clear(int n) {
        v.clear(), v.resize(0);

        for (int i = 1; i <= n; i++)
            root[i] = 0;

        for (int i = 0; i <= cnt; i++)
            node[i].l = node[i].r = node[i].sumN = node[i].sumV = 0;

        cnt = 0;
    }
    inline void init() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    inline void add(int id, int x) {
        a[id] = x, v.push_back(x);
    }
    inline int discr(int x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
    void insert(int l, int r, int pre, int &now, int x) {
        node[++cnt] = node[pre];
        now = cnt;
        node[now].sumN++;
        node[now].sumV += v[x - 1];

        if (l == r)
            return;

        int mid = (l + r) >> 1;

        if (x <= mid)
            insert(l, mid, node[pre].l, node[now].l, x);
        else
            insert(mid + 1, r, node[pre].r, node[now].r, x);
    }
    ll query(int l, int r, int s, int e, int k) {
        // 查询区间前K大和
        if (l == r)
            return k * (node[e].sumV - node[s].sumV) / (node[e].sumN - node[s].sumN);

        int tmp = node[node[e].r].sumN - node[node[s].r].sumN;
        int mid = (l + r) >> 1;

        if (tmp >= k)
            return query(mid + 1, r, node[s].r, node[e].r, k);
        else
            return (node[node[e].r].sumV - node[node[s].r].sumV) + query(l, mid, node[s].l, node[e].l, k - tmp);
    }
} fff;

ll fst[MAXN];
inline void init0(int n) {
    for (int i = 1; i <= n; i++)
        fst[i] = (ll) i * i + fst[i - 1];
}

void solve() {
    int n, q;
    cin >> n;
    fff.clear(n);

    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        fff.add(i, tmp);
    }

    fff.init();

    for (int i = 1; i <= n; i++)
        fff.insert(1, n, fff.root[i - 1], fff.root[i], fff.discr(fff.a[i]));

    cin >> q;

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << fst[r - l + 1] + fff.query(1, n, fff.root[l - 1], fff.root[r], k) << endl;
    }
}

int main() {
    init0(MAXN - 2);
    int T;
    cin >> T;

    while (T--)
        solve();
}

/*
1
5
1 2 3 4 5
2
1 3 1
1 3 2

17 19
*/