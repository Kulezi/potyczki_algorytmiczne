// Rozwiązanie wolne do zadania 'Terytoria [2B]' z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*log(n) + XY)
// Złożoność pamięciowa: O(XY)
// Punkty: 2
#include <bits/stdc++.h>
#define MX 500005
using namespace std;
int n, X, Y, x[MX][2], y[MX][2], N = -1, res;
int dp[5005][5005];
map<int, int> M, id, cnt, los;
void dodaj(int left, int up, int right, int down, int val) {
    if (!los[abs(val)]) los[abs(val)] = rand() % 1158294941;
    if (val < 0)
        val = -los[abs(val)];
    else
        val = los[abs(val)];

    dp[left][up] += val;
    dp[right + 1][up] -= val;
    dp[left][down + 1] -= val;
    dp[right + 1][down + 1] += val;
}
int main() {
    cin >> n >> X >> Y;
    M[0] = M[X] = M[Y] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> x[i][0] >> y[i][0] >> x[i][1] >> y[i][1];
        for (int k = 0; k < 2; k++) {
            for (int j = -1; j <= 1; j++)
                if (x[i][k] + j <= X && x[i][k] + j >= 0) M[x[i][k] + j] = 1;
            for (int j = -1; j <= 1; j++)
                if (y[i][k] + j <= Y && y[i][k] + j >= 0) M[y[i][k] + j] = 1;
        }
    }

    for (auto &i : M) {
        i.second = ++N;
        id[N] = i.first;
    }

    X = M[X];
    Y = M[Y];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) x[i][j] = M[x[i][j]], y[i][j] = M[y[i][j]];
        if (x[i][0] > x[i][1]) swap(x[i][0], x[i][1]);
        if (y[i][0] > y[i][1]) swap(y[i][0], y[i][1]);
        // zwykly prostokat
        dodaj(x[i][0] + 1, y[i][0] + 1, x[i][1], y[i][1], 4 * i + 0);
        // pasek poziomy - prostokat
        dodaj(1, y[i][0] + 1, X, y[i][1], 4 * i + 1);
        dodaj(x[i][0] + 1, y[i][0] + 1, x[i][1], y[i][1], -(4 * i + 1));
        // pasek pionowy - prostokat
        dodaj(x[i][0] + 1, 1, x[i][1], Y, 4 * i + 2);
        dodaj(x[i][0] + 1, y[i][0] + 1, x[i][1], y[i][1], -(4 * i + 2));
        //  cale - pion - poziom + prostokat
        dodaj(1, 1, X, Y, 4 * i + 3);
        dodaj(1, y[i][0] + 1, X, y[i][1], -(4 * i + 3));
        dodaj(x[i][0] + 1, 1, x[i][1], Y, -(4 * i + 3));
        dodaj(x[i][0] + 1, y[i][0] + 1, x[i][1], y[i][1], 4 * i + 3);
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            dp[i][j] += dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
            cnt[dp[i][j]] += (id[i] - id[i - 1]) * (id[j] - id[j - 1]);
            res = max(res, cnt[dp[i][j]]);
        }
    }

    cout << res << "\n";
}