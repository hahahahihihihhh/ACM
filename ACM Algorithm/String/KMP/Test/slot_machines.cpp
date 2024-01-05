/*
    牛客 2021年度训练联盟热身训练赛第四场 I_Slot-Machines
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef pair<int, int> pii;
const int MAXN = 1000005;

int kmp[MAXN], a[MAXN];
inline void solve() {
    int n;
    cin >> n;
    for (int i = n; i >= 1; i--) cin >> a[i];
    kmp[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; i++) {// kmp 求循环节
        while (j && a[i] != a[j + 1]) j = kmp[j];
        if (a[i] == a[j + 1]) j++;
        kmp[i] = j;
    }
    vector<pii> ans;
    ans.push_back({n, 1});
    for (int i = 1; i <= n; i++) {
        int k = n - i, p = i - kmp[i];
        ans.push_back({p + k, p});
    }
    sort(ans.begin(), ans.end());
    cout << ans[0].first - ans[0].second << " " << ans[0].second << endl;
    return;
}

int main() {
    closeSync;
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
6
612534 3157 423 3157 423 3157

0 4
*/

