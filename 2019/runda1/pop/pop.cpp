// Rozwiązanie do zadania 'Muzyka pop [1A]' Z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3*log(max_m))
// Złożoność pamięciowa: O(n^2*log(max_m))
// Punkty: 10 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 205, MAX_LOG = 60;
constexpr ll INF = 1e18;
ll a[MAXN], pref[MAXN];
ll sum(int l, int r) {
    if (l > r) return 0;
    return pref[r] - pref[l - 1];
}

// (lewy koniec, prawy koniec, prefiks bitów, czy mogę już brać wszystko)
ll dp[MAXN][MAXN][MAX_LOG + 1][2];
ll m;

inline void relax(ll &x, ll y) {
    if (x < y) x = y;
}

ll solve(int l, int r, ll lg, int any) {
    if (l > r) return 0;
    if (lg < 0) return 0;
    if (dp[l][r][lg][any] != -INF) return dp[l][r][lg][any];
    if (any) {
        ll full = (1LL << lg) - 1;
        // Wybieram od którego indeksu ten bit będzie równy 1, to gwarantuje, że wszystko na
        // lewo od tej pozycji będzie mniejsze od wszystkiego na prawo.
        for (int start_ones = l; start_ones <= r + 1; start_ones++) {
            int left = start_ones - l;
            int right = r - start_ones + 1;
            if (left <= full + 1 && right <= full + 1) {
                relax(dp[l][r][lg][any], solve(l, start_ones - 1, lg - 1, true) +
                                             solve(start_ones, r, lg - 1, true) +
                                             sum(start_ones, r));
            }
        }
    } else {
        // Skoro nie ma tu zapalonego bitu to nie mogę nic zapalić.
        if (!(m >> lg & 1))
            return dp[l][r][lg][any] = solve(l, r, lg - 1, any);
        else {
            ll full = (1LL << lg) - 1;
            ll rest = m & full;
            // Wybieram od którego indeksu ten bit będzie równy 1, to gwarantuje, że wszystko na
            // lewo od tej pozycji będzie mniejsze od wszystkiego na prawo.
            for (int start_ones = l; start_ones <= r + 1; start_ones++) {
                int left = start_ones - l;
                int right = r - start_ones + 1;
                if (left <= full + 1 && right <= rest + 1) {
                    relax(dp[l][r][lg][any], solve(l, start_ones - 1, lg - 1, true) +
                                                 solve(start_ones, r, lg - 1, false) +
                                                 sum(start_ones, r));
                }
            }
        }
    }

    return dp[l][r][lg][any];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n >> m;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 0; k <= MAX_LOG; k++)
                for (int l = 0; l < 2; l++) dp[i][j][k][l] = -INF;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    cout << solve(1, n, MAX_LOG, 0) << "\n";
}