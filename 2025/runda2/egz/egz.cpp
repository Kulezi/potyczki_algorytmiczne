// Rozwiązanie do zadania 'Egzamin [2A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2 * c) gdzie c to ~ 1/50.
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;
using ld = long double;
constexpr int MAXN = 50'005, OFFSET = 50'000, INF = 4 * OFFSET;
constexpr ld TAK_MALO_ZE_MOGE_ZAPOMNIEC = 2e-11;
ld p[MAXN], dp[2 * MAXN][2];

// Mały paranoik.
bool jedynka(string s) {
    return s == "1" || s == "1.0" || s == "1.00" || s == "1.000" || s == "1.0000" ||
           s == "1.00000" || s == "1.000000" || s == "1.0000000" || s == "1.00000000" ||
           s == "1.000000000";
}

int main() {
    ios_base::sync_with_stdio(0);

    int n, t;
    cin >> n >> t;
    int darmowe = 0;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        stringstream sz(s);
        sz >> p[i];

        if (jedynka(s)) darmowe++;
    }

    sort(p + 1, p + n + 1, [](ld a, ld b) { return a > b; });

    t -= darmowe;

    if (t <= 0) {
        cout << "1\n";
        return 0;
    }

    ld wynik = 0;

    dp[OFFSET][darmowe % 2] = 1;

    int zywe_l = OFFSET, zywe_r = OFFSET;
    for (int i = darmowe + 1; i <= n; i++) {
        int par = i % 2;

        int nowe_zywe_l = INF, nowe_zywe_r = -INF;
        for (int k = zywe_l - 1; k <= zywe_r + 1; k++) {
            dp[k][par] = dp[k - 1][1 - par] * p[i] + dp[k + 1][1 - par] * (1 - p[i]);
            if (dp[k][par] > TAK_MALO_ZE_MOGE_ZAPOMNIEC) {
                if (nowe_zywe_l == INF) nowe_zywe_l = k;
                nowe_zywe_r = k;
            }
        }

        for (int k = zywe_l; k <= zywe_r; k++) dp[k][1 - par] = 0;

        zywe_l = nowe_zywe_l;
        zywe_r = nowe_zywe_r;

        ld kandydat = 0;
        for (int k = max(t + OFFSET, nowe_zywe_l); k <= nowe_zywe_r; k++) {
            kandydat += dp[k][par];
        }

        if (kandydat > wynik) wynik = kandydat;
    }

    cout << fixed << setprecision(9) << wynik << "\n";
}