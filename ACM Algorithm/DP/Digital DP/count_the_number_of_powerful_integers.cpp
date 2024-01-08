/*
    Leetcode 10034 Count-the-Number-of-Powerful-Integers（数位dp）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;

int d[20], false_lim;
string dig, suf, st, ed;
ll dp[20];

inline ll dfs(int pos, int lead_zero, int ture_lim) {
    if (pos < suf.size())
        return 0;
    if (pos == suf.size()) {
        if (!ture_lim)
            return 1;
        else
            return stoll(suf) <= stoll(dig.substr(max(0, (int) dig.size() - (int) suf.size())));
    }
    if (!ture_lim && !lead_zero && dp[pos])
        return dp[pos];
    int up = ture_lim == 1 ? min(false_lim, d[pos]) : false_lim;
    ll ans = 0;
    for (int i = 0; i <= up; i++)
        ans += (dfs(pos - 1, (lead_zero && i == 0), ture_lim && (false_lim >= d[pos] && i == up)));
    if (!lead_zero && !ture_lim)
        dp[pos] = ans;
    return ans;
}

inline ll solve(string num) {
    dig = num;
    int len = num.size();
    for (int i = len - 1; i >= 0; i--)
        d[len - i] = num[i] - '0';
    return dfs(len, true, true);
}

inline bool check(string num) {
    if (num.substr(max(0, (int) num.size() - (int) suf.size())) != suf) return false;
    for (int i = 0; i < num.size(); i++)
        if (num[i] - '0' > false_lim)
            return false;
    return true;
}

void solve() {
    cin >> st >> ed >> false_lim >> suf;
    cout << solve(ed) - solve(st) + check(st) << "\n";
}

int main() {
    closeSync;
//    int T; cin >> T;
//    while (T--)
    solve();
    return 0;
}

/*
1 6000 4 124
5

15 215 6 10
2

1000 2000 4 3000
0
*/