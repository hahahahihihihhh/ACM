/*
    codeforces The-15th-Heilongjiang-Provincial-Collegiate-Programming-Contest H_Hate-That-You-Know-Me
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

inline ull calp2(ull r) {
    ull p1 = r, p2 = 2 * r + 1, p3 = r + 1;
    if (p1 % 6 == 0)
        return p1 / 6 * p2 * p3;
    if (p2 % 6 == 0)
        return p1 * (p2 / 6) * p3;
    if (p3 % 6 == 0)
        return p1 * p2 * (p3 / 6);
    if (p1 % 2 == 0 && p2 % 3 == 0) return (p1 / 2) * (p2 / 3) * p3;
    if (p1 % 3 == 0 && p2 % 2 == 0) return (p1 / 3) * (p2 / 2) * p3;
    if (p1 % 2 == 0 && p3 % 3 == 0) return (p1 / 2) * p2 * (p3 / 3);
    if (p1 % 3 == 0 && p3 % 2 == 0) return (p1 / 3) * p2 * (p3 / 2);
    if (p2 % 2 == 0 && p3 % 3 == 0) return p1 * (p2 / 2) * (p3 / 3);
    if (p2 % 3 == 0 && p3 % 2 == 0) return p1 * (p2 / 3) * (p3 / 2);
}

inline ull calp3(ull r) {
    if (r % 2 == 0)
        return (r / 2) * (r / 2) * (r + 1) * (r + 1);
    else
        return r * r * ((r + 1) / 2) * ((r + 1) / 2);
}

ull getp(ull l, ull r, ull p) {
    if (p == 0) return r - l + 1;
    if (p == 1) {
        ull p1 = (r - l + 1), p2 = l + r;
        if (p1 % 2 == 0) p1 /= 2;
        else p2 /= 2;
        return p1 * p2;
    }

    if (p == 2)
        return calp2(r) - calp2(l - 1);

    return calp3(r) - calp3(l - 1);

}

void solve() {
    ull a, b, n, ans_a = 0, ans_b = 0;
    cin >> a >> b >> n;
    for (ull l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans_a += getp(l, r, a) * (n / l);
        ans_b += getp(l, r, b) * (n / l);
    }
    cout << (ans_a ^ ans_b) << '\n';
}

int main() {
    closeSync;
    solve();
    return 0;
}

/*
0 1 4
7

2 3 2
12
*/