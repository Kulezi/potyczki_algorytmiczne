// Rozwiązanie do zadania 'Żelki [3B]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n+k)*m)
// Złożoność pamięciowa: O(((n+k)*m)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAXN = 7005;
constexpr ll INF = 1e18;

int n, colors, mod;
struct Item {
    int k, c, m;
};

vector<Item> items[MAXN];

int32_t main() {
    boost;
    cin >> n >> colors >> mod;
    vector jeden(colors + 1, vector<ll>(mod, INF));
    vector wszystkie(colors + 1, vector<ll>(mod, INF));
    vector ans(mod, INF);
    for (int i = 1; i <= n; i++) {
        int k, c, m;
        cin >> k >> m >> c;
        if (m == mod) m = 0;
        items[k].push_back({k, c, m});
        jeden[k][m] = min(jeden[k][m], 1LL * c);
    }

    for (int r = 0; r < mod; r++) wszystkie[1][r] = jeden[1][r];
    for (int color = 2; color <= colors; color++) {
        for (int r0 = 0; r0 < mod; r0++) {
            for (auto i : items[color]) {
                int r = (r0 + i.m) % mod;
                wszystkie[color][r] = min(wszystkie[color][r], wszystkie[color - 1][r0] + i.c);
            }
        }
    }

    vector<ll> zestaw(mod, INF);
    for (int r = 0; r < mod; r++) zestaw[r] = wszystkie[colors][r];
    zestaw[0] = 0;
    vector<int> used(mod, 0);

    for (int rep = 0; rep < mod; rep++) {
        int r = -1;
        for (int i = 0; i < mod; i++) {
            if (!used[i] && (r == -1 || zestaw[r] > zestaw[i])) r = i;
        }
        used[r] = 1;

        ll d = zestaw[r];
        for (int r2 = 0; r2 < mod; r2++) {
            if (d + zestaw[r2] < zestaw[r]) {
                zestaw[r] = d + zestaw[r2];
            }
            r++;
            if (r >= mod) r -= mod;
        }
    }

    for (int r = 0; r < mod; r++) {
        if (zestaw[r] >= INF) zestaw[r] = -1;
        cout << zestaw[r] << "\n";
    }
}