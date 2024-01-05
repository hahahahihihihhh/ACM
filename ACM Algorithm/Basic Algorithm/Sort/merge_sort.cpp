/*
    洛谷 P1177 【模板】排序（归并排序）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int a[MAXN];

void merge(int l, int mid, int r) {
    int p1 = l, p2 = mid + 1;
    int b[MAXN];
    for (int i = l; i <= r; i++) {
        if (p1 <= mid && (a[p1] <= a[p2] || p2 > r)) {
            b[i] = a[p1];
            p1++;
        } else {
            b[i] = a[p2];
            p2++;
        }
    }
    for (int i = l; i <= r; i++) a[i] = b[i];

}

void merge_sort(int l, int r) {
    int mid = (l + r) >> 1;
    if (l < r) {
        merge_sort(l, mid);
        merge_sort(mid + 1, r);
        merge(l, mid, r);
    }
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    merge_sort(1, n);
    for (int i = 1; i <= n; i++)
        cout << a[i] << (i == n ? "\n" : " ");
    return 0;
}

/*
5
4 2 4 5 1

1 2 4 4 5
*/