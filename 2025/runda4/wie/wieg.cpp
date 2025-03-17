// Generatorka testów do zadania 'Wieża [4C]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int R(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = R(1, 1000);
    int c = R(1, 10000);

    cout << n << " " << c << "\n";

    vector<int> v(30 * n);
    iota(v.begin(), v.end(), 1);

    shuffle(v.begin(), v.end(), rng);
    sort(v.begin(), v.begin() + n);
    for (int i = 0; i < n; i++) {
        cout << v[i] << " " << R(1, 10) << "\n";
    }
}