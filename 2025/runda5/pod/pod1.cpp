// Rozwiązanie brutalne do zadania 'Podciągi [5B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n * log(n) * q)
// Złożoność pamięciowa: O(2^n)
// Punkty: 1

#include <bits/stdc++.h>
using namespace std;

int n, q;
string s;

void policz() {
    map<string, int> counter;

    int res = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string t;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) t += s[i];
        }

        counter[t]++;
        if(counter[t] == 2) res++; 
    }

    cout << res << "\n";
}

int32_t main() {
    cin >> n >> q;

    cin >> s;

    policz();

    while (q--) {
        int pos;
        char c;
        cin >> pos >> c;

        s[pos-1] = c;
        policz();
    }
}