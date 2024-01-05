/*
    洛谷 P3809 【模板】后缀排序
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

struct SA {
    int n, cnt[MAXN], old_rk[MAXN << 1], sa[MAXN], rk[MAXN], px[MAXN], id[MAXN];
    string s;
    int H[MAXN];

    inline bool cmp(int x, int y, int w) {
        return old_rk[x] == old_rk[y] && old_rk[x + w] == old_rk[y + w];
    }

    inline void init(string _s) {
        n = _s.size();
        s = " " + _s;
    }

    inline void get_SA() {
        int p, m = max(n, 300);

        for (int i = 1; i <= n; i++)
            cnt[rk[i] = s[i]]++; // 计数排序

        for (int i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1; i--)
            sa[cnt[rk[i]]--] = i;

        for (int w = 1;; w <<= 1, m = p) { // m为值域
            // 倍增
            p = 0;

            for (int i = n; i > n - w; i--)
                id[++p] = i;    // 先按第二关键字排序

            for (int i = 1; i <= n; i++)
                if (sa[i] > w)
                    id[++p] = sa[i] - w;

            assert(p == n);

            for (int i = 1; i <= m; i++)
                cnt[i] = 0;     // 再按照第一关键字基数排序

            for (int i = 1; i <= n; i++)
                cnt[px[i] = rk[id[i]]]++;   // px[i]为关键字

            for (int i = 1; i <= m; i++)
                cnt[i] += cnt[i - 1];

            for (int i = n; i >= 1; i--)
                sa[cnt[px[i]]--] = id[i];

            for (int i = 1; i <= n; i++)
                old_rk[i] = rk[i];

            p = 0;

            for (int i = 1; i <= n; i++) // 获得 rk 数组
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;

            if (p == n) {
                // 每个rk不相同，后缀已经有序
                for (int i = 1; i <= n; i++)
                    sa[rk[i]] = i;

                break;
            }
        }
    }

    inline void get_Height() {
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 1)
                continue;

            int l = rk[i], r = rk[i - 1];
            int j = sa[l - 1];
            int len = max(0, H[r] - 1);

            while (i + len <= n && s[i + len] == s[j + len])
                len++;

            H[l] = len;
        }

        H[1] = H[n + 1] = -1;
    }
} fff;

int main() {
    string s;
    cin >> s;
    fff.init(s);
    fff.get_SA();

    for (int i = 1; i <= fff.n; i++)
        cout << fff.sa[i] << (i == fff.n ? "\n" : " ");

    return 0;
}

/*
ababa
5 3 1 4 2
*/