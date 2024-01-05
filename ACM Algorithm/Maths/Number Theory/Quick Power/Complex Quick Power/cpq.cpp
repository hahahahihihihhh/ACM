/*
    复数快速幂
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;

struct Complex {
    ll a, b;   // a + bi
    Complex operator*(const Complex &x)const {
        return {a *x.a - b * x.b, a *x.b + b * x.a};
    }
    Complex operator%(ll mod)const {
        return {(a + mod) % mod, (b + mod) % mod};
    }
    Complex operator+(const Complex &x)const {
        return {a + x.a, b + x.b};
    }
};

Complex cpower(Complex x, ll p, ll mod) {
    Complex re = {1, 0};

    while (p) {
        if (p & 1) {
            re = re * x;
            re = re % mod;
        }

        p >>= 1;
        x = x * x;
        x = x % mod;
    }

    return re;
}

int main() {
    ll real, img, n;
    cin >> real >> img >> n;
    Complex ans = cpower({real, img}, n, MOD);
    cout << ans.a << " " << ans.b << "\n";
    return 0;
}

/*
1 1 2

0 2
*/