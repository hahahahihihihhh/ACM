/*
    洛谷 P1177 【模板】排序（快速排序）
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int a[MAXN];

void quick_sort(int l, int r) {
    int p1 = l, p2 = r;
    int x = a[(l + r) >> 1];
    while (p1 < p2) {
        while (a[p1] < x) p1++;
        while (a[p2] > x) p2--;
        if (p1 <= p2) {
            swap(a[p1], a[p2]);
            p1++, p2--;
        }
    }
    if (l < p2) quick_sort(l, p2);
    if (p1 < r) quick_sort(p1, r);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    quick_sort(1, n);
    for (int i = 1; i <= n; i++)
        cout << a[i] << (i == n ? "\n" : " ");
    return 0;
}

/*
5
4 2 4 5 1

1 2 4 4 5
*/