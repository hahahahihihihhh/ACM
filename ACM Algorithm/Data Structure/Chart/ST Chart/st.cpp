/*
    洛谷 P3865 【模板】ST表
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN1 = 100005;
const int MAXN2 = 18;  // log2(MAXN1)

struct ST {
    int a[MAXN1];
    int st[MAXN1][MAXN2][2];    // 0 / 1 最小值，最大值
    int LOG2[MAXN1], POW2[MAXN1];

    void init(int n) { //初始化st表 O(NlognN)

        for (int i = 2; i <= n; i++)
            LOG2[i] = LOG2[i >> 1] + 1;

        POW2[0] = 1LL;

        for (int i = 1; i <= MAXN2; i++)
            POW2[i] = POW2[i - 1] * 2LL;

        for (int i = 1; i <= n; i++)
            st[i][0][0] = st[i][0][1] = a[i];

        for (int j = 1; POW2[j] <= n; j++) {
            for (int i = 1; i + POW2[j] - 1 <= n; i++) {
                st[i][j][0] = min(st[i][j - 1][0], st[i + POW2[j - 1]][j - 1][0]);
                st[i][j][1] = max(st[i][j - 1][1], st[i + POW2[j - 1]][j - 1][1]);
            }
        }
    }

    int search(int x, int y, int id) { //查询区间[x,y]中 最小值/最大值 0/1    O(1)
        int len = (y - x + 1);
        int t = LOG2[len];
        return id == 0 ? min(st[x][t][0], st[y - POW2[t] + 1][t][0]) : max(st[x][t][1], st[y - POW2[t] + 1][t][1]);
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> fff.a[i];

    fff.init(n);

    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        cout << fff.search(l, r, 1) << endl;
    }

    return 0;
}

/*
8 8
9 3 1 7 5 6 0 8
1 6
1 5
2 7
2 6
1 8
4 8
3 7
1 8

9
9
7
7
9
8
7
9
*/