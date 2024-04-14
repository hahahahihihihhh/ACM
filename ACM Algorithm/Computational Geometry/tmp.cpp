/*
    计算几何模板（某年区域赛真题）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-7;  // 1e-6 ~ 1e-8
const ld PI = acos(-1.0);

int sgn(ld x) {  //三态函数，减小误差
    if (fabs(x) < EPS)
        return 0;

    if (x < 0)
        return -1;
    else
        return 1;
}

inline ld sqr(ld x) {
    return x * x;
}

struct Point {  //点、向量
    ld x, y;

    Point() {}

    Point(ld _x, ld _y) {
        x = _x;
        y = _y;
    }

    void input() {  //输入点
        cin >> x >> y;
    }

    void output() { // 输出点
        cout << setprecision(2) << x << " " << y << "\n";
    }

    bool operator==(Point b) const {  //判断两点是否相等
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }

    bool operator<(Point b) const {  //两点间比大小，类似 pair
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }

    Point operator-(const Point &b) const {  //返回减去后的新点
        return Point(x - b.x, y - b.y);
    }

    ld operator^(const Point &b) const {  //叉乘
        return x * b.y - y * b.x;
    }

    ld operator*(const Point &b) const {  //点乘
        return x * b.x + y * b.y;
    }

    ld len() {  //返回长度
        return hypot(x, y);
    }

    ld len2() {  //返回长度的平方
        return x * x + y * y;
    }

    ld distance(Point p) {  //返回两点间的距离
        return hypot(x - p.x, y - p.y);
    }

    Point operator+(const Point &b) const {  //返回加上后的新点
        return Point(x + b.x, y + b.y);
    }

    Point operator*(const ld &k) const {  //返回相乘后的新点
        return Point(x * k, y * k);
    }

    Point operator/(const ld &k) const {  //返回相除后的新点
        return Point(x / k, y / k);
    }

    ld rad(Point a, Point b) { // 计算 pa 和 pb 的夹角，就是求从这个点看 a,b 所成夹角
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }

    Point trunc(ld r) {  //化为长度为 r 的向量
        ld l = len();

        if (!sgn(l))
            return *this;

        r /= l;
        return Point(x * r, y * r);
    }

    Point rotLeft() { // 逆时针选择90度
        return Point(-y, x);
    }

    Point rotRight() {
        return Point(y, -x);
    }

    Point rotate(Point p, ld rad) { //向量绕点p逆时针旋转rad度
        Point v = (*this) - p;
        ld c = cos(rad), s = sin(rad);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
};

typedef Point Vector;

struct Line {  //直线、线段
    Point s, e;

    Line() {}

    Line(Point _s, Point _e) {// 线段
        s = _s;
        e = _e;
    }

    bool operator==(Line v) {  //判断两条线段是否相等
        return s == v.s && e == v.e;
    }

    Line(Point p, ld angle) {   // 根据一个点和倾斜角angle确定直线， 0 <= angle < PI
        s = p;

        if (sgn(angle - PI / 2) == 0)
            e = s + Point(0, 1);
        else
            e = s + Point(1, tan(angle));
    }

    Line(double a, double b, double c) { // ax+by+c = 0
        if (sgn(a) == 0) {
            s = Point(0, -c / b);
            e = Point(1, -c / b);
        } else if (sgn(b == 0)) {
            s = Point(-c / a, 0);
            e = Point(-c / a, 1);
        } else {
            s = Point(0, -c / b);
            e = Point(1, (-c - a) / b);
        }
    }

    void input() { // 输入直线
        s.input();
        e.input();
    }

    void adjust() {
        if (e < s)
            swap(s, e);
    }

    ld length() {  // 线段的长度
        return s.distance(e);
    }

    ld angle() {  // 返回直线的倾斜角 0 <= seta < PI
        ld k = atan2(e.y - s.y, e.x - s.x);

        if (sgn(k) < 0)
            k += PI;

        if (sgn(k - PI) == 0)
            k -= PI;

        return k;
    }

    int relation(Point p) {
        /*点和直线的关系
                                 1 在左侧
                                 2 在右侧
                                 3 在直线上
                               */
        int c = sgn((p - s) ^ (e - s));

        if (c < 0)
            return 1;
        else if (c > 0)
            return 2;
        else
            return 3;
    }

    bool pointOnSeg(Point p) {  //判断点是否在线段上
        return sgn((p - s) ^ (e - s)) == 0      // 如果点已在直线上则会有精度误差
               && sgn((p - s) * (p - e)) <= 0;
    }

    bool parallel(Line v) { // 两直线是否平行或重合
        return sgn((e - s) ^ (v.e - v.s)) == 0;
    }

    int segCrossSeg(Line v) {
        /*
            2 规范相交
            1 非规范相交
            0 不相交
            */
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        int d3 = sgn((v.e - v.s) ^ (s - v.s));
        int d4 = sgn((v.e - v.s) ^ (e - v.s));

        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
            return 2;

        return (d1 == 0 && sgn((v.s - s) * (v.s - e)) <= 0) ||
               (d2 == 0 && sgn((v.e - s) * (v.e - e)) <= 0) ||
               (d3 == 0 && sgn((s - v.s) * (s - v.e)) <= 0) ||
               (d4 == 0 && sgn((e - v.s) * (e - v.e)) <= 0);
    }

    int lineCrossSeg(Line v) {
        /*
            直线和线段相交判断
            -*this line -v seg
            2：规范相交
            1：非规范相交
            0：不相交
        */
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));

        if ((d1 ^ d2) == -2)
            return 2;

        return (d1 == 0 || d2 == 0);
    }

    int lineCrossLine(Line v) {
        /*
            两直线关系
            0 平行
            1 重合
            2 相交
            */
        if ((*this).parallel(v))
            return v.relation(s) == 3;

        return 2;
    }

    Point crossPoint(Line v) { //求两直线的交点 (调用前要保证两直线不平行或重合)
        ld a1 = (v.e - v.s) ^ (s - v.s); // -
        ld a2 = (v.e - v.s) ^ (e - v.s); // +
        return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
    }

    ld disPointToLine(Point p) {  //点到直线的距离
        return fabs((p - s) ^ (e - s)) / length();
    }

    ld disPointToSeg(Point p) { // 点到线段的距离（最近距离）
        if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
            return min(p.distance(s), p.distance(e));

        return disPointToLine(p);
    }

    ld disSegToSeg(Line v) {  // 线段到线段距离（两线段不相交,相交距离为0）
        return min(min(disPointToSeg(v.s), disPointToSeg(v.e)),
                   min(v.disPointToSeg(s), v.disPointToSeg(e)));
    }

    Point lineProg(Point p) {  //返回点p在直线上的投影
        return s + ((e - s) * ((e - s) * (p - s))) / (e - s).len2();
    }

    Point symmetryPoint(Point p) {  //返回点p关于直线的对称点
        Point q = lineProg(p);
        return Point(2.0 * q.x - p.x, 2.0 * q.y - p.y);
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

    Circle(Point a, Point b, Point c, bool flag) {
        // 三角形的内切圆，bool flag 只是为了与上面的的外接圆函数做区别
        Line u, v;
        ld m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        v.s = b;
        m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
        v.e = v.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        p = u.crossPoint(v);
        r = Line(a, b).disPointToSeg(p);
    }

    void input() {  //输入圆
        p.input();
        cin >> r;
    }

    void output() { //输出圆
        cout << setprecision(2) << p.x << " " << p.y << " " << r << "\n";
    }

    bool operator==(Circle v) {
        return (p == v.p) && sgn(r - v.r) == 0;
    }

    bool operator<(Circle v) const { // 圆心优先比较，在比半径
        return ((p < v.p) || ((p == v.p) && sgn(r - v.r) < 0));
    }

    ld area() { // 面积
        return PI * r * r;
    }

    ld circumference() { // 周长
        return 2.0 * PI * r;
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

    int relationSeg(Line v) {
        /*
            线段和圆的关系
            0 圆内
            1 圆上
            2 圆内
        */
        ld dst = v.disPointToSeg(p);

        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;

        return 0;
    }

    int relationLine(Line v) {
        /*直线和圆的关系
                                      0 : 相离
                                      1 : 相切
                                      2 : 相交
                                  */
        ld dst = v.disPointToLine(p);

        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;

        return 0;
    }

    int relationCircle(Circle v) {
        /*
            两圆的关系
            5 相离
            4 外切
            3 相交
            2 内切
            1 内含
        */
        ld d = p.distance(v.p);

        if (sgn(d - r - v.r) > 0)
            return 5;

        if (sgn(d - r - v.r) == 0)
            return 4;

        ld l = fabs(r - v.r);

        if (sgn(d - r - v.r) < 0 && sgn(d - l) > 0)
            return 3;

        if (sgn(d - l) == 0)
            return 2;

        if (sgn(d - l) < 0)
            return 1;
    }

    int pointCrossLine(Line &l, Point &p1,
                       Point &p2) {  //求直线和圆的交点，返回交点个数  p1为近点，p2为远点
        if (!(*this).relationLine(l))
            return 0;

        Point a = l.lineProg(p);
        ld d = l.disPointToLine(p);
        d = sqrt(r * r - d * d);

        if (sgn(d) == 0) {
            p1 = a;
            p2 = a;
            return 1;
        }

        p1 = a - (l.e - l.s).trunc(d);
        p2 = a + (l.e - l.s).trunc(d);
        return 2;
    }

    bool pointInsideCircle(Point &p1) { // 判断点是不是在圆内
        return sgn(p1.distance(p) - r) <= 0;
    }
};

void solve(int t) {
    Point A, B;
    Vector va;
    Circle O;
    O.input();
    A.input();
    va.input();
    B.input();
    Line la = Line(A, A + va * 10000);
    Point P1, P2;
    int cnt = O.pointCrossLine(la, P1, P2);
    string ans = "No";

    if (Vector(O.p - A) * va >= 0 && cnt == 2) {  // 反弹
        if (P2.distance(A) < P1.distance(A))
            P1 = P2;

        Line OP1 = Line(O.p, P1);
        Point A1 = OP1.symmetryPoint(A);
        Line AP1 = Line(A, P1);
        Line P1A1 = Line(P1, P1 + (A1 - P1) * 10000);

        if (AP1.pointOnSeg(B) || P1A1.pointOnSeg(B))
            ans = "Yes";
    } else {
        if (la.pointOnSeg(B))
            ans = "Yes";
    }

    cout << "Case #" << t << ": " << ans << endl;
}

int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++)
        solve(i);

    return 0;
}