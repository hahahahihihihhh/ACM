#pragma GCC optimize(2)
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,avx,avx2")
//#pragma comment(linker, "/STACK:102400000,102400000") �ֶ���ջ
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
// typedef __int128 lll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef set<int>::iterator iit;

template<typename T>
inline T abs(T x) {
    return x > 0 ? x : -x;
}

template<typename T>
inline T sqr(T x) {
    return x * x;
}

template<typename T>
inline T max(T a, T b, T c) {
    return max(max(a, b), c);
}

template<typename T>
inline T min(T a, T b, T c) {
    return min(min(a, b), c);
}

template<typename T>
inline T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

template<typename T, typename T1>
inline T qpower(T x, T p, T1 mod) {
    T re = 1;
    x %= mod;
    while (p) {
        if (p & 1)
            re = (re * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return re;
}

template<typename T1, typename T2>
inline T1 power(T1 x, T2 p) {
    return x < 0 && p < 1 && -1 < p ? p != 0 ? -pow(-x, p) : 1 : pow(x, p);
}

inline bool mr(ll x, ll b) {
    ll k = x - 1;
    while (k) {
        ll cur = qpower(b, k, x);
        if (cur != 1 && cur != x - 1)
            return false;
        if ((k & 1) == 1 || cur == x - 1)
            return true;
        k >>= 1;
    }
    return true;
}

inline bool isprime(ll x) {
    if (x == 46856248255981ll || x < 2)
        return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251)
        return true;
    return mr(x, 2) && mr(x, 61);
}

// char buf[1 << 21], *p1=buf, *p2=buf;
// inline int getc(){return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF :
// *p1++;}
template<typename T>
inline void read(T &res) {
    char c;
    res = 0;
    bool f = 0;
    while ((c = getchar()) < 48)
        if (c == '-')
            f = 1;
    do
        res = (res << 1) + (res << 3) + (c ^ 48);
    while ((c = getchar()) > 47);
    if (f)
        res = -res;
}

template<typename T>
inline void write(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 ^ 48);
}

const double PI = acos(-1);
const double e = 2.718281828459;
const ll MOD = 1000000007;
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
#define fr first
#define sc second
#define MP make_pair
#define rep(i, a, n) for (int i = (a); i <= (n); i++)
#define per(i, a, n) for (int i = (a); i >= (n); i--)
#define mst(X, Y) memset(X, Y, sizeof(X))
#define setp(X)                                       \
    cout.setf(ios_base::fixed, ios_base::floatfield); \
    cout.precision((X))
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

void debug_out() { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#define writln(X) write(X), putchar('\n')
#define writsp(X) write(X), putchar(' ')
#define closeSync            \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)

inline void solve() {
    /*
        Code
    */
    return;
}

int main() {
    closeSync;
#ifdef DEBUG
    // freopen("xxx/in.txt", "r", stdin);
    // freopen("xxx/output.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}