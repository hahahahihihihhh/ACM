/*
    分块求和（向上取整）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    // ans = w/1 + w/2 + w/3 + ..... + w/n （ / 表示向上取整 ）
    ll n, w;
    cin >> n >> w;
    ll ans = 0;

    for (ll l = 1, r; l <= n; l = r + 1) {
        if ((w - 1) / l)
            r = (w - 1) / ((w - 1) / l);
        else
            r = n;          // 限制  w - 1 < n

        r = min(r, n);      // 限制  w > n
        ans += (r - l + 1) * ((w - 1) / l + 1);         // 求和，l —— r 的值全为  (w - 1) / l + 1
        //cout << l << " " << r << ": " << (w - 1) / l + 1 << "\n";
    }

    cout << ans << endl;
    return 0;
}

/*
100 100
573
*/