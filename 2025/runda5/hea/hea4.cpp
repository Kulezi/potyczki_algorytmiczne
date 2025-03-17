// Rozwiązanie brutalne do zadania 'Heavy metal [5B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(c * log(c) * n * (n + m)), gdzie c to liczba osiągalnych iloczynów
// Złożoność pamięciowa: O(n * c)
// Punkty: 4

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
constexpr int MAXN = 105, MAXM = 205;

int p[MAXN];
vector<pair<int, int>> g[MAXN];
vector<int> ones[MAXN];

map<int, bitset<MAXN>> dp;

int solve() {
    dp.clear();
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        g[i].clear();
        ones[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int a, b, w;
        cin >> a >> b >> w;

        if (w == 1)
            ones[a].push_back(b);
        else if (w <= p[n])
            g[a].push_back({b, w});
    }
    int wynik = -1;

    dp[1][1] = 1;
    int ilo = 0;
    while (1) {
        auto it = dp.upper_bound(ilo);
        if (it == dp.end()) break;
        auto &[X, moje] = *it;
        ilo = X;

        for (int reps = 1; reps <= n; reps++) {
            for (int src = 1; src <= n; src++) {
                if (moje[src]) {
                    for (auto dst : ones[src]) {
                        if (p[dst] >= ilo) moje[dst] = true;
                    }
                }
            }
        }

        for (int src = 1; src <= n; src++) {
            if (moje[src]) {
                for (auto [dst, w] : g[src]) {
                    if (p[dst] >= 1LL * ilo * w) {
                        dp[ilo * w][dst] = true;
                    }
                }
            }
        }

        if (moje[n]) wynik = ilo;
    }

    return wynik;
}

int main() {
    ios_base::sync_with_stdio(0);

    int T = 1;
    cin >> T;
    while (T--) {
        cout << solve() << "\n";
    }
}