// Rozwiązanie wolne do zadania 'Wyliczanka [2B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 5

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;

constexpr int MAXN = 1'000'005;

bool solve() {
    int n;

    cin >> n;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto check = [&](int s) {
        vector<int> l_pref(n + 2, 0), r_pref(n + 2, 0), l_suf(n + 2, 0), r_suf(n + 2, 0),
            good_pref(n + 2, 1), good_suf(n + 2, 1);

        int L = 1, R = n;
        while (a[L] == 0) ++L;
        while (a[R] == 0) --R;

        for (int i = L; i <= R + 1; i++) {
            l_pref[i] = r_pref[i - 1] - (i > s);
            r_pref[i] = a[i] - l_pref[i];
            good_pref[i] = good_pref[i - 1] && r_pref[i] >= 1;
        }

        // Bez straty ogólności początek jest po lewej więc mogę mieć wyjebane w te parzystości
        // tutaj.
        for (int i = R; i >= L - 1; i--) {
            r_suf[i] = l_suf[i + 1] - (i < s);
            l_suf[i] = a[i] - r_suf[i];

            good_suf[i] = good_suf[i + 1] && l_suf[i] >= 1;
        }

        // Jakby koniec był w tym miejscu.
        for (int i = L; i <= R; i++) {
            if (good_pref[i - 1] && good_suf[i + 1] &&
                (r_pref[i - 1] + l_suf[i + 1] == a[i] - (i == s)))
                return true;
        }

        return false;
    };

    for (int i = 1; i <= n; i++)
        if (check(i)) return true;

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int q;
    cin >> q;
    while (q--) {
        if (solve())
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}