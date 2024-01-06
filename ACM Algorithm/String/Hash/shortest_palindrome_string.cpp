/*
    Leetcode 214 【模板】Shortest-palindrome（字符串哈希）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef unsigned long long ull;

const ull BASE = 29;
const int MAXN = 100005;

ull hsh[2][MAXN], POW[MAXN];
string s;
int n;

inline ull ask(int l, int r) {
    return hsh[0][r] - hsh[0][l - 1] * POW[r - l + 1];
}

inline ull rask(int L, int R) {
    return hsh[1][L] - hsh[1][R + 1] * POW[R - L + 1];
}

inline void solve() {
    cin >> s;
    n = s.size();
    s = " " + s;
    POW[0] = 1;
    for (int i = 1; i <= n; i++) {
        hsh[0][i] = hsh[0][i - 1] * BASE + (ull) (s[i] - 'a' + 1);
        POW[i] = POW[i - 1] * BASE;
    }
    for (int i = n; i >= 1; i--)
        hsh[1][i] = hsh[1][i + 1] * BASE + (ull) (s[i] - 'a' + 1);
    for (int i = n; i >= 1; i--) {
        if (ask(1, i) == rask(1, i)) {
            string tmp = s.substr(i + 1, n - i);
            reverse(tmp.begin(), tmp.end());
            cout << tmp + s.substr(1) << "\n";
            return;
        }
    }
}

int main() {
    closeSync;
//    int T;  cin >> T;
//    while (T--)
    solve();
    return 0;
}

/*
abcd
dcbabcd

aacecaaa
aaacecaaa
 */



