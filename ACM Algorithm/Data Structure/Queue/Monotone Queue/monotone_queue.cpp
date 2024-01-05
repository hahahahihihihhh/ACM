/*
    洛谷 P1886 滑动窗口/【模板】单调队列
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
struct Node {
    int val;
    int id;
};
deque<Node> dq;
int a[MAXN];

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        //递增队列求长度为 k 的区间 min
        while (!dq.empty() && a[i] <= dq.back().val)
            dq.pop_back();

        dq.push_back({a[i], i});

        if (dq.front().id + k <= dq.back().id)
            dq.pop_front();

        if (i >= k)
            cout << dq.front().val << " ";
    }

    cout << "\n";
    dq.clear();

    for (int i = 1; i <= n; i++) {
        //递减队列求长度为 k 的区间 max
        while (!dq.empty() && dq.back().val <= a[i])
            dq.pop_back();

        dq.push_back({a[i], i});

        if (dq.front().id + k <= dq.back().id)
            dq.pop_front();

        if (i >= k)
            cout << dq.front().val << " ";
    }

    cout << "\n";
    return 0;
}

/*
8 3
1 3 -1 -3 5 3 6 7

-1 -3 -3 -3 3 3
3 3 5 5 6 7
*/