// Rozwiązanie do zadania 'Wieża [4C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 500'005;
constexpr ll INF = 1e18;

int a[MAXN], w[MAXN];

ll dp[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, c;
    cin >> n >> c;

    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> w[i];
        dp[w[i]] = -INF;
    }

    set<pair<ll, int>> maksy;
    vector<pair<ll, int>> to_insert;

    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            while (!to_insert.empty()) {
                auto [A, W_A] = to_insert.back();
                to_insert.pop_back();
                dp[W_A] = A;
                maksy.insert({-A, W_A});
            }
        }
        ll nowe = max((ll)a[i], dp[w[i]] + a[i]);
        int two = 2;
        for (auto [A, W_A] : maksy) {
            nowe = max(nowe, -A + a[i] - c);
            two--;
            if (!two) break;
        }

        to_insert.emplace_back(nowe, w[i]);
    }

    while (!to_insert.empty()) {
        auto [A, W_A] = to_insert.back();
        to_insert.pop_back();
        dp[W_A] = A;
        maksy.insert({-A, W_A});
    }

    cout << -maksy.begin()->first << endl;
}