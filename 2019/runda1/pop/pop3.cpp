// Rozwiązanie brutalne do zadania 'Muzyka pop [1A]' Z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m)
// Złożoność pamięciowa: O(n * m)
// Punkty: 3 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 205, MAXM = 1 << 16 + 1;
constexpr ll INF = 1e18;
ll a[MAXN];

int C(ll n) { return __builtin_popcount(n); }

ll dp[MAXN][MAXM];
int32_t main() {
    int n;
    ll m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i];

    dp[1][0] = 0;
    for (int i = 0; i <= m; i++) {
        dp[1][i] = max(dp[1][i - 1], a[1] * C(i));
    }

    for (int i = 2; i <= n; i++) {
        dp[i][i - 2] = -INF;
        for (int last = i - 1; last <= m; last++) {
            dp[i][last] = max(dp[i][last - 1], dp[i - 1][last - 1] + a[i] * C(last));
        }
    }

    cout << dp[n][m] << "\n";
}