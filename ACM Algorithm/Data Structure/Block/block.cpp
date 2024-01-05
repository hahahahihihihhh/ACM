/*
    LibreOJ #6277 数列分块入门1
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const int MAXN = 100005;

ll a[MAXN], add[MAXN];
int bl[MAXN], L[MAXN], R[MAXN];

inline void init(int n) {
    int len = sqrt(n), t, i; //块长为len,块数为 t

    for (int i = 1; i <= n; i++)
        bl[i] = (i - 1) / len + 1;

    for (i = 1, t = 1; i <= n; i += len, t++)
        L[t] = R[t - 1] + 1, R[t] = R[t - 1] + len;

    R[t] = n;
}
inline void change(int l, int r, ll c) {
    int p = bl[l], q = bl[r];

    if (p == q) {
        for (int i = l; i <= r; i++)
            a[i] += c;

        return;
    }

    for (int t = p + 1; t <= q - 1; t++)
        add[t] += c;

    for (int i = l; i <= R[p]; i++)
        a[i] += c;

    for (int i = L[q]; i <= r; i++)
        a[i] += c;

    return;
}
inline ll query(int x) {
    return a[x] + add[bl[x]];
}

int main() {
    closeSync;
    int n;
    cin >> n;
    init(n);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        int opt, l, r;
        ll c;
        cin >> opt >> l >> r >> c;

        if (opt)
            cout << query(r) << "\n";
        else
            change(l, r, c);
    }

    return 0;
}

/*
4
1 2 2 3
0 1 3 1
1 0 1 0
0 1 2 2
1 0 2 0

2
5
*/