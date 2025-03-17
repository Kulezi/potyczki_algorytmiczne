// Rozwiązanie prawie-optymalne do zadania 'Migawka [5C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 9
// Ilość operacji: (n-2)*(n-1), 9704 dla n = 100.

#include <bits/stdc++.h>
using namespace std;

int t[105][105];
int32_t main() {
    ios_base::sync_with_stdio(0);

    t[2][1] = 1;
    for (int i = 2; i <= 100; i++) {
        t[1][i] = 1;
    }

    for (int j = 4; j <= 100; j += 2) {
        t[j][1] = 1;
        t[j - 1][100] = 1;
    }

    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            cout << t[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}