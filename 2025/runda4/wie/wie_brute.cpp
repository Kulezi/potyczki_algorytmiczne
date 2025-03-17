// Rozwiązanie brutalne do zadania 'Wieża [4C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
// Punkty: ???

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;

constexpr int MAXN = 500005;

int a[MAXN], w[MAXN];

ll dp[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, c;
    cin >> n >> c;

    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> w[i];
    }

    ll wynik = 0;
    dp[0] = c;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; a[j] < a[i]; j++) {
            dp[i] = max(dp[i], dp[j] + a[i] - (w[i] != w[j]) * c);
        }

        wynik = max(dp[i], wynik);
    }

    cout << wynik << "\n";
}