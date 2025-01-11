// Rozwiązanie błędne do zadania próbnego 'A + B' z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(log(n))
// Złożoność pamięciowa: O(log(n))
// Punkty: 2

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll single_ways(int x) {
    int res = 0;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            if (i + j == x) res++;
        }
    }

    return res;
}

string s;
ll dp[50];
int mam[50];

ll ways(int l) {
    if (mam[l]) return dp[l];
    mam[l] = 1;
    if (l >= s.size()) return dp[l] = 1;
    // bez carry
    ll res = single_ways(s[l] - '0') * ways(l + 1);
    // z carry
    if (l + 1 < s.size()) res += single_ways((s[l] - '0') * 10 + s[l + 1] - '0') * ways(l + 2);

    return dp[l] = res;
}

int32_t main() {
    cin >> s;
    cout << ways(0) << "\n";
}