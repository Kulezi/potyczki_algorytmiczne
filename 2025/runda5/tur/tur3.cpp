// Rozwiązanie wolne i zbugowane do zadania 'Turniej trójek [5C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2 * max(a_i)^(1/3) * log(n))
// Złożoność pamięciowa: O(n^2)
// Punkty: 3

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 200'005;

int dp[2005][2005];

ll ile(int l, int x, int r) {
    return 1LL * l * x * r + 1LL * (x * (x - 1) / 2) * (l + r) + 1LL * x * (x - 1) * (x - 2) / 6;
}

bool check(vector<int> &a, int total) {
    int n = a.size();
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= total; l++) {
            dp[i][l] = 0;
            for (int x = 0; x <= l; x++) {
                if (!dp[i - 1][l - x]) continue;
                // Long long mistake.
                int mozna = ile(l - x + (i - 1), x + 1, total - l + (n - i));
                if (a[i - 1] <= mozna) {  // spełnione dla dowolnego x >= 183.
                    dp[i][l] = 1;
                    break;
                }
            }
        }
    }

    return dp[n][total];
}

int solve(int n) {
    vector<int> a;
    for (int i = 1; i <= n; i++) {
        int x = 1'000'000;
        cin >> x;
        if (x != 0) a.push_back(x);
    }

    n = a.size();

    int lo = 2, hi = 2000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (!check(a, mid))
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo + n;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int tests = 100;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        int n = tc * 10;
        cin >> n;
        cout << solve(n) << "\n";
    }
}