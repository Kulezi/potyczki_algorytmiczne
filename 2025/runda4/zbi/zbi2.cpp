// Rozwiązanie brutalne do zadania 'Zbieranie klocków [4B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * (n*m + wynik) * log(n*m))
// Złożoność pamięciowa: O(n*m)
// Punkty: 2

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;

constexpr int MAXN = 1'000'005, INF = 2'000'000'000;

int n, m, k, q;
set<pair<int, int>> plansza, t;

bool jest(int x, int y) { return t.count({x, y}); }

bool pion(int x, int y) { return jest(x, y) && !jest(x, y - 1) && !jest(x, y + 1); }

bool poziom(int x, int y) { return jest(x, y) && !jest(x - 1, y) && !jest(x + 1, y); }

vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
set<pair<int, int>> vis;
queue<pair<int, int>> Q;

void sprawdz(int x, int y) {
    if (!vis.count({x, y}) && (poziom(x, y) || pion(x, y))) {
        Q.push({x, y});
        vis.insert({x, y});
    }
}

int ile() {
    t = plansza;
    vis = {};

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            sprawdz(x, y);
        }
    }

    int res = 0;
    while (!Q.empty()) {
        res++;
        auto [x, y] = Q.front();
        Q.pop();
        t.erase({x, y});

        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            sprawdz(nx, ny);
        }
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m >> k >> q;

    while (k--) {
        int x, y;
        cin >> x >> y;
        plansza.insert({x, y});
    }

    cout << ile() << "\n";
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (!plansza.count({x, y}))
            plansza.insert({x, y});
        else
            plansza.erase({x, y});

        cout << ile() << "\n";
    }
}