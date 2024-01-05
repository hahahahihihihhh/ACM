/*
    ZOJ The-16th-Zhejiang-Provincial-Collegiate-Programming-Contest K_Strings-in-the-Pocket
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 2000005;
typedef long long ll;

int r[MAXN << 1];
inline void manacher(string str) {
    string tmp = " ?#";
    int ed = str.size() - 1;
    for (int i = 0; i <= ed; i++)
        tmp.push_back(str[i]), tmp.push_back('#');
    int n = tmp.size() - 1;
    int L = 1, C = 1;
    for (int i = 2; i <= n - 1; i++) {
        if (i > L || i + r[2 * C - i] - 1 >= L) {
            C = i;
            r[i] = L - i + 1;
            while (tmp[C + r[i]] == tmp[C - r[i]])
                r[i]++;
            L = C + r[i] - 1;
        } else if (i + r[2 * C - i] - 1 < L)
            r[i] = r[2 * C - i];
    }
}

inline void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    for (int i = 0; i <= 2 * n + 5; i++)
        r[i] = 0;

    s = " " + s;
    t = " " + t;
    int head = 1, tail = n;

    while (head <= n && s[head] == t[head])
        head++;
    if (head > n) {
        manacher(s.substr(1, n));

        ll ans = 0;
        for (int i = 2; i <= 2 * n + 2; i++)
            ans += r[i] / 2;

        cout << ans << "\n";
        return;
    }
    while (tail >= 1 && s[tail] == t[tail])
        tail--;
    if (tail == head) {
        cout << "0\n";
        return;
    }

    int tickl = head, tickr = tail;
    while (tickl <= tail && s[tickl] == t[tickr])
        tickl++, tickr--;

    if (tickl <= tail) {
        cout << "0\n";
        return;
    }

    string str = "";
    for (int i = 1; i < head; i++)
        str.push_back(s[i]);
    for (int i = tail + 1; i <= n; i++)
        str.push_back(s[i]);
    manacher(str);
    int tick = 2 * (head - 1) + 2;

    cout << (1 + r[tick] / 2) << "\n";

    return;
}

int main() {
    closeSync;
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
5
aaabcaa
aacbaaa
aaaaa
aaaaa
abcdef
abcdfe
asdasd
asdddd
edaa
deaa

3
15
1
0
1
*/



