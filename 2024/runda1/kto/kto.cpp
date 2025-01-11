// Rozwiązanie do zadania 'Kto wygrał? [1C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(1)
// Złożoność pamięciowa: O(1)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

const int SUM_POINTS = 11, ALGOSIA = 0, BAJTEK = 1;
int cnt[2][20];

int32_t main() {
    boost;

    for (int person = 0; person < 2; person++) {
        for (int task = 0; task < 18; task++) {
            int points;
            cin >> points;
            cnt[person][points]++;
            cnt[person][SUM_POINTS] += points;
        }
    }

    for (int i = SUM_POINTS; i >= 0; i--) {
        if (cnt[ALGOSIA][i] > cnt[BAJTEK][i]) {
            cout << "Algosia\n";
            return 0;
        }

        if (cnt[ALGOSIA][i] < cnt[BAJTEK][i]) {
            cout << "Bajtek\n";
            return 0;
        }
    }

    cout << "remis\n";
}