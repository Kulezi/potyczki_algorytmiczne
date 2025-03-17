// Rozwiązanie wolne do zadania 'Turniej trójek [5C]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * max(a_i) * log(n))
// Złożoność pamięciowa: O(n^2)
// Punkty: 5

#include <bits/stdc++.h>
#define int long long
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 200'005;

int dp[2005][2005];

ll ile(int l, int x, int r) {
    return 1LL * l * x * r + 1LL * (x * (x - 1) / 2) * (l + r) + 1LL * x * (x - 1) * (x - 2) / 6;
}

vector<int> wywal_srodek(vector<int> &a) {
    int n = a.size();
    vector<int> res;
    for (int i = 0; i < 1000; i++) res.push_back(a[i]);
    for (int i = n - 1000; i < n; i++) res.push_back(a[i]);
    return res;
}

int frajerstwo = 0;

bool check(vector<int> &a, int total) {
    int n = a.size();
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= total; l++) {
            dp[i][l] = 0;
            for (int x = 0; x <= l; x++) {
                if (!dp[i - 1][l - x]) continue;

                int L = l - x + (i - 1) + (i > 1000 ? frajerstwo : 0);
                int R = total - l + (n - i) + (i <= 1000 ? frajerstwo : 0);
                int mozna = ile(L, x + 1, R);
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

    frajerstwo = 0;
    if (n > 2000) {
        a = wywal_srodek(a);
        frajerstwo = n - 2000;
        n = 2000;
    }

    int lo = 2, hi = 2000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (!check(a, mid))
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo + n + frajerstwo;
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