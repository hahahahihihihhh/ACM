/*
    洛谷 P3390 【模板】矩阵快速幂
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 105;
const ll MOD = 1e9 + 7;

ll n, k; // n阶 下的矩阵

struct Matrix {
    ll a[MAXN][MAXN];
    Matrix() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = 0;
    }
    void identity() {
        //获得n阶单位矩阵
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = i == j ? 1 : 0;
    }
    Matrix operator*(const Matrix &x) const {
        Matrix res;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * x.a[k][j] % MOD) % MOD;

        return res;
    }
    friend ostream &operator<<(ostream &out, const Matrix &x) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                out << x.a[i][j] << (j == n ? "\n" : " ");

        return out;
    }
};
Matrix mpower(Matrix x, ll p) {
    Matrix res;
    res.identity();

    while (p) {
        if (p & 1)
            res = res * x;

        p >>= 1;
        x = x * x;
    }

    return res;
}

int main() {
    cin >> n >> k;
    Matrix m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> m.a[i][j];

    Matrix ans = mpower(m, k);
    cout << ans;
    return 0;
}

/*
2 1
1 1
1 1

1 1
1 1
*/