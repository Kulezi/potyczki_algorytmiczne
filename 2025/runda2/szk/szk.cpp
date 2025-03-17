// Rozwiązanie do zadania 'Szkoła [2C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = 1e18;
int32_t main() {
    ios_base::sync_with_stdio(0);
    ll n, s;
    int m;

    cin >> n >> m >> s;

    vector<pair<ll, ll>> przedzialy(m);
    for (auto &[l, r] : przedzialy) cin >> l >> r;

    sort(przedzialy.begin(), przedzialy.end());

    vector<pair<ll, ll>> zlepione;
    for (auto [l, r] : przedzialy) {
        if (zlepione.empty() || zlepione.back().second != l - 1)
            zlepione.emplace_back(l, r);
        else
            zlepione.back().second = r;
    }

    ll wynik_numer;
    ll wynik_odleglosc = INF;
    auto popraw = [&](ll x) {
        ll d = llabs(s - x);
        if (x >= 1 && x <= n &&
            (wynik_odleglosc > d || (wynik_odleglosc == d && x < wynik_numer))) {
            wynik_numer = x;
            wynik_odleglosc = llabs(s - x);
        }
    };

    for (auto [l, r] : zlepione) {
        if (l <= s && s <= r) {
            popraw(l - 1);
            popraw(r + 1);
        }
    }

    cout << wynik_numer << "\n";
}