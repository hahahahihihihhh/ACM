/*
    洛谷 P1168 中位数（求第K大值）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct WLT {
    struct Node {
        int l, r;
        int sum;
    } node[MAXN << 2];
    int a[MAXN];
    vector<int> v;

    void init() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    inline int discre(int x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
    inline void add(int id, int x) {
        a[id] = x, v.push_back(x);
    }
    void build(int l, int r, int rt = 1) {  // 建树
        node[rt].l = l, node[rt].r = r;
        int ls = rt << 1, rs = rt << 1 | 1;

        if (l == r) {
            node[rt].sum = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        return;
    }
    void insert(int x, int rt = 1) {  // 加入 x 这个数
        if (node[rt].l == node[rt].r) {
            node[rt].sum += 1;
            return;
        }

        int ls = rt << 1, rs = rt << 1 | 1;

        if (x <= node[ls].r)
            insert(x, ls);
        else
            insert(x, rs);

        node[rt].sum = node[ls].sum + node[rs].sum;
        return;
    }
    int search(int l, int r, int rt = 1) {  //  查找区间中的数的个数
        if (node[rt].l >= l && node[rt].r <= r)
            return node[rt].sum;

        int ls = rt << 1, rs = rt << 1 | 1;
        int ans = 0;

        if (node[ls].r >= l)
            ans += search(l, r, ls);

        if (node[rs].l <= r)
            ans += search(l, r, rs);

        return ans;
    }
    int KthNum(int k, int rt = 1) {  // 查找第K大数
        if (node[rt].l == node[rt].r)
            return node[rt].l;

        int ls = rt << 1, rs = rt << 1 | 1;

        if (node[rs].sum >= k)
            return KthNum(k, rs);
        else
            return KthNum(k - node[rs].sum, ls);
    }
} fff;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        fff.add(i, tmp);
    }

    fff.init();
    fff.build(1, MAXN);

    for (int i = 1; i <= n; i++) {
        fff.insert(fff.discre(fff.a[i]));

        if (i & 1)
            cout << fff.v[fff.KthNum(i / 2 + 1) - 1] << endl;
    }

    return 0;
}

/*
7
1 3 5 7 9 11 6

1
3
5
6
*/