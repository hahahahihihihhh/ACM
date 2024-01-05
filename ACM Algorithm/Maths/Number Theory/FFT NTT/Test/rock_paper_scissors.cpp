/*
    牛客 2021年度训练联盟热身训练赛第四场 H_Rock-Paper-Scissors
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 1e6 + 10;
const double PI = acos(-1);

struct Complex { // 复数
    double x, y;
    Complex(double xx = 0, double yy = 0) { x = xx, y = yy; }
    Complex operator+(const Complex &xx) const { return Complex(x + xx.x, y + xx.y); }
    Complex operator-(const Complex &xx) const { return Complex(x - xx.x, y - xx.y); }
    Complex operator*(const Complex &xx) const { return Complex(x * xx.x - y * xx.y, x * xx.y + y * xx.x); }
} A[MAXN], B[MAXN];
string S, T;
int n, m;
struct FFT {
    int r[MAXN];
    inline void fft(Complex *A, int lim, int type) {// type = 1 : 傅利叶变换 ; type = -1 : 傅利叶逆变换
        for (int i = 0; i < lim; i++) if (i < r[i]) swap(A[i], A[r[i]]); // 初始状态
        for (int i = 1; i < lim; i <<= 1) {// 要被归并的区间长度
            Complex wn(cos(PI / i), type * sin(PI / i));
            for (int j = 0; j < lim; j += i << 1) {// 一个区间一个区间的合并
                Complex w(1, 0);
                for (int k = 0; k <= i - 1; k++, w = w * wn) {// w = w(2i,k)
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
        while (lim <= n + m) lim <<= 1, l++;
        for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));   //二进制反转取得i位置的最终位置r[i]
        fft(A, lim, 1);
        fft(B, lim, 1);
        for (int i = 0; i < lim; i++) A[i] = A[i] * B[i];  // A[i] 满足 A，B[i] 满足 B，A[i] * B[i] 满足 A * B
        fft(A, lim, -1);  // 根据点值求多项式
        vector<int> ans;
        for (int i = 0; i <= n + m; i++) ans.push_back(int(A[i].x / lim + 0.5));
        return ans;
    }
} fff;

inline void init() {
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
}

int ans[MAXN];
inline void cal1() {// 上 S 1 下 R 1
    for (int i = 0; i < n; i++) A[i].x = (S[i] == 'S');
    for (int i = 0; i < m; i++) B[i].x = (T[i] == 'R');
    vector<int> polyans = fff.poly_mul(A, B);
    for (int i = m - 1; i <= n + m - 2; i++) ans[i - (m - 1)] += polyans[i];
}

inline void cal2() {// 上 P 1 下 S 1
    for (int i = 0; i < n; i++) A[i].x = (S[i] == 'P');
    for (int i = 0; i < m; i++) B[i].x = (T[i] == 'S');
    vector<int> polyans = fff.poly_mul(A, B);
    for (int i = m - 1; i <= n + m - 2; i++) ans[i - (m - 1)] += polyans[i];
}

inline void cal3() {// 上 R 1 下 P 1
    for (int i = 0; i < n; i++) A[i].x = (S[i] == 'R');
    for (int i = 0; i < m; i++) B[i].x = (T[i] == 'P');
    vector<int> polyans = fff.poly_mul(A, B);
    for (int i = m - 1; i <= n + m - 2; i++) ans[i - (m - 1)] += polyans[i];
}

inline void solve() {
    cin >> n >> m;
    cin >> S >> T;
    reverse(T.begin(), T.end());
    cal1();
    init();
    cal2();
    init();
    cal3();
    int res = 0;
    for (int i = 0; i <= n - 1; i++)
        res = max(res, ans[i]);

    cout << res << "\n";
    return;
}

int main() {
    closeSync;
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
12 4  
PPPRRRRRRRRR
RSSS

2
*/
