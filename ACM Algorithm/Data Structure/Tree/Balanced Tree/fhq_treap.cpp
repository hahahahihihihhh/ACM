/*
    洛谷 P3369 【模板】普通平衡树（fhq treap）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

mt19937 rnd(666);
struct FHQ {
    struct Node {
        int l, r;
        ll val, key;
        int size;
    } fhq[MAXN];
    int rt, cnt;
    inline void init() {
        rt = 0;  //为了让根为1（即第一个插入的节点号）且仅能为1
        cnt = 0;
        memset(fhq, 0, sizeof(fhq));
    }
    inline int newnode(ll val) {
        fhq[++cnt].val = val;
        fhq[cnt].key = rnd();  //随机键值
        fhq[cnt].size = 1;
        return cnt;
    }
    inline void update(int now) {
        fhq[now].size = fhq[fhq[now].l].size + fhq[fhq[now].r].size + 1;  //!!注意加上自己
    }
    void split(int now, ll val, int &x,
               int &y) {  //根为now的树分裂成根为 x,y的两颗子树 (x子树中所有节点都 <=val ,y中 >val)
        if (!now)
            x = y = 0;
        else {
            if (fhq[now].val <= val) {
                x = now;
                split(fhq[now].r, val, fhq[now].r, y);
                update(x);
            } else {
                y = now;
                split(fhq[now].l, val, x, fhq[now].l);
                update(y);
            }
        }
    }
    int merge(int x, int y) {  //根为x,y的两颗子树合并成根为返回值的树
        if (!x || !y)
            return x + y;
        if (fhq[x].key > fhq[y].key) {
            fhq[x].r = merge(fhq[x].r, y);  //!!!返回合并完后的根节点编号,注意要重新赋值
            update(x);
            return x;
        } else {
            fhq[y].l = merge(x, fhq[y].l);  //!!!返回合并完后的根节点编号,注意要重新赋值!
            update(y);
            return y;
        }
    }
    int x = 0, y = 0, z = 0;
    inline void ins(ll val) {
        split(rt, val, x, y);
        rt = merge(merge(x, newnode(val)), y);
    }
    inline void del(ll val) {
        split(rt, val, x, z);
        split(x, val - 1, x, y);
        y = merge(fhq[y].l, fhq[y].r);
        rt = merge(merge(x, y), z);
    }
    inline int getRank(ll val) {    // 获得值为 val 的 rank 
        split(rt, val - 1, x, y);
        int rk = fhq[x].size + 1;
        rt = merge(x, y);
        return rk;
    }
    inline ll getNum(int rank) {    // 获得排名为 rank 的数的值
        int now = rt;
        while (now) {
            if (fhq[fhq[now].l].size == rank - 1)
                break;
            if (fhq[fhq[now].l].size > rank - 1)
                now = fhq[now].l;
            else {
                rank -= fhq[fhq[now].l].size + 1;  //!!注意加上自己
                now = fhq[now].r;
            }
        }
        return fhq[now].val;
    }
    inline ll pre(ll val) { // val 的前驱 （ < val 且最大）
        split(rt, val - 1, x, y);
        int now = x;
        while (fhq[now].r) now = fhq[now].r;
        rt = merge(x, y);
        return fhq[now].val;
    }
    inline ll nxt(ll val) { // val 的后继（ > val 且最小 ）
        split(rt, val, x, y);
        int now = y;
        while (fhq[now].l) now = fhq[now].l;
        rt = merge(x, y);
        return fhq[now].val;
    }
} fff;

int main() {
    int n;
    cin >> n;
    fff.init();
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        switch (opt) {
            case 1:fff.ins(x);
                break;
            case 2:fff.del(x);
                break;
            case 3:cout << fff.getRank(x) << endl;
                break;
            case 4:cout << fff.getNum(x) << endl;
                break;
            case 5:
                // cout<<fhq.getNum(fhq.getRank(x)-1)<<endl;
                cout << fff.pre(x) << endl;
                break;
            case 6:
                // cout<<fhq.getNum(fhq.getRank(x+1))<<endl;
                cout << fff.nxt(x) << endl;
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