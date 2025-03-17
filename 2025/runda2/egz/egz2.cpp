// Rozwiązanie wolne do zadania 'Egzamin [2A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2).
// Złożoność pamięciowa: O(n)
// Punkty: 2

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;
using ld = long double;
constexpr int MAXN = 50'005, OFFSET = 50'000;
ld p[MAXN], dp[2 * MAXN][2];
int main() {
    ios_base::sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    sort(p + 1, p + n + 1, [](ld a, ld b) { return a > b; });

    ld wynik = 0;

    dp[OFFSET][0] = 1;
    for (int i = 1; i <= n; i++) {
        int par = i % 2;
        ld kandydat = 0;

        for (int ile = OFFSET - i; ile <= OFFSET + i; ile++) {
            dp[ile][par] = dp[ile - 1][1 - par] * p[i] + dp[ile + 1][1 - par] * (1 - p[i]);
        }

        for (int ile = OFFSET + t; ile <= OFFSET + i; ile++) kandydat += dp[ile][par];

        wynik = max(wynik, kandydat);
    }

    cout << fixed << setprecision(9) << wynik << "\n";
}