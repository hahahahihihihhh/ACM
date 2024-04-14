/*
    P3803 【模板】 多项式乘法(FFT)
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e7 + 10;  // n + m << 1
const double PI = acos(-1);

struct Complex { // 复数
    double x, y;

    Complex(double xx = 0, double yy = 0) {
        x = xx, y = yy;
    }

    Complex operator+(const Complex &xx) const {
        return Complex(x + xx.x, y + xx.y);
    }

    Complex operator-(const Complex &xx) const {
        return Complex(x - xx.x, y - xx.y);
    }

    Complex operator*(const Complex &xx) const {
        return Complex(x * xx.x - y * xx.y, x * xx.y + y * xx.x);
    }
} A[MAXN], B[MAXN];

int n, m;   // 多项式 A,B 的最高幂次
struct FFT {
    int r[MAXN];

    inline void fft(Complex *A, int lim, int type) {
        // type = 1 : 傅利叶变换 ; type = -1 : 傅利叶逆变换
        for (int i = 0; i < lim; i++)
            if (i < r[i])
                swap(A[i], A[r[i]]); // 初始状态

        for (int i = 1; i < lim; i <<= 1) {
            // 要被归并的区间长度
            Complex wn(cos(PI / i), type * sin(PI / i));

            for (int j = 0; j < lim; j += i << 1) {
                // 一个区间一个区间的合并
                Complex w(1, 0);

                for (int k = 0; k <= i - 1; k++, w = w * wn) {
                    // w = w(2i,k)
                    Complex x = A[j + k], y = w * A[j + i + k];
                    A[j + k] = x + y;
                    A[j + i + k] = x - y;
                }
            }
        }

        return;
    }

    inline vector<int> poly_mul(Complex *A, Complex *B) {
        int lim = 1, l = 0;

        while (lim <= n + m)
            lim <<= 1, l++;

        for (int i = 0; i < lim; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1)); //二进制反转取得i位置的最终位置r[i]

        fft(A, lim, 1);
        fft(B, lim, 1);

        for (int i = 0; i < lim; i++)
            A[i] = A[i] * B[i];  // A[i] 满足 A，B[i] 满足 B，A[i] * B[i] 满足 A * B

        fft(A, lim, -1); // 根据点值求多项式
        vector<int> ans;

        for (int i = 0; i <= n + m; i++)
            ans.push_back(int(A[i].x / lim + 0.5));

        return ans;
    }
} fff;

int main() {
    cin >> n >> m;

    for (int i = 0; i <= n; i++)
        cin >> A[i].x;

    for (int i = 0; i <= m; i++)
        cin >> B[i].x;

    vector<int> ans = fff.poly_mul(A, B);

    for (auto c: ans)
        cout << c << " ";

    cout << "\n";
    return 0;
}

/*
1 2
1 2
1 2 1

1 4 5 2
*/