/*
    洛谷 P3383 【模板】线性筛素数
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e8 + 10;
int isnotprime[MAXN], prime[MAXN];
int cnt = 0;

inline void init(int n) {
    isnotprime[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!isnotprime[i]) {
            prime[++cnt] = i;

            for (ll j = (ll) i * i; j <= n; j += i) {
                isnotprime[j] = 1;
            }
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    init(n);

    while (q--) {
        int k;
        cin >> k;
        cout << prime[k] << "\n";
    }

    return 0;
}

/*
100 5
1
2
3
4
5

2
3
5
7
11
*/