// Rozwiązanie do zadania 'Muzyka pop [1A]' Z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3*log(max_m))
// Złożoność pamięciowa: O(n^2*log(max_m))
// Punkty: 10 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_BIT = 61;
ll a[205];
ll dp[205][205][123];

int highest_bit(ll x) {
    for (int i = MAX_BIT; i >= 0; i--) {
        if (x >> i & 1) return i;
    }
    return 0;
}

int max_ones(ll x) { return max(highest_bit(x), __builtin_popcountll(x)); }

vector<ll> get_interesting(ll m) {
    vector<ll> interesting;
    for (ll i = 2; i <= m; i *= 2) interesting.push_back(i - 1);
    while (m > 0) {
        interesting.push_back(m);
        m -= (1LL << highest_bit(m));
    }

    sort(interesting.begin(), interesting.end());
    interesting.erase(unique(interesting.begin(), interesting.end()), interesting.end());
    return interesting;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    ll m;

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto interesting = get_interesting(m);
    map<ll, int> idx;

    idx[0] = 0;
    for (int i = 1; i <= interesting.size(); i++) {
        ll k = interesting[i - 1];
        idx[k] = i;
        int B = highest_bit(k);
        ll without_one = k - (1LL << B);
        ll full = (1LL << B) - 1;

        int full_idx = idx[full];
        int without_idx = idx[without_one];
        for (int l = 1; l <= n; l++) dp[l][l][i] = max(0LL, a[l]) * max_ones(k);

        for (int l = 1; l <= n; l++) {
            for (int r = l + 1; r <= n; r++) {
                dp[l][r][i] = -2e18;
                if (k < r - l) continue;

                ll sum = 0;
                for (int mid = r; mid >= l; mid--) {
                    if (full >= mid - l && without_one >= r - (mid + 1))
                        dp[l][r][i] = max(dp[l][r][i],
                                          sum + dp[l][mid][full_idx] + dp[mid + 1][r][without_idx]);
                    sum += a[mid];
                }

                if (without_idx >= r - l)
                    dp[l][r][i] = max(dp[l][r][i], sum + dp[l][r][without_idx]);
            }
        }
    }

    cout << dp[1][n][idx[m]] << "\n";
}