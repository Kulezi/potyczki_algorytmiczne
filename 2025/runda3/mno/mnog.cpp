// Generatorka testów do zadania 'Mnożenie cyfr [3B]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int q = R(1, 10);
    cout << q << endl;
    while (q--) {
        cout << R(1, 9);
        int L = R(1, 15);
        while (L--) {
            cout << R(1, 9);
        }
        cout << "\n";
    }
}