// Generatorka testów do zadania 'Muzyka pop [1A]' z Potyczek Algorytmicznych 2019.
// Autor: Paweł Putra

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
ll R(ll a, ll b) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(a, b)(rng);
}

int32_t main() {
    int n = 200;
    ll m = R(1, 1e18);
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; i++) {
        cout << R(-1e14, 1e14) << " ";
    }
    cout << "\n";
}