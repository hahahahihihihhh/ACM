/*
    洛谷 P3805 【模板】manacher
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 11000005;

int r[MAXN << 1];              // 表示以 i 为中心的最长半径

inline int manacher(string str) {
    string tmp = " ?#";
    int ed = str.size() - 1;

    for (int i = 0; i <= ed; i++) {
        tmp.push_back(str[i]);
        tmp.push_back('#');
    }

    int n = tmp.size() - 1;
    int L = 1, C = 1; // 回文串的最右端，及其中心位置
    int mx = 1;

    for (int i = 2; i <= n - 1; i++) {
        if (i > L || i + r[2 * C - i] - 1 >= L) {  // r[i] 还会继续增大 , L还可继续扩张 .
            C = i;
            r[i] = L - i + 1;

            while (tmp[C + r[i]] == tmp[C - r[i]])
                r[i]++;

            L = C + r[i] - 1;
        } else if (i + r[2 * C - i] - 1 < L) // 答案可从对称位置转移
            r[i] = r[2 * C - i];

        mx = max(r[i], mx);
    }

    return mx - 1;
}

int main() {
    string str;
    cin >> str;
    cout << manacher(str) << "\n";
    return 0;
}

/*
aaa
3
*/