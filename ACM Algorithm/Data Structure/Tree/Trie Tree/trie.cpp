/*
    洛谷 P2580 于是他错误的点名开始了（字典树）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int LIM = 30;
map<string, int> mp;

struct Trie {   // trie树（字典树）
    int trie[MAXN][LIM];      //trie[a][c] 表示 a 节点连出去的字母为 c 的边的节点编号
    int endWords[MAXN];     //存放终止节点
    int tot = 1;

    void init() {
        tot = 1;
        memset(trie, 0, sizeof(trie));
        memset(endWords, 0, sizeof(endWords));
    }
    void insert(string str) {
        int ed = str.size() - 1;
        int now = 1;

        for (int i = 0; i <= ed; i++) {
            int c = str[i] - 'a';

            if (trie[now][c])
                now = trie[now][c];
            else {
                trie[now][c] = ++tot;
                now = tot;
            }
        }

        endWords[now] = 1;
        return;
    }
    bool query(string str) {
        int ed = str.size() - 1;
        int now = 1;

        for (int i = 0; i <= ed; i++) {
            int c = str[i] - 'a';

            if (!trie[now][c])
                return false;

            now = trie[now][c];
        }

        return true;
    }
} fff;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        fff.insert(name);
    }

    int m;
    cin >> m;

    for (int i = 1; i <= m; i++) {
        string name;
        cin >> name;
        mp[name] += fff.query(name);

        switch (mp[name]) {
            case 0:cout << "WRONG\n";
                break;

            case 1:cout << "OK\n";
                break;

            default:cout << "REPEAT\n";
                break;
        }
    }

    return 0;
}

/*
5
a
b
c
ad
acd
3
a
a
e

OK
REPEAT
WRONG
*/