/*
    洛谷 P1075 [NOIP2012-普及组]-质因数分解（Pollard rho 算法 n^(1/4)）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

int ss[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 325, 9375, 28187, 450775, 9870504, 1795265022};

inline ll mul(ll a, ll b, ll p) {  //a*b%p
    ll s = a * b - (ll) ((long double) a * b / p + 0.5) * p;
    return s < 0 ? s + p : s;
}

inline ll qpower(ll x, ll y, ll p) {
    ll s = 1;

    for (; y;) {
        if (y & 1)
            s = mul(s, x, p);

        x = mul(x, x, p);
        y = y >> 1;
    }

    return s;
}

inline bool MR_detect(ll n, ll a) {
    if (n == a)
        return 1;

    if (a % n == 0)
        return 1;

    if (qpower(a, n - 1, n) != 1)
        return 0;

    ll p = n - 1, lst = 1;

    for (; ((p & 1) ^ 1) && lst == 1;) {
        p = p >> 1;
        lst = qpower(a, p, n);

        if (lst != 1 && lst != n - 1)
            return 0;
    }

    return 1;
}

inline bool MR(ll n) {
    // 质数判定
    if (n < 2)
        return 0;

    for (int i = 0; i < 16; i++)
        if (!MR_detect(n, ss[i]))
            return 0;

    return 1;
}

inline ll F(ll x, ll C, ll p) {
    return (mul(x, x, p) + C) % p;
}

inline ll Rand() {
    return (ll) rand() + ((ll) rand() << 15) + ((ll) rand() << 30) + ((ll) rand() << 45);
}

inline ll PR(ll n) {
    // 获得 n 的一个因数
    if (MR(n))
        return n;

    if (n == 4)
        return 2;

    for (;;) {
        ll C = Rand() % (n - 1) + 1;
        ll p1 = 0, p2 = 0;
        ll s = 1, tmp;

        for (;;) {
            for (int i = 0; i < 128; i++) {
                p2 = F(F(p2, C, n), C, n);
                p1 = F(p1, C, n);
                tmp = mul(s, abs(p1 - p2), n);

                if (tmp == 0 || p1 == p2)
                    break;

                s = tmp;
            }

            tmp = __gcd(n, s);

            if (tmp > 1)
                return tmp;

            if (p1 == p2)
                break;
        }
    }
}

inline vector<ll> Pollard_rho(ll n) {
    // 质因数分解
    vector<ll> pf;

    if (MR(n))
        pf.push_back(n);
    else {
        for (; n != 1;) {
            ll tmp = PR(n);

            for (; !MR(tmp);)
                tmp = PR(tmp);

            pf.push_back(tmp);

            for (; n % tmp == 0;)
                n = n / tmp;
        }
    }

    return pf;
}

int main() {
    srand((unsigned) 0);
    ll n;
    cin >> n;
    vector<ll> tmp = Pollard_rho(n);
    assert(tmp.size() == 2);
    cout << (tmp[0] > tmp[1] ? tmp[0] : tmp[1]) << "\n";
    return 0;
}

/*
21
7
*/