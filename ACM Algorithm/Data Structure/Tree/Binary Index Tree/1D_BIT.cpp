/*
    洛谷 P3372 【模板】线段树1
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
typedef long long ll;

inline int lowbit(int x) { return x & -x; }

struct BIT {
    ll a[MAXN];
    ll t1[MAXN], t2[MAXN];  // 维护区间的增量 (t1 维护t[i] ,t2 维护t[i] * i)
    int n;
    inline void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) a[i] = a[i - 1] + a[i];
    }

    inline ll ask(int x) {  // 询问点 x 的值
        ll ans = a[x];
        for (int i = x; i; i -= lowbit(i)) ans += (x + 1) * t1[i] - t2[i];
        return ans;
    }
    inline void add(int x, ll k) {  // 点 x 的增量 +k
        for (int i = x; i <= n; i += lowbit(i)) t1[i] += k, t2[i] += x * k;
    }
    inline void modify(int l, int r, ll k) {  // 区间修改
        add(l, k);
        add(r + 1, -k);
    }
    inline ll query(int l, int r) {  // 区间求和
        return ask(r) - ask(l - 1);
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> fff.a[i];
    }
    fff.init(n);
    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            ll k;
            cin >> k;
            fff.modify(x, y, k);
        } else
            cout << fff.query(x, y) << endl;
    }
    return 0;
}

/*
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4

11
8
20
*/