/*
    洛谷 P3690 【模板】动态树（Link Cut Tree）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ls(x)   (spl[x].ch[0])
#define rs(x)   (spl[x].ch[1])
#define fa(x)   (spl[x].fa)
const int MAXN = 100005;

struct Lct {

    struct Spl {
        int fa, ch[2], val, sum;
        bool tag;       // 翻转标记
    } spl[MAXN];

    inline void init() {
        // 初始化
        memset(spl, 0, sizeof(spl));
    }

    inline void update(int x) {
        // 向上更新 x
        spl[x].sum = spl[ls(x)].sum ^ spl[rs(x)].sum ^ spl[x].val;
    }

    inline void reverse(int x) {
        // 翻转 x
        swap(ls(x), rs(x)), spl[x].tag ^= 1;
    }

    inline void pushdown(int x) {
        // 下传 x 的懒惰标记
        if (spl[x].tag) {
            if (ls(x))
                reverse(ls(x));

            if (rs(x))
                reverse(rs(x));
        }

        spl[x].tag = 0;
    }

    inline bool ntroot(int x) {
        // 判断 x 是否为所在实链的根
        return ls(fa(x)) == x || rs(fa(x)) == x;
    }

    inline void pushall(int x) {
        // 从所在实链的根开始将懒惰标记下传到 x
        if (ntroot(x))
            pushall(fa(x));

        pushdown(x);
    }

    inline bool indent(int x, int f) {
        // 确认父子关系
        return rs(f) == x;
    }

    inline void connect(int x, int f, bool k) {
        // 建立父子关系
        spl[fa(x) = f].ch[k] = x;
    }

    inline void rotate(int x) {
        // 单旋
        int f = fa(x), ff = fa(f), k = indent(x, f);
        connect(spl[x].ch[k ^ 1], f, k);
        fa(x) = ff;

        if (ntroot(f))
            spl[ff].ch[indent(f, ff)] = x;

        connect(f, x, k ^ 1);
        update(f), update(x);
    }

    inline void splay(int x) {
        // x 旋转到所在实链的根
        pushall(x); // !!!!

        while (ntroot(x)) {
            int f = fa(x), ff = fa(f);

            if (ntroot(f))
                (indent(x, f) ^ indent(f, ff)) ? rotate(x) : rotate(f);

            rotate(x);
        }
    }

    inline void access(int x) {
        // 打通 x 到所在连通块的根的实链
        int y;

        for (y = 0; x; x = fa(y = x)) {
            splay(x);
            rs(x) = y;
            update(x);
        }
    }

    inline void mkroot(int x) {
        // 以 x 为所在连通块的根
        access(x);
        splay(x);
        reverse(x);
    }

    inline int findroot(int x) {
        // 寻找 x 所在连通块的根
        access(x);
        splay(x);

        while (ls(x)) {
            pushdown(x);
            x = ls(x);
        }

        splay(x);
        return x;
    }

    inline void split(int x, int y) {
        // 分离出 y -> x 的路径
        mkroot(x);
        access(y);
        splay(y);
    }

    inline void link(int x, int y) {
        // 建边
        mkroot(x);

        if (findroot(y) == x)
            return;    // 已存在边

        fa(x) = y;          // 建虚边
    }

    inline void cut(int x, int y) {
        // 删边
        mkroot(x);

        if (findroot(y) != x || fa(y) != x || ls(y))
            return;

        rs(x) = fa(y) = 0;      // 断实边
        update(x);
    }

    inline int query(int x, int y) {
        // 询问 x -> y 路径的异或和
        split(x, y);
        return spl[y].sum;
    }

    inline void change(int x, int y) {
        // 改变一个点的权值
        mkroot(x);
        spl[x].val = y;
        update(x);
    }

} fff;

int main() {
    closeSync;
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> fff.spl[i].val;

    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;

        switch (opt) {
            case 0:cout << fff.query(x, y) << "\n";
                break;

            case 1:fff.link(x, y);
                break;

            case 2:fff.cut(x, y);
                break;

            case 3:fff.change(x, y);
                break;
        }
    }

    return 0;
}

/*
5 14
114
514
19
19
810
1 1 2
0 1 2
2 1 2
1 1 2
1 2 3
2 1 3
1 1 3
1 4 5
1 2 5
0 3 5
0 3 4
3 5 233333
0 1 5
0 2 5

624
315
296
232709
232823
*/