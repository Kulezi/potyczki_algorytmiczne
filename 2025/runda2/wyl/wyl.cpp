// Rozwiązanie do zadania 'Wyliczanka [2B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;
constexpr int MAXN = 1'000'005, INF = 2'000'000'000;

bool solve() {
    int n;

    cin >> n;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> l_pref(n + 2, 0), r_pref(n + 2, 0), l_suf(n + 2, 0), r_suf(n + 2, 0),
        good_pref(n + 2, 1), good_suf(n + 2, 1);
    int L = 1, R = n;
    while (a[L] == 0) ++L;
    while (a[R] == 0) --R;

    for (int i = L; i <= R + 1; i++) {
        l_pref[i] = r_pref[i - 1];  // - (i > s);
        r_pref[i] = a[i] - l_pref[i];
        good_pref[i] = good_pref[i - 1] && r_pref[i] >= 1;
    }

    // Bez straty ogólności początek jest po lewej więc mogę mieć wyjebane w te parzystości tutaj.
    for (int i = R; i >= L - 1; i--) {
        r_suf[i] = l_suf[i + 1];
        l_suf[i] = a[i] - r_suf[i];

        good_suf[i] = good_suf[i + 1] && l_suf[i] >= 1;
    }

    int first_incremented = 0;

    // Jakby koniec był w tym miejscu.
    for (int i = L; i <= R; i++) {
        if (good_suf[i + 1]) {
            // Początek tam gdzie koniec.
            if (!first_incremented && r_pref[i - 1] + l_suf[i + 1] == a[i] - 1) return true;

            // Początek jest o parzystą liczbę miejsc w lewo.
            if (i - 2 >= L &&
                (!first_incremented || (first_incremented && first_incremented % 2 != i % 2)))
                if (r_pref[i - 1] + 1 + l_suf[i + 1] == a[i]) return true;

            // Początek jest o nieparzystą liczbę miejsc w lewo.
            if (i - 1 >= L &&
                (!first_incremented || (first_incremented && first_incremented % 2 == i % 2)))
                if (r_pref[i - 1] + l_suf[i + 1] == a[i]) return true;
        }

        if (!first_incremented) {
            if (r_pref[i] < 0)
                return false;  // Nie wybronimy się z tego nawet ustawiając początek.
            else if (r_pref[i] == 0)
                first_incremented = i;  // O 1, 3, ..., pola od nas musi stać początek, żeby nas
                                        // wyratować z zera na jeden.
        } else {
            if (r_pref[i] < 0)
                return false;
            else if (r_pref[i] == 0 && (first_incremented % 2 != i % 2))
                return false;  // Kaszana, teraz początek musi być na dwóch różnych parzystościach
                               // naraz.
        }
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--) {
        if (solve())
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}