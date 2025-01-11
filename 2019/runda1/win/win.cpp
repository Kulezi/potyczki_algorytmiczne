// Rozwiązanie do zadania 'Wina [1B]' z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 10 

#include <bits/stdc++.h>
using namespace std;
int n, k, x, dp[2005][2005], res = 2137;
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 2; i <= n + 1; i++)
        for (int j = 2; j <= i; j++) {
            cin >> x;
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + 1 - dp[i - 2][j - 1];
            if (dp[i][j] <= k) res = min(res, x);
        }
    cout << res;
}