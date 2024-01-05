/*
    洛谷 P3369 【模板】普通平衡树（splay 普通版）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 100005;

int cnt, root;
struct Spl {

    struct Node {
        int l, r;
        int val, siz, cnt;  // cnt 为该节点重复次数
    } spl[MAXN];

    inline void init() {
        // 初始化
        root = 0, cnt = 0;
        memset(spl, 0, sizeof(spl));
    }

    inline void newNode(int &now, int val) {
        // 创建一个新节点
        spl[now = ++cnt].val = val;
        spl[now].cnt++, spl[now].siz++;
    }

    inline void update(int now) {
        // 更新
        spl[now].siz = spl[spl[now].l].siz + spl[spl[now].r].siz + spl[now].cnt;
    }

    inline void zig(int &now) {
        // 右旋
        int l = spl[now].l;
        spl[now].l = spl[l].r;
        spl[l].r = now;
        now = l;

        if (spl[now].r)
            update(spl[now].r);

        update(now);
    }

    inline void zag(int &now) {
        // 左旋
        int r = spl[now].r;
        spl[now].r = spl[r].l;
        spl[r].l = now;
        now = r;

        if (spl[now].l)
            update(spl[now].l);

        update(now);
    }

    void splay(int x, int &y) {
        // x 旋转到 y
        if (x == y)
            return;

        int &l = spl[y].l;
        int &r = spl[y].r;

        if (l == x)
            zig(y);
        else if (r == x)
            zag(y);
        else {
            if (spl[x].val < spl[y].val) {
                if (spl[x].val < spl[l].val)
                    splay(x, spl[l].l), zig(y), zig(y);
                else
                    splay(x, spl[l].r), zag(l), zig(y);
            } else {
                if (spl[x].val > spl[r].val)
                    splay(x, spl[r].r), zag(y), zag(y);
                else
                    splay(x, spl[r].l), zig(r), zag(y);
            }
        }
    }

    void ins(int val, int &now = root) {
        // 插入
        if (!now)
            newNode(now, val), splay(now, root);
        else if (val < spl[now].val)
            ins(val, spl[now].l);
        else if (val > spl[now].val)
            ins(val, spl[now].r);
        else
            spl[now].cnt++, splay(now, root);
    }

    void delNode(int now) {
        // 删除某个节点
        splay(now, root);
        assert(now == root);

        if (spl[now].cnt > 1) {
            spl[now].cnt--;
            update(now);
            return;
        }

        if (spl[now].r) {
            int p = spl[now].r;

            while (spl[p].l)
                p = spl[p].l;

            splay(p, spl[now].r);
            spl[p].l = spl[now].l;
            root = p;
            update(root);
        } else
            root = spl[now].l;
    }

    void del(int val, int now = root) {
        // 删除
        if (spl[now].val == val)
            delNode(now);
        else if (val < spl[now].val)
            del(val, spl[now].l);
        else
            del(val, spl[now].r);
    }

    inline int getRank(int num) {
        // 根据值获得排名
        int now = root, rk = 1;

        while (now) {
            if (num == spl[now].val) {
                rk += spl[spl[now].l].siz;
                splay(now, root);
                break;
            }

            if (num < spl[now].val)
                now = spl[now].l;
            else {
                rk += spl[spl[now].l].siz + spl[now].cnt;
                now = spl[now].r;
            }
        }

        return rk;
    }

    inline int getNum(int rk) {
        // 根据排名获得值
        int now = root, num = -1;

        while (now) {
            if (spl[spl[now].l].siz + 1 <= rk && rk <= spl[spl[now].l].siz + spl[now].cnt) {
                num = spl[now].val;
                splay(now, root);
                break;
            }

            if (rk < spl[spl[now].l].siz + 1) {
                now = spl[now].l;
            } else {
                rk -= spl[spl[now].l].siz + spl[now].cnt;
                now = spl[now].r;
            }
        }

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