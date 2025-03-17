// Generatorka testów do zadania 'Zbieranie klocków [4B]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 200000, MAXM = 200000, MAXQ = 75000;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    int n = R(MAXN, MAXN);
    int m = R(MAXM, MAXM);
    int k = R(MAXQ, MAXQ);
    int q = MAXQ;

    cout << n << " " << m << " " << k << " " << q << "\n";
    set<pair<int,int>> wziete;
    while (k--) {
        int x = R(1, n);
        int y = R(1, m);
        while (wziete.count({x, y})) {
            x = R(1, n);
            y = R(1, m);
        }
        wziete.insert({x, y});
        cout << x << " " << y << "\n";
    }

    // Losuje po 10 bliskich sobie punktów, żeby było ciekawiej.
    for (int i = 1; i <= q / 100; i++) {
        int x = R(1, n);
        int y = R(1, m);

        for (int rep = 1; rep <= 10; rep++) {
            int nx = R(x-4, x+4), ny = R(y-4, y+4);
            nx = clamp(nx, 1, n);
            ny = clamp(ny, 1, m);
            cout << nx << " " << ny << "\n";
        }

        // cout << R(1, n) << " " << R(1, m) << "\n";
        
    }

}