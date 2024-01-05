/*
    洛谷 P3369 【模板】普通平衡树（替罪羊树）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;
#define closeSync ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct TZY {
    const double alpha = 0.75;
    struct Node {
        int l, r, val;
        int size, fact;
        bool exist;
    } tzy[MAXN];
    int cnt, rt;
    vector<int> v;
    void init() {
        rt = 0;
        cnt = 0;
        memset(tzy, 0, sizeof(tzy));
    }
    void newnode(int &now, int val) {
        now = ++cnt;
        tzy[now].val = val;
        tzy[now].l = tzy[now].r = 0;
        tzy[now].size = tzy[now].fact = 1;
        tzy[now].exist = true;
    }
    void lift(int l, int r, int &now) {
        if (l == r) {
            now = v[l];
            tzy[now].l = tzy[now].r = 0;
            tzy[now].size = tzy[now].fact = 1;
            return;
        }
        int m = (l + r) >> 1;
        while (m > l && tzy[v[m]].val == tzy[v[m - 1]].val)
            m--;
        now = v[m];
        if (m > l)
            lift(l, m - 1, tzy[now].l);
        else
            tzy[now].l = 0;
        lift(m + 1, r, tzy[now].r);
        tzy[now].fact = tzy[now].size = tzy[tzy[now].l].size + tzy[tzy[now].r].size + 1;
    }
    void ldr(int now) {
        if (!now) return;
        ldr(tzy[now].l);
        if (tzy[now].exist)
            v.push_back(now);
        ldr(tzy[now].r);
    }
    void rebuild(int &now) {
        v.clear();
        ldr(now);
        if (v.empty()) {
            now = 0;
            return;
        }
        lift(0, v.size() - 1, now);
    }
    void update(int now, int end) {
        if (now == end) return;
        if (tzy[end].val < tzy[now].val)
            update(tzy[now].l, end);
        else
            update(tzy[now].r, end);
        tzy[now].size = tzy[tzy[now].l].size + tzy[tzy[now].r].size + 1;
    }
    void check(int &now, int end) {
        if (now == end) return;
        if (tzy[now].size * alpha < max(tzy[tzy[now].l].size, tzy[tzy[now].r].size) ||
            tzy[now].size - tzy[now].fact > 0.3 * tzy[now].size) {
            rebuild(now);                   //暴力重构
            update(rt, now);                //更新
            return;
        }
        if (tzy[end].val < tzy[now].val)
            check(tzy[now].l, end);
        else
            check(tzy[now].r, end);
    }
    void ins(int &now, int val) {
        if (!now) {
            newnode(now, val);
            check(rt, now);  //检查是否要重构，如果是就重构
            return;
        }
        tzy[now].size++, tzy[now].fact++;
        if (val < tzy[now].val)
            ins(tzy[now].l, val);
        else
            ins(tzy[now].r, val);
    }
    void del(int now, int val) {
        if (tzy[now].exist && tzy[now].val == val) {
            tzy[now].exist = false;
            tzy[now].fact--;
            check(rt, now);
            return;
        }
        tzy[now].fact--;
        if (val < tzy[now].val)
            del(tzy[now].l, val);
        else
            del(tzy[now].r, val);
    }
    int getrank(int val) {
        int rank = 1;
        int now = rt;
        while (now) {
            if (tzy[now].exist && val == tzy[now].val) {
                rank += tzy[tzy[now].l].fact;
                break;
            }
            if (val <= tzy[now].val)
                now = tzy[now].l;
            else {
                rank += tzy[now].exist + tzy[tzy[now].l].fact;
                now = tzy[now].r;
            }
        }
        return rank;
    }
    int getnum(int rank) {
        int now = rt;
        while (now) {
            if (tzy[now].exist && tzy[tzy[now].l].fact + tzy[now].exist == rank)
                break;
            else if (tzy[tzy[now].l].fact >= rank)
                now = tzy[now].l;
            else {
                rank -= tzy[tzy[now].l].fact + tzy[now].exist;
                now = tzy[now].r;
            }
        }
        return tzy[now].val;
    }
};

int main() {
    closeSync;
    int n;
    cin >> n;
    TZY tzy;
    tzy.init();
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        switch (opt) {
            case 1: tzy.ins(tzy.rt, x);
                break;
            case 2: tzy.del(tzy.rt, x);
                break;
            case 3: cout << tzy.getrank(x) << endl;
                break;
            case 4: cout << tzy.getnum(x) << endl;
                break;
            case 5: cout << tzy.getnum(tzy.getrank(x) - 1) << endl;
                break;
            case 6: cout << tzy.getnum(tzy.getrank(x + 1)) << endl;
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