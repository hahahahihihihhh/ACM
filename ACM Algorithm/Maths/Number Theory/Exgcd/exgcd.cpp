/*
    【模板】扩展gcd及求解一阶同余方程，一阶不定方程
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const ll MOD = 1e9 + 7;

// 裴蜀定理 : 设 a,b 是不全为 0 的整数，则存在整数 x,y 使得 ax + by = gcd(a,b) -> a,b 互质的充要条件是存在整数 x,y 使 ax+by=1
void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    //  ax + by = gcd(a,b) x 最小的特解 x1,y1
    if (!b) {
        x = 1, y = 0;
        d = a;
    } else {
        exgcd(b, a % b, d, y, x);
        // exgcd(b,a%b,d,x,y);
        // ll t = x;
        // x = y,y = t - (a/b)*y;
        y -= (a / b) * x;
    }
}

vector<pll> General_solution(ll a, ll b, int n) {
    // ax + by = gcd(a,b) 的前 n 个解
    ll d, x, y;
    exgcd(a, b, d, x, y);
    vector<pll> ans;
    for (int i = 0; i < n; i++)
        ans.push_back({x + (b / d) * i, y - (a / d) * i});
    return ans;
}

ll ask_inv(ll a, ll m) {
    // 扩展 gcd 求逆元 ：ax = 1(Mod m) -> ax + my = 1  ( gcd(a,m) = 1 )最小正整数解
    ll d, x, y;
    exgcd(a, m, d, x, y);
    return d == 1 ? (x + m) % m : -1;
}

ll modular_linear_minSolution(ll a, ll b, ll m) {
    // ax = b(Mod m) -> ax + my = b  最小正整数解 x
    ll d, x, y;
    exgcd(a, m, d, x, y);
    if (b % d)
        return -1; // 无解
    return (x + m / d) % (m / d) * (b / d) % (m / d);
}

vector<ll> modular_linear_allSolution(ll a, ll b, ll m) {
    // ax = b(Mod m) -> ax + my = b  所有解
    ll d, x, y;
    exgcd(a, m, d, x, y);
    vector<ll> ans;
    if (b % d)
        return ans;
    x = (x + m) % m * (b / d) % m;
    for (int i = 0; i < d; i++)
        ans.push_back((x + i * (m / d)) % m);
    return ans;
}

int main() {
    ll a, b, m;
    cin >> a >> b >> m;
    cout << modular_linear_minSolution(a, b, m) << "\n";
    return 0;
}

/*
3 5 4

3
*/