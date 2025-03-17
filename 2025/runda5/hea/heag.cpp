// Generatorka testów do zadania 'Heavy metal [5B]' z Potyczek Algorytmicznych 2025.

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXW = 1'000'000'000, MAXW_SQRT = 31622;
bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;

    return true;
}

vector<int> primes;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    int q = 1;
    cout << q << endl;
   
    for (int tc = 1; tc <= q; tc++) {
        int n = 100;
        int m = 200;
    
        cout << n << " " << m << endl;

        for (int i = 1; i <= n; i++) {
            cout << R(1, MAXW)   << " ";
        }

        cout << "\n";
        auto add_edge = [&](int a, int b, int w) {
            cout << a << " " << b << " " << w << endl;
            assert(m >= 0);
        };


        // // Cykl z jedynkami na krawedziach.
        // for (int i = 1; i < n; i++) {
        //     add_edge(i, i + 1, 1);
        // }

        // add_edge(n, 1, 1);

        for (int i = 0; i < m; i++) {
            add_edge(R(1, n), R(1, n), R(1, MAXW));
        }

    }
}