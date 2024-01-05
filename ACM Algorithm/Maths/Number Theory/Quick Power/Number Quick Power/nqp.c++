/*
    洛谷 P1226 【模板】快速幂||取余运算
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

ll npower(ll x, ll p, ll mod) {
    ll re = 1;

    while (p != 0) {
        if (p & 1)
            re = (re * x) % mod;

        x = (x * x) % mod;
        p >>= 1;
    }

    return re % mod;
}

int main() {
    ll x, p, k;
    cin >> x >> p >> k;
    ll ans = npower(x, p, k);
    cout << x << "^" << p << " mod " << k << "=" << ans << endl;
    return 0;
}

/*
2 10 9

2^10 mod 9=7
*/
