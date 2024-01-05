/*
    洛谷 P3369 【模板】普通平衡树（splay 简化版）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 100005;

int cnt, root;
struct Spl {

    struct Node {
        int fa, ch[2];      // 父亲，ch[0]：左儿子，ch[1]：右儿子
        int val, siz;
    } spl[MAXN];

    inline void init() {
        // 初始化
        root = 0, cnt = 0;
        memset(spl, 0, sizeof(spl));
    }

    inline void newNode(int val, int &now, int fa) {
        // 创建一个新节点
        spl[now = ++cnt].val = val;
        spl[now].fa = fa;
        spl[now].siz = 1;
    }

    inline void update(int x) {
        // 更新
        spl[x].siz = spl[spl[x].ch[0]].siz + spl[spl[x].ch[1]].siz + 1;
    }

    inline bool ident(int x, int fa) {
        // x 是 fa 的左儿子(0)/右儿子(1)
        return spl[fa].ch[1] == x;
    }

    inline void connect(int x, int fa, bool k) {
        // 建立父子关系
        spl[fa].ch[k] = x;
        spl[x].fa = fa;
    }

    inline void rotate(int x) {
        // 旋转（左旋/右旋）
        int f = spl[x].fa, ff = spl[f].fa, k = ident(x, f);
        connect(spl[x].ch[k ^ 1], f, k);
        connect(x, ff, ident(f, ff));
        connect(f, x, k ^ 1);
        update(f), update(x);
    }

    void splay(int x, int y = 0) {
        // x 旋转到 y 的儿子，虚拟点0是根的父亲
        if (!y)
            root = x;

        while (spl[x].fa != y) {
            int f = spl[x].fa, ff = spl[f].fa;

            if (ff != y)
                (ident(f, ff) ^ ident(x, f)) ? rotate(x) : rotate(f);

            rotate(x);
        }
    }

    void ins(int val, int &now = root, int fa = 0) {
        // 插入
        if (!now)
            newNode(val, now, fa), splay(now);
        else if (val < spl[now].val)
            ins(val, spl[now].ch[0], now);
        else
            ins(val, spl[now].ch[1], now);
    }

    void delNode(int x) {
        // 删除某个节点
        splay(x);

        if (spl[x].ch[1]) {
            int p = spl[x].ch[1];

            while (spl[p].ch[0])
                p = spl[p].ch[0];

            splay(p, x);            //p为 x 的后继
            connect(spl[x].ch[0], p, 0);
            root = p;
            spl[root].fa = 0;
            update(root);
        } else
            root = spl[x].ch[0], spl[root].fa = 0;
    }

    void del(int val, int now = root) {
        // 删除
        if (spl[now].val == val)
            delNode(now);
        else if (val < spl[now].val)
            del(val, spl[now].ch[0]);
        else
            del(val, spl[now].ch[1]);
    }

    inline int getRank(int num) {
        // 根据值获得排名
        int now = root, rk = 1, pre = 0;

        while (now) {
            if (num <= spl[now].val) {
                pre = now;
                now = spl[now].ch[0];
            } else {
                rk += spl[spl[now].ch[0]].siz + 1;
                now = spl[now].ch[1];
            }
        }

        if (pre)
            splay(pre);

        return rk;
    }

    inline int getNum(int rk) {
        // 根据排名获得值
        int now = root, num = -1;

        while (now) {
            if (spl[spl[now].ch[0]].siz + 1 == rk) {
                num = spl[now].val;
                splay(now);
                break;
            }

            if (rk < spl[spl[now].ch[0]].siz + 1) {
                now = spl[now].ch[0];
            } else {
                rk -= spl[spl[now].ch[0]].siz + 1;
                now = spl[now].ch[1];
            }
        }

        assert(num != -1);
        return num;
    }
} fff;

int main() {
    closeSync;
    int q;
    cin >> q;

    while (q--) {
        int opt, x;
        cin >> opt >> x;

        switch (opt) {
            case 1:fff.ins(x);
                break;

            case 2:fff.del(x);
                break;

            case 3:cout << fff.getRank(x) << "\n";
                break;

            case 4:cout << fff.getNum(x) << "\n";
                break;

            case 5:cout << fff.getNum(fff.getRank(x) - 1) << "\n";
                break;

            case 6:cout << fff.getNum(fff.getRank(x + 1)) << "\n";
                break;
        }
    }

    return 0;
}

/*
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598

106465
84185
492737
*/