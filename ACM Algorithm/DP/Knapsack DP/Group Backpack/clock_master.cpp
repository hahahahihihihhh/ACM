/*
    Codeforces 2020-CCPC-Weihai L_Clock-Master
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
const int MAXN = 30005;
const int LIM = 30000;

int isnotprime[MAXN];
int cnt, prime[MAXN];
ld dp[MAXN];
ld LOG[MAXN];
// 分组背包
inline void init() {
    isnotprime[1] = 1;
    for (int i = 2; i <= LIM; i++) {
        if (!isnotprime[i]) prime[++cnt] = i;
        for (int j = 1; prime[j] * i <= LIM && j <= cnt; j++) {
            isnotprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= LIM; i++) LOG[i] = log(i);
}

inline void init1() {
    dp[0] = 0;
    for (int j = 1; j <= cnt; j++)    // 第 j 组
        for (int i = LIM; i >= prime[j]; i--) // 有多少钱
            for (int k = prime[j]; k <= i; k *= prime[j])   // 这个买不买
                dp[i] = max({dp[i - k] + LOG[k], dp[i]});       // 到第 j 组为止花费费用 i 能取得的最大权值
}

inline void solve() {
    int n;
    cin >> n;
    cout << fixed << setprecision(10) << dp[n] << endl;
}

int main() {
    closeSync;
    init();
    init1();
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
3
2
7
10

0.693147181
2.484906650
3.401197382
*/