/*
    Codeforces Round106 D_The-Number-of-Pairs
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const int MAXN = 2e7 + 10;
const ll INF = 1e18;

bool isnotprime[MAXN];
ll cnt[MAXN];   // cnt[i] 表示 i 能分解成多少个不同的质数
ll pow2[MAXN];
inline void init() {// 线性筛
    pow2[0] = 1LL;
    for (int i = 1; i <= 30; i++) pow2[i] = pow2[i - 1] * 2LL;
    isnotprime[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (!isnotprime[i]) {
            cnt[i] = 1;
            for (int j = i + i; j <= MAXN; j += i) {
                isnotprime[j] = 1;
                cnt[j] += 1;
            }
        }
    }
}

inline void solve() {
    ll c, d, x;
    cin >> c >> d >> x;         // 裴蜀定理 : 设 a,b 是不全为0的整数，则存在整数 x,y 使得 ax + by = gcd(a,b)
    vector<ll> v;
    for (ll i = 1; i <= (ll) sqrt(x); i++)    // gcd(a,b) 是 x 的因子
    {// 枚举所有因子
        if (x % i == 0) {
            ll t2 = x / i;
            v.push_back(i);
            if (t2 != i) v.push_back(t2);
        }
    }
    ll ans = 0;
    for (auto gcd : v) {// 枚举 gcd
        if ((x + d * gcd) % c != 0) continue;
        ll lcm = (x + d * gcd) / c;
        if (lcm % gcd != 0) continue;
        ll L = lcm / gcd;   // lcm = (x / gcd + d) / c 的上界是 2e7
        ans += pow2[cnt[L]];
    }
    cout << ans << "\n";
    return;
}

int main() {
    closeSync;
    init();
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
4
1 1 3
4 2 6
3 3 7
2 7 25

4
3
0
8
*/