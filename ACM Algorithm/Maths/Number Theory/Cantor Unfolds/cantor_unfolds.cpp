/*
    洛谷 P5367 【模板】康托展开
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1000005;
const ll MOD = 998244353;

struct Contor {
    int n;
    int delta[MAXN], vis[MAXN], a[MAXN], ans[MAXN];
    ll fac[MAXN];
    // 树状数组

    inline int lowbit(int x) {
        return x & -x;
    }

    inline void add(int x, int k) {
        for (int i = x; i <= n; i += lowbit(i))
            delta[i] += k;
    }

    inline int ask(int x) {
        int sum = 0;
        for (int i = x; i; i -= lowbit(i))
            sum += delta[i];
        return sum;
    }

    inline void modify(int l, int r, int k) {
        add(l, k);
        add(r + 1, -k);
    }

    inline void init(int _n) {
        n = _n;
        fac[0] = 1;
        for (int i = 1; i <= MAXN - 5; ++i)
            fac[i] = fac[i - 1] * i % MOD;
    }

    inline int conter() {
        // 求长度为n的排列中，a为第几个排列
        ll ans = 0;
        for (int i = 1; i <= n - 1; ++i) {
            int cnt = a[i] - 1 + ask(a[i]);
            modify(a[i] + 1, n, -1);
            ans += cnt * fac[n - i] % MOD;
            ans %= MOD;
        }
        return (ans + 1) % MOD;
    }

    inline void deconetr(int n, ll k) {
        // 求长度为n的排列中，第k大的排列
        for (int i = 1; i <= n; i++)
            vis[i] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int cnt = 0;
            ll q = k / fac[i], r = k % fac[i];
            for (int j = 1; j <= n; j++) {
                if (!vis[j])
                    cnt++;
                if (cnt == q + 1) {
                    ans[n - i] = j;
                    k = r;
                    vis[j] = 1;
                    break;
                }
            }
        }
    }
} fff;

int main() {
    int n;
    cin >> n;
    fff.init(n);
    for (int i = 1; i <= n; ++i)
        cin >> fff.a[i];
    cout << fff.conter() << endl;
    return 0;
}

/*
3
2 1 3

3
*/