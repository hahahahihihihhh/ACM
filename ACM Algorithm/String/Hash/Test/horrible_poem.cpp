/*
    洛谷 P3538 [POI2012]-OKR-A-Horrible-Poem
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef unsigned long long ull;
typedef long long ll;
const int MAXN = 500005;

int min_prime_fac[MAXN], prime[MAXN], isnotprime[MAXN], cnt = 0;
ull POWB[MAXN], hsh[MAXN], base = 29; // base 要是质数，自然溢出取模
string str;
int n;

inline void init() {
    POWB[0] = 1ULL;
    hsh[0] = 0ULL;
    for (int i = 1; i <= n; i++) {
        hsh[i] = hsh[i - 1] * base + ull(str[i] - 'a' + 1);
        POWB[i] = POWB[i - 1] * base;
    }
    isnotprime[1] = 1;
    for (int i = 2; i <= MAXN - 2; i++) {
        if (!isnotprime[i]) {
            prime[++cnt] = i;
            min_prime_fac[i] = i;
        }
        for (int j = 1; j <= cnt && (ll) prime[j] * i <= MAXN - 2; j++) {
            min_prime_fac[i * prime[j]] = prime[j];
            isnotprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

inline bool check(int l, int r, int x) {// 区间哈希值
    ull head = hsh[r - x] - hsh[l - 1] * POWB[r - x - l + 1];
    ull tail = hsh[r] - hsh[l + x - 1] * POWB[r - x - l + 1];
    return head == tail;
}

inline int ask(int l, int r) {
    int len = r - l + 1;
    int tmp = len, ans = len;
    while (tmp != 1) {
        int t = min_prime_fac[tmp]; // 要检验的最小质因数，不会有重复与遗漏
        while (tmp % t == 0 && check(l, r, ans / t)) tmp /= t, ans /= t;  // 此时的 t 为循环次数，不对 ans 产生贡献，故除掉
        while (tmp % t == 0) tmp /= t;   // 由于 check() 跳出循环， ans/t 后不再为循环节，所以把 tmp 中 t 除尽以留住 ans 中的 t
    }
    return ans;
}

inline void solve() {
    cin >> n >> str;
    str = " " + str;
    init();
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << ask(l, r) << "\n";
    }
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
8
aaabcabc
3
1 3
3 8
4 8

1
3
5
*/