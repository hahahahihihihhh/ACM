/*
    atcoder abc196 F_Substring-2
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long double ld;
const int MAXN = 1e7 + 10;
const double PI = acos(-1);
const int INF = 0x3f3f3f3f;

struct Complex {
    double x, y;
    Complex(ld xx = 0, ld yy = 0) { x = xx, y = yy; }
    Complex operator+(const Complex &xx) const { return Complex(x + xx.x, y + xx.y); }
    Complex operator-(const Complex &xx) const { return Complex(x - xx.x, y - xx.y); }
    Complex operator*(const Complex &xx) const { return Complex(x * xx.x - y * xx.y, x * xx.y + y * xx.x); }
} A[MAXN], B[MAXN];
int n, m;
struct FFT {
    int r[MAXN];
    inline void fft(Complex *A, int lim, int type) {
        for (int i = 0; i < lim; i++) if (i < r[i]) swap(A[i], A[r[i]]); // 重新安排顺序
        for (int i = 1; i < lim; i <<= 1) {// 要被合并的区间长度
            Complex wn(cos(PI / i), type * sin(PI / i));
            for (int j = 0; j < lim; j += i << 1) {
                Complex w(1, 0);
                for (int k = 0; k <= i - 1; k++, w = w * wn) {
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
        for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        fft(A, lim, 1);
        fft(B, lim, 1);
        for (int i = 0; i < lim; i++) A[i] = A[i] * B[i];
        fft(A, lim, -1);
        vector<int> ans;
        for (int i = 0; i <= n + m; i++) ans.push_back(int(A[i].x / lim + 0.5));
        return ans;
    }
} fff;

int sumS[MAXN], sumT[MAXN];

inline void solve() {
    string s, t;
    cin >> s >> t;
    n = s.size();
    m = t.size();
    sumS[0] = (s[0] == '1'), sumT[0] = (t[0] == '1');
    for (int i = 1; i < n; i++) sumS[i] = sumS[i - 1] + (s[i] == '1');
    for (int i = 1; i < m; i++) sumT[i] = sumT[i - 1] + (t[i] == '1');
    for (int i = 0; i < n; i++) A[i] = s[i] - '0';
    reverse(t.begin(), t.end());
    for (int i = 0; i < m; i++) B[i] = t[i] - '0';
    vector<int> C = fff.poly_mul(A, B);
    int ans = INF;
    for (int i = m - 1; i <= n - 1; i++) {
        int ii = i - m + 1;
        int tmp = (ii == 0 ? sumS[ii + m - 1] : sumS[ii + m - 1] - sumS[ii - 1]) + sumT[m - 1];
        ans = min(ans, tmp - 2 * C[i]);
    }
    cout << ans << "\n";
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
10101000010011011110
0010011111
1

0101010
1010101
7
*/