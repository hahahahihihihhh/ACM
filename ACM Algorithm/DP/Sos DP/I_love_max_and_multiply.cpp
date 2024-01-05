/*
    hdu 2021"MINIEYE杯"中国大学生算法设计超级联赛2 K_I-love-max-and-multiply（SOSdp/父集/子集dp）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const ll MOD = 998244353;
const int MAXN = 1 << 20;
const ll INF = 1e9;

int N = 0;
ll A[MAXN], B[MAXN];
ll FA[MAXN][2], FB[MAXN][2];  // A,B mask 最大值，最小值
ll C[MAXN];

inline void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> A[i];
    for (int i = 0; i < n; i++)
        cin >> B[i];

    int tmp = n;
    N = 0;
    while (tmp) {
        N++;
        tmp >>= 1;
    }                // N位Sosdp

    for (int i = 0; i < (1 << N); ++i) {// 初始化A、B前0位不同的父集的最大值，最小值
        FA[i][0] = FA[i][1] = A[i];
        FB[i][0] = FB[i][1] = B[i];
        if (i >= n) {
            FA[i][0] = INF, FA[i][1] = -INF;
            FB[i][0] = INF, FB[i][1] = -INF;
        }
    }

    for (int i = 0; i < N; ++i)   // 前 i 位不同的A、B的父集最小值，最大值
        for (int mask = 0; mask < (1 << N); ++mask) {
            if (!(mask & (1 << i)))    // 去掉 ! 算的是子集
            {
                FA[mask][0] = min(FA[mask ^ (1 << i)][0], FA[mask][0]);
                FB[mask][0] = min(FB[mask ^ (1 << i)][0], FB[mask][0]);
                FA[mask][1] = max(FA[mask ^ (1 << i)][1], FA[mask][1]);
                FB[mask][1] = max(FB[mask ^ (1 << i)][1], FB[mask][1]);
            }
        }

    for (int i = n - 1; i >= 0; i--) {
        C[i] = max(max(FA[i][0] * FB[i][0], FA[i][1] * FB[i][1]),
                   max(FA[i][0] * FB[i][1], FA[i][1] * FB[i][0]));
    }
    ll ans = 0;
    for (int i = n - 2; i >= 0; i--)
        C[i] = max(C[i + 1], C[i]);
    for (int i = 0; i < n; i++) {
        ans += C[i] % MOD;
        ans %= MOD;
    }
    cout << (ans + MOD) % MOD << "\n";

}

int main() {
    closeSync;
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
2
4
9 1 4 1
5 4 1 1
4
-1 -1 -1 -1
1 1 1 1

54
998244349
*/
