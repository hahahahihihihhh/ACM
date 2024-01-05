/*
    洛谷 P5788 【模板】单调栈
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3000005;

int a[MAXN];
int f[MAXN];
int stk[MAXN], cnt = 0;
int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = n; i >= 1; i--) {
        while (cnt && a[i] >= a[stk[cnt]])
            cnt--;

        f[i] = stk[cnt];
        stk[++cnt] = i;
    }

    for (int i = 1; i <= n; i++)
        cout << f[i] << (i == n ? "\n" : " ");

    return 0;
}

/*
5
1 4 2 3 5

2 5 4 5 0
*/