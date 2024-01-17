/*
    洛谷 P2742 [USACO5.1]圈奶牛Fencing-the-Cows/【模板】二维凸包
*/
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const int MAXN = 100005;

struct Point {  //点、向量
    ld x, y;

    Point() {}

    Point(ld _x, ld _y) { // 读入点
        x = _x;
        y = _y;
    }

    void input() {  //读入一个点
        cin >> x >> y;
    }

    ld operator^(const Point &b) const {  //叉乘
        return x * b.y - y * b.x;
    }

    Point operator-(const Point &b) const {  //返回减去后的新点
        return Point(x - b.x, y - b.y);
    }

    ld distance(Point &p) {  //返回两点间的距离
        return hypot(x - p.x, y - p.y);
    }
} point[MAXN];

Point st;

inline bool cmp1(const Point &a, const Point &b) {
    if (a.y == b.y)
        return a.x < b.x;

    return a.y < b.y;
}

bool cmp2(Point &a, Point &b) {
    if (atan2(a.y - st.y, a.x - st.x) == atan2(b.y - st.y, b.x - st.x))
        return a.distance(st) < b.distance(st);

    return atan2(a.y - st.y, a.x - st.x) < atan2(b.y - st.y, b.x - st.x);
}

struct CH {
    int cnt = 0, n;
    Point stk[MAXN];

    inline void init(int _n) {
        n = _n, cnt = 0;
    }

    inline ld cross(const Point &a, const Point &b, const Point &c) {
        return (b - a) ^ (c - a);
    }

    inline ld convex_hull_per() {   // 求凸包周长
        if (n == 1)
            return 0;
        else if (n == 2)
            return point[1].distance(point[2]);

        sort(point + 1, point + n + 1, cmp1);
        st = stk[++cnt] = point[1];
        sort(point + 1, point + n + 1, cmp2);
        stk[++cnt] = point[2];

        for (int i = 3; i <= n; i++) {
            while (cnt >= 2 && cross(stk[cnt - 1], stk[cnt], point[i]) < 0)
                cnt--;

            stk[++cnt] = point[i];
        }

        ld ans = 0;

        for (int i = 2; i <= cnt; i++)
            ans += stk[i].distance(stk[i - 1]);

        ans += stk[cnt].distance(stk[1]);
        return ans;
    }
} fff;

int main() {
    int n;
    cin >> n;

    fff.init(n);

    for (int i = 1; i <= n; i++)
        point[i].input();

    cout << fixed << setprecision(2) << fff.convex_hull_per() << "\n";

    return 0;
}

/*
4
4 8
4 12
5 9.3
7 8

12.00
*/