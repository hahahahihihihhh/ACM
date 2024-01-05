/*
    洛谷 P3382 【模板】三分法
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const double eps = 1e-8;

int n;
double l, r, a[MAXN];

inline double F(double x) { // 多项式
    double sum = 0;

    for (int i = n; i >= 0; i--)
        sum = sum * x + a[i];

    return sum;
}

int main() {
    cin >> n >> l >> r;

    for (int i = n; i >= 0; i--)
        cin >> a[i];

    while (fabs(r - l) > eps) {
        double mid = (l + r) / 2;

        if (F(mid + eps) < F(mid))
            r = mid;
        else
            l = mid;
    }

    cout << fixed << setprecision(5) << r << endl;
    return 0;
}

/*
3 -0.9981 0.5
1 -3 -3 1

-0.41421
*/