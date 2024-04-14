/*
    洛谷 P3367 【模板】并查集
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct DSU {
    int n;
    int fa[MAXN];
    int rnk[MAXN];

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++)
            fa[i] = i, rnk[i] = 0;
    }

    int tfind(int x) { // 路径压缩
        return fa[x] == x ? x : tfind(fa[x]);
    }

    void tunion(int x, int y) {
        int xf = tfind(x), yf = tfind(y);

        if (xf != yf) {       //按秩合并
            if (rnk[xf] < rnk[yf])
                fa[xf] = yf;
            else {
                fa[yf] = xf;

                if (rnk[xf] == rnk[yf])
                    rnk[xf]++;
            }
        }
    }

    int tcount(int n) {
        int cnt = 0;

        for (int i = 1; i <= n; i++)
            if (fa[i] == i)
                cnt++;

        return cnt;
    }
} fff;

int main() {
    int n, m;
    cin >> n >> m;
    fff.init(n);

    for (int i = 1; i <= m; i++) {
        int z, x, y;
        cin >> z >> x >> y;

        if (z == 1)
            fff.tunion(x, y);
        else {
            if (fff.tfind(x) == fff.tfind(y))
                cout << "Y\n";
            else
                cout << "N\n";
        }
    }

    return 0;
}

/*
4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4

N
Y
N
Y
*/