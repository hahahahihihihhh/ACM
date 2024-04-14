/*
    洛谷 P3389 【模板】高斯消元法
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const double eps = 1e-5;

int n;
double det[MAXN][MAXN];
double ans[MAXN];

inline bool equal(double x, double y) {
    return fabs(x - y) < eps;
}

inline bool gauss_kill() {
    //高斯消元计算 n 阶行列式的值
    double ans = 1.0;
    for (int j = 1; j <= n; j++) {
        int i;
        for (i = j; i <= n; i++)
            if (det[i][j])
                break;
        if (i == n + 1)
            continue;
        if (i != j) {
            ans *= -1.0;
            for (int k = j; k <= n + 1; k++)
                swap(det[j][k], det[i][k]);
        }
        i += 1;
        for (i; i <= n; i++) {
            while (det[i][j]) {
                double t = det[i][j] / det[j][j];
                for (int k = j; k <= n + 1; k++)
                    det[i][k] = det[i][k] - t * det[j][k];
                if (equal(det[i][j], 0))
                    break;
                for (int k = j; k <= n + 1; k++)
                    swap(det[i][k], det[j][k]);
                ans *= -1.0;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (equal(det[i][i], 0))
            return false;
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> det[i][j];
    if (!gauss_kill()) {
        cout << "No Solution\n";
        return 0;
    }
    for (int i = n; i >= 1; i--) {
        double sum = det[i][n + 1];
        for (int j = n; j > i; j--)
            sum -= ans[j] * det[i][j];
        ans[i] = sum / det[i][i];
    }
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(2) << ans[i] << endl;
    return 0;
}

/*
3
1 3 4 5
1 4 7 3
9 3 2 2

-0.97
5.18
-2.39
*/
