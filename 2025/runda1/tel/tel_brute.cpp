// Rozwiązanie brutalne do zadania 'Teleport [1A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^4)
// Złożoność pamięciowa: O(n^2)
// Punkty: ???

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 405, INF = 1'000'000;
string g[MAXN];
int d[MAXN][MAXN];

int shortcut(int a, int b, int i, int j) { return d[i][a] + d[b][j] < d[i][j]; }

int n, mx;
int diameter(int a, int b) {
    int res = 0;

    for (int i = 0; i < n; i++) {
        int A = d[i][a];
        int B = d[i][b];

        for (int j = 0; j < n; j++) {
            int d_ij = min({A + d[b][j], B + d[a][j], d[i][j]});
            res = max(res, d_ij);
        }
    }

    return res;
}

void solve() {
    cin >> n;

    for (int i = 0; i < n; i++) {
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

    int wynik = INF;
    for (int a = 0; a < n; a++) {
        for (int b = a; b < n; b++) {
            wynik = min(wynik, diameter(a, b));
        }
    }

    cout << wynik << "\n";
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) solve();
}