/*
    洛谷 P3812 【模板】线性基
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int LIM = 60;
typedef long long ll;

ll S[MAXN];
struct LB {
    ll a[LIM + 5], p[LIM + 5];
    int cnt = 0;

    inline void init() {
        cnt = 0;

        for (int i = 1; i <= LIM; i++)
            a[i] = p[i] = 0;
    }
    inline bool getbit(ll x, int pos) {
        return (x >> (pos - 1)) & 1;
    }
    inline bool insert(ll x) {
        for (int i = LIM; i >= 1; i--)
            if (getbit(x, i)) {
                if (!a[i]) {
                    a[i] = x;
                    return true;
                }

                x ^= a[i];
            }

        return false;
    }
    inline void merge(const LB &lb) {
        for (int i = 1; i <= LIM; i++)
            if (lb.a[i])
                insert(lb.a[i]);
    }
    inline ll maxXor() {
        ll ans = 0;

        for (int i = LIM; i >= 1; i--)
            ans = max(ans, ans ^ a[i]);

        return ans;
    }
    inline ll minXor() {
        for (int i = 1; i <= LIM; i++)
            if (a[i])
                return a[i];

        return 0;
    }
    inline void rebuild() {
        for (int i = LIM; i >= 1; i--)
            for (int j = i - 1; j >= 1; j--)
                if (getbit(a[i], j))
                    a[i] ^= a[j];

        for (int i = 1; i <= LIM; i++)
            if (a[i])
                p[++cnt] = a[i];
    }
    inline ll KthSmall(ll k) {  // 先rebuild
        if (k >= (1LL << cnt) || k <= 0)
            return -1;

        ll ans = 0;

        for (int i = 1; i <= cnt; i++)
            if (getbit(k, i))
                ans ^= p[i];

        return ans;
    }
} fff;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> S[i];
        fff.insert(S[i]);
    }

    cout << fff.maxXor() << "\n";
    return 0;
}

/*
10
681519689123291 153992348230057 352917520953222 379410980430607 333284887124912 596782649548897 1004880543767517 258503666829624 353486948696275 244563245470691

1125412639244478
*/