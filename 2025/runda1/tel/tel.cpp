// Rozwiązanie do zadania 'Teleport [1A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^4 / c) gdzie c to ~ 1/47 worstcase.
// Złożoność pamięciowa: O(n^2)
// Punkty: 10

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 405, INF = 1'000'000;
string g[MAXN];
int d[MAXN][MAXN], dab[MAXN];
vector<pair<int, int>> pary[MAXN];
int n, max_diameter;
int diameter(int a, int b) {
    for (int i = 0; i < n; i++) dab[i] = min(d[a][i], d[b][i]);

    int max_dab = 1;
    for (int dis = max_diameter; dis > max_dab; --dis) {
        for (auto [i, j] : pary[dis]) {
            if (dab[i] + dab[j] >= dis) return dis;
            max_dab = max(max_dab, dab[i] + dab[j]);
        }
    }

    return max_dab;
}

void solve() {
    cin >> n;
    max_diameter = 0;

    for (int i = 0; i < n; i++) {
        pary[i] = {};
        cin >> g[i];
        for (int j = 0; j < n; j++) {
            d[i][j] = g[i][j] - '0';
            if (i != j && g[i][j] == '0') d[i][j] = INF;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pary[d[i][j]].emplace_back(i, j);
            max_diameter = max(max_diameter, d[i][j]);
        }
    }

    int wynik = INF;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            wynik = min(wynik, diameter(a, b));
        }
    }

    cout << wynik << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int q = 1;
    cin >> q;
    while (q--) solve();
}