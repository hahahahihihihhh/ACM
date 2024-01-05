/*
    洛谷 P3834 【模板】可持久化线段树2（主席树）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct CT {
    struct Node {
        int l, r;
        int sum;
    } node[MAXN * 40];
    int cnt, root[MAXN];
    int a[MAXN];
    vector<int> v;

    void init() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    inline int discre(int x) {  // x离散化后对应的数值
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
    inline void add(int id, int x) {
        a[id] = x, v.push_back(x);
    }
    void insert(int l, int r, int pre, int &now, int x) {  // 插入一个数
        node[++cnt] = node[pre];
        now = cnt;
        node[now].sum++;

        if (l == r)
            return;

        int mid = (l + r) >> 1;

        if (x <= mid)  //往左插入
            insert(l, mid, node[pre].l, node[now].l, x);
        else
            insert(mid + 1, r, node[pre].r, node[now].r, x);

        node[now].sum = node[node[now].l].sum + node[node[now].r].sum;
        return;
    }
    int query(int l, int r, int L, int R, int k) {  // 动态求区间第k小
        if (l == r)
            return l;

        int tmp = node[node[R].l].sum - node[node[L].l].sum;
        int mid = (l + r) >> 1;

        if (tmp >= k)  //往左
            return query(l, mid, node[L].l, node[R].l, k);
        else
            return query(mid + 1, r, node[L].r, node[R].r, k - tmp);
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        fff.add(i, tmp);
    }

    fff.init();

    for (int i = 1; i <= n; i++)
        fff.insert(1, n, fff.root[i - 1], fff.root[i], fff.discre(fff.a[i]));

    for (int i = 1; i <= m; i++) {
        int L, R, k;
        cin >> L >> R >> k;
        cout << fff.v[fff.query(1, n, fff.root[L - 1], fff.root[R], k) - 1] << "\n";
    }

    return 0;
}

/*
5 5
25957 6405 15770 26287 26465
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1

6405
15770
26287
25957
26287
*/