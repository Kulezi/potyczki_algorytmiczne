// Rozwiązanie brutalne do zadania 'Liście [5A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((m + z) * q)
// Złożoność pamięciowa: O(n)
// Punkty: 2

#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_NMZ = 1'000'005;
int n, m, z;

int a[MAX_NMZ];
long long v[MAX_NMZ];

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m >> z;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m + z; i++) {
        int typ, p, w;
        cin >> typ >> p >> w;
        if (typ == 1) {
            for (int i = 1; i <= p; i++) {
                v[i] += w;
            }
        } else {
            assert(typ == 2);
            long long wynik = 0;
            for (int i = 1; i <= p; i++) {
                if (a[i] >= w) wynik += v[i];
            }

            cout << wynik << "\n";
        }
    }
}