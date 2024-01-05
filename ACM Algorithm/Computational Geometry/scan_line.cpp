/*
    洛谷 P5490 【模板】扫描线
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 200005;

struct Line {
    ll x;       //横坐标
    ll y1, y2;  // 纵坐标 y1 < y2
    int state;  //左右 1 -1
    bool operator<(const Line &a) const {
        return x < a.x;
    }
} line[MAXN];
struct Node {
    ll l, r;
    int cover;  //覆盖次数
    ll len; //真实覆盖长度
} node[MAXN << 4];
int v[MAXN];    //所有矩形纵坐标上的点

inline void pushup(int rt) {
    int ls = rt << 1, rs = rt << 1 | 1;

    if (node[rt].cover)
        node[rt].len = node[rt].r - node[rt].l;     //全覆盖
    else
        node[rt].len = node[ls].len + node[rs].len; //没有覆盖了，儿子线段的覆盖顶替
}
void build(int l, int r, int rt = 1) {
    node[rt].l = v[l], node[rt].r = v[r]; //表示该节点所表示线段的起始点，终到点

    if (r - l <= 1) {
        return;   //避免线段长度为0
    }

    int mid = (l + r) >> 1;
    int ls = rt << 1, rs = rt << 1 | 1;
    build(l, mid, ls);
    build(mid, r, rs);      //不留空隙
    return;
}
void modify(int l, int r, int x, int rt = 1) {
    if (l <= node[rt].l && node[rt].r <= r) {
        node[rt].cover += x;
        pushup(rt);
        return;
    }

    int ls = rt << 1, rs = rt << 1 | 1;

    if (l < node[ls].r)
        modify(l, r, x, ls);

    if (r > node[rs].l)
        modify(l, r, x, rs);

    pushup(rt);
    return;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        line[i] = {x1, y1, y2, 1}, line[n + i] = {x2, y1, y2, -1};
        v[i] = y1, v[i + n] = y2;
    }

    int m = n << 1;
    sort(line + 1, line + m + 1); //为了扫描
    sort(v + 1, v + m + 1); //为了建树

    build(1, m);

    ll ans = 0;

    for (int i = 1; i <= m; i++) {
        ans += (line[i].x - line[i - 1].x) * node[1].len; //先处理增加的贡献
        modify(line[i].y1, line[i].y2, line[i].state);      //再处理y轴覆盖的长度
    }

    cout << ans << endl;
    return 0;
}

/*
2
100 100 200 200
150 150 250 255

18000
*/