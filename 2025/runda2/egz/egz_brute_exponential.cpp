// Rozwiązanie brutalne do zadania 'Egzamin [2A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n * n^2).
// Złożoność pamięciowa: O(n)
// Punkty: ???

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;
using ld = long double;
constexpr int MAXN = 50'005;
ld p[MAXN];
int main() {
    ios_base::sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    sort(p, p + n, [](ld a, ld b) { return a > b; });

    ld wynik = 0;

    for (int i = 1; i <= n; i++) {
        ld kandydat = 0;
        int full = (1 << i) - 1;
        for (int A = 0; A <= full; A++) {
            int sz_A = __builtin_popcount(A);
            int sz_B = i - sz_A;
            if (sz_A - sz_B >= t) {
                ld p_exact = 1;
                for (int j = 0; j < i; j++) {
                    if (A >> j & 1)
                        p_exact *= p[j];
                    else
                        p_exact *= (1.0 - p[j]);
                }
                kandydat += p_exact;
            }
        }

        wynik = max(wynik, kandydat);
    }

    cout << fixed << setprecision(9) << wynik << "\n";
}