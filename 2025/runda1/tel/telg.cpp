// Generatorka testów do zadania 'Teleport [1A]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int q = 100;
    cout << q << "\n";

    for (int tc = 1; tc <= q; tc++) {
        int n = R(3, 100);
        cout << n << "\n";

        vector g(n, string(n, '0'));
        auto add_edge = [&](int a, int b) {
            g[a][b] = '1';
            g[b][a] = '1';
        };

        // Jakieś drzewko, żeby spójne było.
        for (int i = 1; i < n; i++) {
            add_edge(R(max(0, i - 2), i - 1), i);
        }

        // + jakieś losowe krawędzie, wywalone w duplikaty.
        int m = (n * (n - 1) / 2) / R(1, 100);
        while (m--) {
            int a = R(0, n - 2);
            int b = R(a + 1, n - 1);
            add_edge(a, b);
        }

        for (int i = 0; i < n; i++) cout << g[i] << "\n";
    }
}