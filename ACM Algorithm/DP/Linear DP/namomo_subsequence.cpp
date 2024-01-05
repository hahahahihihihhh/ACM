/*
    Codeforces 2020-ICPC-Asia-East-Continent-Final A_Namomo-Subsequence
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 1000005;
const int LIM = 61 + 2;
typedef long long ll;
const ll MOD = 998244353;

int num[MAXN];
ll tj1[LIM], tj2[LIM][LIM], tj3[LIM][LIM], tj4[LIM], tj5[LIM][LIM], tj[LIM];
int dp1[MAXN][LIM], dp2[MAXN][LIM], dp3[MAXN][LIM];
ll sumdif;
ll tjx_[LIM], tj_x[LIM];
int lim = 61;

inline void solve() {
    string str;
    cin >> str;
    int len = str.size();
    str = " " + str;
    for (int i = 1; i <= len; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            num[i] = str[i] - '0';
        else if (str[i] >= 'A' && str[i] <= 'Z')
            num[i] = str[i] - 'A' + 10;
        else
            num[i] = str[i] - 'a' + 36;
    }
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j <= lim; j++) {
            if (j == num[i]) continue;
            dp1[i][j] = tj1[j];
        }
        tj1[num[i]]++;
    }
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j <= lim; j++) {
            if (j == num[i]) continue;
            dp2[i][j] = tj2[j][num[i]];
        }
        for (int j = 0; j <= lim; j++) {
            tj2[num[i]][j] += dp1[i][j];
            tj2[num[i]][j] %= MOD;
        }
    }
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j <= lim; j++) {
            if (j == num[i]) continue;
            dp3[i][j] = tj3[j][num[i]];
        }
        for (int j = 0; j <= lim; j++) {
            tj3[num[i]][j] += dp2[i][j];
            tj3[num[i]][j] %= MOD;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j <= lim; j++) {
            ll t = ((sumdif - tj_x[num[i]] - tj_x[j] - tjx_[num[i]] - tjx_[j] + 4LL * MOD) % MOD
                + tj5[j][num[i]] + tj5[num[i]][j]) % MOD;
            ans += dp3[i][j] * t;
            ans %= MOD;
        }
        for (int j = 0; j <= lim; j++) {
            if (num[i] != j) {
                sumdif += tj[j], tjx_[j] += tj[j], tj_x[num[i]] += tj[j], tj5[j][num[i]] += tj[j];
                sumdif %= MOD, tjx_[j] %= MOD, tj_x[num[i]] %= MOD, tj5[j][num[i]] %= MOD;
            }
        }
        tj[num[i]]++;
    }
    cout << ans << "\n";
}

int main() {
    closeSync;
    // int  T; cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
gshfd1jkhaRaadfglkjerVcvuy0gf
73
*/