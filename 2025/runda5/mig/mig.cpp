// Rozwiązanie do zadania 'Migawka [5C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 10
// Ilość operacji: (n-1)*(n-1)+1, 9802 dla n = 100.


#include <bits/stdc++.h>
using namespace std;
constexpr int N = 100;
int t[N + 1][N + 1];
int32_t main() {
    ios_base::sync_with_stdio(0);

    t[2][1] = 1;
    for (int i = 2; i <= N; i++) {
        t[1][i] = 1;
    }

    for (int j = 4; j <= N; j += 2) {
        t[j][1] = 1;
        for (int i = 1; i <= N - 1; i++) {
            t[j - 1][i] = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << t[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}