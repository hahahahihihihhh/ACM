/*
    洛谷 P3369 【模板】普通平衡树（AVL树）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 100005;

int cnt, rt;
struct Avl {
    struct Node {
        int l, r;
        int val, siz, h;
    } avl[MAXN];

    inline void init() {
        rt = 0, cnt = 0;
        memset(avl, 0, sizeof(avl));
    }

    inline void newNode(int &now, int val) {
        // 新建一个节点
        avl[now = ++cnt].val = val;
        avl[now].siz = avl[now].h = 1;
    }

    inline void update(int now) {
        // 更新节点
        avl[now].siz = avl[avl[now].l].siz + avl[avl[now].r].siz + 1;
        avl[now].h = max(avl[avl[now].l].h, avl[avl[now].r].h) + 1;
    }

    inline void lrotate(int &now) {
        // 左旋
        int r = avl[now].r;
        avl[now].r = avl[r].l;
        avl[r].l = now;
        now = r;
        update(avl[now].l), update(now);
    }

    inline void rrotate(int &now) {
        // 右旋
        int l = avl[now].l;
        avl[now].l = avl[l].r;
        avl[l].r = now;
        now = l;
        update(avl[now].r), update(now);
    }

    inline int getbf(int now) {
        // 获得平衡因子
        return avl[avl[now].l].h - avl[avl[now].r].h;
    }

    inline void balance(int &now) {
        // 平衡
        if (now)
            update(now);

        int bf = getbf(now);

        if (bf < -1) {
            if (getbf(avl[now].r) < 0)
                lrotate(now);   // RR
            else
                rrotate(avl[now].r), lrotate(now);  // RL                              
        } else if (bf > 1) {
            if (getbf(avl[now].l) > 0)
                rrotate(now);    // LL
            else
                lrotate(avl[now].l), rrotate(now); // LR
        }
    }

    void ins(int val, int &now = rt) {
        // 插入
        if (!now)
            newNode(now, val);
        else if (val < avl[now].val)
            ins(val, avl[now].l);
        else
            ins(val, avl[now].r);

        balance(now);
    }

    int tfind(int &now, int fa) {
        // 寻找后继    （由于balance函数的存在，这里now需为引用）
        int res;

        if (!avl[now].l) {
            res = now;
            avl[fa].l = avl[now].r;
        } else {
            res = tfind(avl[now].l, now);
            balance(now);
        }

        return res;
    }

    void del(int val, int &now = rt) {
        // 删除
        int l = avl[now].l, r = avl[now].r;

        if (val == avl[now].val) {
            if (!l || !r)
                now = l + r;
            else {
                // 双儿子
                now = tfind(r, r);   // 后继

                if (now != r)
                    avl[now].r = r;

                avl[now].l = l;
            }
        } else if (val < avl[now].val)
            del(val, avl[now].l);
        else
            del(val, avl[now].r);

        balance(now);
    }

    inline int getRank(int num) {
        // 获得值的排名
        int now = rt, rk = 1;

        while (now) {
            //      if (num == avl[now].val)        ？？？
            //      {
            //          rk += avl[avl[now].l].siz;
            //          break;
            //      }
            if (num <= avl[now].val)
                now = avl[now].l;
            else
                rk += avl[avl[now].l].siz + 1, now = avl[now].r;
        }

        return rk;
    }

    inline int getNum(int rk) {
        // 获得排名的值
        int now = rt, num = -1;

        while (now) {
            if (avl[avl[now].l].siz + 1 == rk) {
                num = avl[now].val;
                break;
            } else if (avl[avl[now].l].siz + 1 > rk)
                now = avl[now].l;
            else {
                rk -= avl[avl[now].l].siz + 1;
                now = avl[now].r;
            }
        }

        return num;
    }
} fff;

int main() {
    closeSync;
    int n;
    cin >> n;

    while (n--) {
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