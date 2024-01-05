/*
    矩阵树（n个点m条边的无自环的无向图，统计其中生成树的数量）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;
const int MAXN = 105;

ll det[MAXN][MAXN];
int n, m;

inline ll gauss_kill() {
    ll ans = 1;
    for (int j = 1; j < n; j++) {
        int i;
        for (i = j; i <= n; i++)
            if (det[i][j])
                break;
        if (i == n)
            continue;
        if (i != j) {
            ans *= -1;
            for (int k = j; k < n; k++)
                swap(det[j][k], det[i][k]);
        }
        i += 1;
        for (i; i < n; i++) {
            while (det[i][j]) {
                ll t = det[i][j] / det[j][j];
                for (int k = j; k < n; k++)
                    det[i][k] = (det[i][k] - t * det[j][k] % MOD + MOD) % MOD;
                if (!det[i][j])
                    break;
                for (int k = j; k < n; k++)
                    swap(det[i][k], det[j][k]);
                ans *= -1;
            }
        }
    }
    for (int i = 1; i < n; i++)
        ans = (ans * det[i][i] + MOD) % MOD;
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        det[u][u]++;
        det[v][v]++;            //矩阵树定理
        det[u][v]--;
        det[v][u]--;
    }
    cout << gauss_kill() << endl;
    return 0;
}

/*
3 3 
1 2
1 3
2 3

3
*/