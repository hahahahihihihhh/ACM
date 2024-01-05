/*
    洛谷 P1494 [国家集训队]小Z的袜子（莫涛队列）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const int MAXN = 50005;

ll up, down, sum;       //不经过约分的分子分母，总共有多少的袜子
int block, bl[MAXN];    // 块数，块号
pll ans[MAXN];
int a[MAXN];
int cnt[MAXN];  // 维护区间各颜色的个数
int n, m;

struct Q {
    int l, r, id;
} q[MAXN];

inline void init() {
    block = n / sqrt((m << 1) / 3);

    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
        bl[q[i].l] = (q[i].l - 1) / block + 1;
    }
}
inline void add(int x) {
    up += cnt[a[x]];
    down += sum;
    cnt[a[x]]++;
    sum++;
}
inline void sub(int n) {
    cnt[a[n]]--;
    sum--;
    up -= cnt[a[n]];
    down -= sum;
}

int main() {

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    init();

    sort(q + 1, q + m + 1, [](Q x, Q y) {
        return bl[x.l] != bl[y.l] ? bl[x.l] < bl[y.l] : bl[x.l] & 1 ? x.r < y.r : x.r > y.r;
    });
    int l = 1, r = 0;

    for (int i = 1; i <= m; i++) {

        while (r < q[i].r)
            add(++r);

        while (l > q[i].l)
            add(--l);

        while (l < q[i].l)
            sub(l++);

        while (r > q[i].r)
            sub(r--);

        ans[q[i].id] = (down == 0 ? make_pair(0LL, 1LL) : make_pair(up / __gcd(up, down), down / __gcd(up, down)));
    }

    for (int i = 1; i <= m; i++)
        cout << ans[i].first << "/" << ans[i].second << "\n";

    return 0;
}

/*
6 4
1 2 3 3 3 2
2 6
1 3
3 5
1 6

2/5
0/1
1/1
4/15
*/