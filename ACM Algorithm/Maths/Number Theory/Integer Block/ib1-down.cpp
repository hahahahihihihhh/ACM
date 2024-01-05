/*
    分块求和（向下取整）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    // ans = w/1 + w/2 + w/3 + ..... + w/n （ / 表示向下取整 ）
    ll n, w, ans = 0;
    cin >> n >> w;

    for (ll l = 1, r; l <= n; l = r + 1) {
        if (w / l)
            r = w / (w / l);
        else
            r = n;                  // 限制 w < n

        r = min(r, n);                  // 限制  w > n
        ans += (r - l + 1) * (n / l);   // 求和，// l —— r 的值全为  w / l
        //cout << l << " " << r << ": " <<  w / l << endl;   // 分块
    }

    cout << ans << "\n";
    return 0;
}

/*
100 100
482
*/