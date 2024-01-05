/*
    洛谷 P3375 【模板】KMP字符串匹配
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct KMP {
    int kmp[MAXN];

    void getkmp(string pattern) {  // 获得 kmp 数组
        int j = 0, lenp = pattern.size();
        pattern = " " + pattern;
        kmp[1] = 0;

        for (int i = 2; i <= lenp; i++) {
            while (j && pattern[i] != pattern[j + 1])
                j = kmp[j];

            if (pattern[i] == pattern[j + 1])
                j++;

            kmp[i] = j;
        }
    }
    void kmpit(string txt, string pattern) {  // 匹配
        getkmp(pattern);
        int j = 0, lent = txt.size(), lenp = pattern.size();
        txt = " " + txt, pattern = " " + pattern;

        for (int i = 1; i <= lent; i++) {
            while (j && txt[i] != pattern[j + 1])
                j = kmp[j];

            if (txt[i] == pattern[j + 1])
                j++;

            if (j == lenp) {
                cout << i - j + 1 << endl;  // 模式串在文本串中的出现位置
                j = kmp[j];
            }
        }
    }
};

int main() {
    string txt, pattern;
    cin >> txt >> pattern;
    KMP kmp;
    kmp.kmpit(txt, pattern);
    int lenp = pattern.size();

    for (int i = 1; i <= lenp; i++)
        cout << kmp.kmp[i] << (i == lenp ? "\n" : " ");

    return 0;
}

/*
ABABABC
ABA

1
3
0 0 1
*/