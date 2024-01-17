/*
    洛谷 P1742 最小圆覆盖
*/
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-7;  // 1e-6 ~ 1e-8
const ld PI = acos(-1);
const int MAXN = 100005;

int sgn(ld x) {  //三态函数，减小误差
    if (fabs(x) < EPS)
        return 0;

    if (x < 0)
        return -1;
    else
        return 1;
}

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

    Point operator-(const Point &b) const {  //返回减去后的新点
        return Point(x - b.x, y - b.y);
    }

    Point operator+(const Point &b) const {  //返回加上后的新点
        return Point(x + b.x, y + b.y);
    }

    Point operator*(const ld k) const {  //返回相乘后的新点
        return Point(x * k, y * k);
    }

    Point operator/(const ld k) const {  //返回相除后的新点
        return Point(x / k, y / k);
    }

    ld operator^(const Point &b) const {  //叉乘
        return x * b.y - y * b.x;
    }

    Point rotLeft() { // 逆时针选择90度
        return Point(-y, x);
    }

    ld distance(Point &p) {  //返回两点间的距离
        return hypot(x - p.x, y - p.y);
    }
};

typedef Point Vector;

struct Line {  //直线、线段
    Point s, e;
    Vector v;

    Line() {}

    Line(Point _s, Point _e) {// 线段
        s = _s;
        e = _e;
        v = _e - _s;
    }

    Point crossPoint(Line v) { //求两直线的交点 (调用前要保证两直线不平行或重合)
        ld a1 = (v.e - v.s) ^ (s - v.s); // -
        ld a2 = (v.e - v.s) ^ (e - v.s); // +
        return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
    }
};

typedef Line Seg;

struct Circle {  //圆
    ld r;        //半径
    Point p;     //圆心
    Circle() {}

    Circle(Point _p, ld _r) {
        p = _p;
        r = _r;
    }

    void input() {  //读入圆
        p.input();
        cin >> r;
    }

    Circle(ld x, ld y, ld _r) {
        p = Point(x, y);
        r = _r;
    }

    Circle(Point a, Point b, Point c) {
        // 三角形的外接圆
        Line u = Line((a + b) / 2, (a + b) / 2 + (b - a).rotLeft());
        Line v = Line((b + c) / 2, (b + c) / 2 + (c - b).rotLeft());
        p = u.crossPoint(v);
        r = p.distance(a);
    }

    int relationPoint(Point b) {
        /*
            点和圆的关系
            0 圆外
            1 圆上
            2 圆内
        */
        ld dst = b.distance(p);

        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;

        return 0;
    }
};

Point pt[MAXN];

inline Circle MinCcover(int n) {
    Circle ans = {pt[1], 0};

    for (int i = 2; i <= n; i++) {
        if (ans.relationPoint(pt[i]))
            continue;

        ans = {pt[i], 0};

        for (int j = 1; j < i; j++) {
            if (ans.relationPoint(pt[j]))
                continue;

            ans = {(pt[i] + pt[j]) / 2.0, pt[j].distance(pt[i]) / 2.0};

            for (int k = 1; k < j; k++) {
                if (ans.relationPoint(pt[k]))
                    continue;

                ans = Circle(pt[i], pt[j], pt[k]);
            }
        }
    }

    return ans;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        pt[i].input();

    random_shuffle(pt + 1, pt + n + 1);
    Circle c = MinCcover(n);
    cout << fixed << setprecision(10) << c.r << endl;
    cout << fixed << setprecision(10) << c.p.x << " " << c.p.y << endl;
    return 0;
}

/*
6
8.0 9.0
4.0 7.5
1.0 2.0
5.1 8.7
9.0 2.0
4.5 1.0

5.0000000000
5.0000000000 5.0000000000
*/