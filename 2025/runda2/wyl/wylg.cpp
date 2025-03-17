// Generatorka testów do zadania 'Wyliczanka [2B]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

void gen_case() {
    int n = R(2, 1000000);
    cout << n << endl;

    int ok = R(0, 1);
    int moves = R(1, 10000000);

    int pos = R(1, n);
    vector<int> a(n + 1, 0);

    a[pos]++;
    while (moves--) {
        if (pos == 1)
            pos++;
        else if (pos == n)
            pos--;
        else if (R(0, 10))
            pos++;
        else
            pos--;
        a[pos]++;
    }

    if (!ok) {
        int losu = R(1, 10);
        while (losu--) a[R(1, n)] += R(-1, 1);
    }

    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int q = R(1, 10);
    cout << q << endl;
    while (q--) gen_case();
}