/*
    洛谷 P1908 逆序对（归并排序）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 500005;
typedef long long ll;

int a[MAXN];
int tmp[MAXN];
ll invCnt = 0;

inline void merge(int l, int mid, int r) {
    int tk1 = l, tk2 = mid + 1;
    for (int i = l; i <= r; i++) {
        if (tk2 > r || tk1 <= mid && a[tk1] <= a[tk2])
            tmp[i] = a[tk1++];
        else {
            tmp[i] = a[tk2++];
            invCnt += mid - tk1 + 1;
        }
    }
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}

inline void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
}

inline void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    merge_sort(1, n);
    cout << invCnt << "\n";
    return;
}

int main() {
    closeSync;
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
6
5 4 2 6 3 1

11
*/