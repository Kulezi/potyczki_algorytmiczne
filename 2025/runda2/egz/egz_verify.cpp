// Weryfikatorka outów do zadania 'Egzamin [2A]' z Potyczek Algorytmicznych 2025.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld ldabs(ld x) {
    if (x < 0) return -x;
    return x;
}

int32_t main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "usage: ./verify sol.out model.out\n";
        return 1;
    }

    ifstream sol(argv[1]);
    ifstream model(argv[2]);

    long double sol_ans, model_ans;
    sol >> sol_ans;
    model >> model_ans;

    if (ldabs(sol_ans - model_ans) > 1e-6) return 1;
    return 0;
}