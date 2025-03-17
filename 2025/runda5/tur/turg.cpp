// Generatorka testów do zadania 'Turniej trójek [5C]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    int tests = R(1, 1);
    cout << tests << endl;
    while (tests--) {
        int n = R(1, 3000);
        cout << n << endl;

        for (int i = 1; i <= n; i++) {
            cout << R(1, 1000000) << " ";
        }

        cout << endl;
    }
}