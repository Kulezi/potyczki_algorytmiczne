// Rozwiązanie do zadania 'Znaczki pocztowe [2C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;
const int MAX_N = 300'005;
int ans[MAX_N];
int32_t main() {
    boost;

    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (auto [_, c] : cnt) {
        for (int i = 1; i <= c; i++) {
            ans[i] += (c / i) * i;
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}