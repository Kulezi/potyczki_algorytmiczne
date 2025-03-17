// Rozwiązanie brutalne do zadania 'Praca [1B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3)
// Złożoność pamięciowa: O(n)
// Punkty: ???

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 8005;
enum {
    BIURO = 1,
    ZDALNE = 2,
    WOLNE = 3,
};

int pref[MAXN][5];
int n, k, t;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> t;

    string s;
    cin >> s;

    int wynik = -1;

    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            if (r - l + 1 <= 2 * t) continue;

            int spalone_w_drodze = 0;
            for (int k = l; k < l + t; k++)
                if (s[k] == '1' || s[k] == '2') spalone_w_drodze++;

            for (int k = r - t + 1; k <= r; k++)
                if (s[k] == '1' || s[k] == '2') spalone_w_drodze++;

            vector<int> cnt(300, 0);
            for (int k = 0; k < l; k++) cnt[s[k]]++;

            for (int k = r + 1; k < n; k++) cnt[s[k]]++;

            int spalone = spalone_w_drodze + cnt['1'];

            if (spalone <= k) wynik = max(wynik, cnt['3'] + cnt['1'] + min(cnt['2'], k - spalone));
        }
    }

    vector<int> cnt(300, 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    if (cnt['1'] <= k) wynik = max(wynik, cnt['3'] + cnt['1'] + min(k - cnt['1'], cnt['2']));

    cout << wynik << "\n";
}