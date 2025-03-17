// Rozwiązanie do zadania 'Finaliści [1C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <iostream>
#include <string>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    int finalisci = 0;
    for (int i = 1; i <= n; ++i) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "NIE") continue;
        if (finalisci < 10 || (finalisci < 20 && x < 2)) {
            ++finalisci;
            cout << i << " ";
        }
    }

    cout << "\n";
}