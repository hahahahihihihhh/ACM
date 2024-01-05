/*
    牛客 2021牛客多校训练营2 F_Girlfriend（两球交的体积，也可求并）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld PI = acos(-1);

struct Point {
    ld x, y, z;
} A, B, C, D;

struct Ball {
    Point p;
    ld r;
};

int k1, k2;

inline ld sqr(ld x) {
    return x * x;
}

inline Ball getBall(Point A, Point B, ld k1) {
    // AP >= k1 * BP (圆)
    ld A1 = (-2 * sqr(k1) * B.x + 2 * A.x) / (sqr(k1) - 1);
    ld B1 = (-2 * sqr(k1) * B.y + 2 * A.y) / (sqr(k1) - 1);
    ld C1 = (-2 * sqr(k1) * B.z + 2 * A.z) / (sqr(k1) - 1);
    ld D1 = (sqr(k1) * sqr(B.z) + sqr(k1) * sqr(B.x) + sqr(k1) * sqr(B.y) - sqr(A.x) - sqr(A.y) - sqr(A.z)) /
        (sqr(k1) - 1);
    Point p = {-A1 / 2, -B1 / 2, -C1 / 2};
    ld r = sqrt(-D1 + (sqr(A1) + sqr(B1) + sqr(C1)) / 4);
    return {p, r};
}

inline ld intersect(Ball a, Ball b) {
    ld x1 = a.p.x, y1 = a.p.y, z1 = a.p.z, r1 = a.r;
    ld x2 = b.p.x, y2 = b.p.y, z2 = b.p.z, r2 = b.r;
    ld d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));

    if (d >= r1 + r2) {
        return 0;
    } else if (d <= fabs(r1 - r2)) {
        ld r = min(r1, r2);
        return 4.0 / 3.0 * PI * (sqr(r) * r);
    } else {
        ld s = 0;
        ld h1 = r1 - (sqr(r1) - sqr(r2) + sqr(d)) / (2.0 * d);
        s += (PI * sqr(h1) * (3 * r1 - h1) / 3.0);
        ld h2 = r2 - (sqr(r2) - sqr(r1) + sqr(d)) / (2.0 * d);
        s += (PI * sqr(h2) * (3 * r2 - h2) / 3.0);
        return s;
    }
}

inline void solve() {
    cin >> A.x >> A.y >> A.z;
    cin >> B.x >> B.y >> B.z;
    cin >> C.x >> C.y >> C.z;
    cin >> D.x >> D.y >> D.z;
    cin >> k1 >> k2;

    Ball b1 = getBall(A, B, k1);
    Ball b2 = getBall(C, D, k2);

    cout << fixed << setprecision(10) << intersect(b1, b2) << "\n";

}

int main() {
    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}

/*
1
1 0 0
3 0 0
2 0 0
4 0 0
3 3

0.262
*/