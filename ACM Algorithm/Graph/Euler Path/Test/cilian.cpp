/*
	洛谷 P1127 词链（欧拉通路）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 1005;
const int LIM = 26;
typedef pair<int, int> pii;

int in[MAXN], out[MAXN], vis[MAXN], hh[LIM + 5];
vector<pii> G[MAXN];
string words[MAXN];
int tk[MAXN], stk[MAXN], top;
int n;

void dfs(int u) {
    int ed = G[u].size() - 1;
    for (int i = tk[u]; i <= ed; i++) {
        int e = G[u][i].first, v = G[u][i].second;
        if (vis[e]) continue;
        vis[e] = 1;
        tk[u] = i + 1;
        dfs(v);
        stk[++top] = e;
    }
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> words[i];
    sort(words + 1, words + n + 1);
    for (int i = 1; i <= n; i++) {
        int ed = words[i].size() - 1;
        int u = words[i][0] - 'a' + 1, v = words[i][ed] - 'a' + 1;
        hh[u] = hh[v] = 1;
        G[u].push_back({i, v});
        out[u]++, in[v]++;
    }
    int st = 0, ed = 0;
    for (int i = 1; i <= LIM; i++) {
        if (in[i] == out[i]) continue;
        if (out[i] > in[i] && out[i] - in[i] == 1) {
            if (st) {
                cout << "***\n";
                return;
            }
            st = i;
        } else if (in[i] > out[i] && in[i] - out[i] == 1) {
            if (ed) {
                cout << "***\n";
                return;
            }
            ed = i;
        } else {
            cout << "***\n";
            return;
        }
    }
    if (st && ed) {
        dfs(st);
        if (top != n) {
            cout << "***\n";
            return;
        }
        for (int i = top; i >= 1; i--)
            cout << words[stk[i]] << (i == 1 ? "\n" : ".");
    } else if (!st && !ed) {
        for (int i = 1; i <= LIM; i++) {
            if (hh[i]) {
                dfs(i);
                if (top != n) {
                    cout << "***\n";
                    return;
                }
                for (int i = top; i >= 1; i--)
                    cout << words[stk[i]] << (i == 1 ? "\n" : ".");
                return;
            }
        }
    } else
        cout << "***\n";
    return;
}

int main() {
    closeSync;
    solve();
    return 0;
}

/*
6
aloha
arachnid
dog
gopher
rat
tiger

aloha.arachnid.dog.gopher.rat.tiger
*/
 