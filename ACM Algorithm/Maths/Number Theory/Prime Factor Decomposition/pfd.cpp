/*
    洛谷 P1075 [NOIP2012-普及组]-质因数分解
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> pfd(ll n) {
    vector<ll> ans;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n = n / i;
            ans.push_back(i);
        }
    }
    if (n != 1)
        ans.push_back(n);
    return ans;
}

int main() {
    ll n;
    cin >> n;
    vector<ll> tmp = pfd(n);
    sort(tmp.begin(), tmp.end());
    cout << tmp[1] << "\n";
}

/*
21

7
*/