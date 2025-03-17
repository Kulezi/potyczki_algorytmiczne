// Rozwiązanie brutalne do zadania 'Mnożenie cyfr [3B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(1)
// Punkty: ???


#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;
using ll = long long;

int cyfra(ll n) {
    while (n >= 10) {
        ll nowe_n = 1;
        while (n > 0) nowe_n *= n % 10, n /= 10;
        n = nowe_n;
    }

    return n;
}

void paluj(ll n) {
    vector<ll> wynik(10, 0);
    for (ll i = 1; i <= n; i++) {
        wynik[cyfra(i)]++;
    }

    for (int i = 0; i < 10; i++) cout << wynik[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);

    int q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        paluj(n);
    }
}