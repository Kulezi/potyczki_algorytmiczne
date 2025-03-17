// Rozwiązanie do zadania 'Praca [1B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 8005;
enum {
    BIURO = 0,
    ZDALNE = 1,
    WOLNE = 2,
};

int pref[MAXN][3];
int n, k, t;

int cnt(int l, int r, int typ) {
    if (r < l) return 0;
    return pref[r][typ] - pref[l - 1][typ];
}
int spalone_dojazd(int l) { return cnt(l, l + t - 1, BIURO) + cnt(l, l + t - 1, ZDALNE); }

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> t;

    string s;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            pref[i][j] = pref[i - 1][j];
        }

        pref[i][s[i - 1] - '1']++;
    }

    int wynik = -1;

    // Case 1: Pojedzie.
    for (int l = 1; l <= n; l++) {
        for (int r = l + t; r + t - 1 <= n; r++) {
            int spalone_dom = cnt(1, l - 1, BIURO) + cnt(r + t, n, BIURO);
            int spalone = spalone_dojazd(l) + spalone_dojazd(r) + spalone_dom;

            int za_friko = cnt(1, l - 1, WOLNE) + cnt(r + t, n, WOLNE);
            int zdalne_w_domu = cnt(1, l - 1, ZDALNE) + cnt(r + t, n, ZDALNE);
            if (spalone <= k) {
                wynik = max(wynik, za_friko + spalone_dom + min(k - spalone, zdalne_w_domu));
            }
        }
    }

    // Case 2: Nie pojedzie.
    int spalone = cnt(1, n, BIURO);
    if (spalone <= k) {
        wynik = max(wynik, spalone + cnt(1, n, WOLNE) + min(cnt(1, n, ZDALNE), k - spalone));
    }

    cout << wynik << "\n";
}