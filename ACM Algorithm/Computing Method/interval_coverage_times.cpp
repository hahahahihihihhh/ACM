/*
    牛客 2021牛客寒假算法基础集训营2 G_牛牛与比赛颁奖（求区间覆盖n次对应的长度问题）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 100005;

int cnt[MAXN];
int ans[MAXN];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> team;

    for (int i = 1; i <= m; i++) {
        // second = -1 (左)，second = 1 (右)
        int l, r;
        cin >> l >> r;
        team.push_back({l, -1});
        team.push_back({r, 1});
    }

    sort(team.begin(), team.end());

    int tmp = 1;  // 临时变量

    for (int i = 1; i < team.size(); i++) {
        if (team[i - 1].second == -1)
            cnt[tmp] += team[i].first - team[i - 1].first + (team[i].second == 1);
        else
            cnt[tmp] += team[i].first - team[i - 1].first - (team[i].second == -1);
        tmp -= team[i].second;
    }

    int gd = (n + 9) / 10, sv = (n + 3) / 4, br = (n + 1) / 2;
    int tj = 0, tick = 1;

    // 1 : 金  2 : 银  3 : 铜
    for (int i = m; i >= 1; i--) {
        tj += cnt[i];
        ans[tick] += cnt[i];

        if (tick == 1 && tj >= gd) { // 金牌满了
            tick++;

            if (tj >= sv)
                tick++;

            if (tj >= br)
                break;
        } else if (tick == 2 && tj >= sv) { // 银牌满了
            tick++;

            if (tj >= br)
                break;
        } else if (tick == 3 && tj >= br) // 铜牌满了
            break;
    }

    for (int i = 1; i <= 3; i++)
        cout << ans[i] << " ";

    cout << endl;

    return;
}

int main() {
    closeSync;
    // int T; cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
10 10
1 10
2 10
3 10
4 10
5 10
6 10
7 10
8 10
9 10
10 10

1 2 2
*/