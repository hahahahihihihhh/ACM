/*
    洛谷 P5357 【模板】AC自动机（二次加强版）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
typedef long long ll;
const int LIM = 26;

int n; // 模式串的数目
struct AC {
    struct Tree {
        int ch[26];
        int fail;
        int ans;   //该模式串目前的贡献
        string endstr; // 终止字符串
    } t[MAXN];
    map<string, int> mp; // 该模式串匹配了几次
    int n, tot = 0, indegree[MAXN];

    inline void init() {
        // tot 为模式串的数目
        mp.clear();

        for (int i = 0; i <= tot; i++) {
            for (int j = 0; j < LIM; j++)
                t[i].ch[j] = 0;

            indegree[i] = t[i].fail = t[i].ans = 0;
            t[i].endstr = "";
        }

        tot = 0;
    }

    inline void insert(string s) {
        // 字典树中插入字符串
        int len = s.size();
        int now = 0;

        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';

            if (!t[now].ch[c])
                t[now].ch[c] = ++tot;

            now = t[now].ch[c];
        }

        t[now].endstr = s;
    }

    inline void get_fail() {
        // 建 fail 边
        queue<int> q;

        for (int i = 0; i < LIM; i++)
            if (t[0].ch[i])
                q.push(t[0].ch[i]);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < LIM; i++) {
                if (t[u].ch[i]) {
                    t[t[u].ch[i]].fail = t[t[u].fail].ch[i];
                    indegree[t[t[u].fail].ch[i]]++;
                    q.push(t[u].ch[i]);
                } else
                    t[u].ch[i] = t[t[u].fail].ch[i];
            }
        }
    }

    inline void tpsort() {
        // 拓扑排序跑 fail 边
        queue<int> q;

        for (int i = 1; i <= tot; i++)
            if (indegree[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (t[u].endstr != "")
                mp[t[u].endstr] = t[u].ans;

            int v = t[u].fail;
            indegree[v]--;
            t[v].ans += t[u].ans;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    inline void ac_query(string s) {    // 询问 s 串在各模式串中出现的次数，答案存在 mp 中
        int len = s.size();
        int now = 0;

        for (int i = 0; i < len; i++) {
            now = t[now].ch[s[i] - 'a'];
            t[now].ans++;
        }

        tpsort();
        return;
    }
} fff;

int main() {
    cin >> n;
    vector<string> v;
    fff.init();

    while (n--) {
        string s;
        cin >> s;
        fff.insert(s);
        v.push_back(s);
    }

    fff.get_fail();
    string ans;
    cin >> ans;
    fff.ac_query(ans);

    for (auto c: v)
        cout << fff.mp[c] << endl;

    return 0;
}

/*
5
a
bb
aa
abaa
abaaa
abaaabaa

6
0
3
2
1
*/