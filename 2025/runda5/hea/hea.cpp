// Rozwiązanie do zadania 'Heavy metal [5B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(sqrt(p_n) * n * (n+m))
// Złożoność pamięciowa: O(sqrt(p_n) * n)
// Punkty: 10

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAX = 1'000'000'000, THRESHOLD = 31635, MAXN = 105, MAXM = 205;  // ~~sqrt(MAX)

vector<pair<int, int>> light[MAXN], light_rev[MAXN];
vector<int> ones[MAXN], ones_rev[MAXN];
vector<tuple<int, int, int>> heavy;
int p[MAXN];

bool dp_1[THRESHOLD + 1][MAXN];
int dp_n[THRESHOLD + 1][MAXN];

int mx[MAXN][(THRESHOLD + 1) * 4];

int n, m;
void plant_trees(int pos, int l, int r) {
    if (l == r) {
        for (int i = 1; i <= n; i++) {
            mx[i][pos] = dp_n[l][i];
        }
        return;
    }

    int m = (l + r) / 2;
    plant_trees(pos * 2, l, m);
    plant_trees(pos * 2 + 1, m + 1, r);
    for (int i = 1; i <= n; i++) {
        mx[i][pos] = max(mx[i][pos * 2], mx[i][pos * 2 + 1]);
    }
}

// Znajduje najwyższy indeks w drzewie, taki, że jego wartość jest >= x.
int query_tree(int tree, int x) {
    if (mx[tree][1] < x) return 0;
    int pos = 1, l = 1, r = THRESHOLD;
    while (l < r) {
        int m = (l + r) / 2;
        if (mx[tree][pos * 2 + 1] >= x) {
            l = m + 1;
            pos = pos * 2 + 1;
        } else {
            r = m;
            pos = pos * 2;
        }
    }

    return l;
}

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

bool mozliwe[THRESHOLD + 1];
vector<int> primes;
int solve() {
    cin >> n >> m;
    heavy.clear();

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        ones[i].clear();
        ones_rev[i].clear();
        light[i].clear();
        light_rev[i].clear();

        for (int j = 0; j <= THRESHOLD; j++) {
            dp_1[j][i] = 0;
            dp_n[j][i] = 0;
        }
    }

    set<int> rozne_wagi;
    mozliwe[1] = 1;
    for (int i = 2; i <= THRESHOLD; i++) mozliwe[i] = false;

    for (int i = 1; i <= m; i++) {
        int a, b, w;
        cin >> a >> b >> w;

        if (w <= THRESHOLD) {
            if (w > 1) {
                light[a].push_back({b, w});
                light_rev[b].push_back({a, w});
            } else {
                ones[a].push_back(b);
                ones_rev[b].push_back(a);
            }
            heavy.push_back({a, b, w});
            rozne_wagi.insert(w);
        } else {
            heavy.push_back({a, b, w});
        }
    }

    for (int i = 1; i <= THRESHOLD; i++) {
        if (mozliwe[i]) {
            for (auto w : rozne_wagi) {
                if (i * w <= THRESHOLD) mozliwe[i * w] = 1;
            }
        }
    }

    // Wylicz dp_1 w O(sqrt(MAX) * n * (n+m)).
    dp_1[1][1] = 1;
    for (int p_src = 1; p_src < THRESHOLD; p_src++) {
        if (mozliwe[p_src]) {
            for (int rep = 1; rep <= n; rep++) {  // Trzeba przepchać jedynki...
                for (int src = 1; src <= n; src++) {
                    if (dp_1[p_src][src]) {
                        for (auto dst : ones[src]) {
                            if (p_src <= p[dst]) {
                                dp_1[p_src][dst] = 1;
                            }
                        }
                    }
                }
            }

            for (int src = 1; src <= n; src++) {
                if (dp_1[p_src][src]) {
                    for (auto [dst, w] : light[src]) {
                        int p_dst = p_src * w;
                        if (p_dst <= THRESHOLD && p_dst <= p[dst]) {
                            dp_1[p_dst][dst] = 1;
                        }
                    }
                }
            }
        }
    }

    // Wylicz dp_n w O(sqrt(MAX) * n * (n+m)).
    dp_n[1][n] = p[n];
    for (int p_dst = 1; p_dst <= min(THRESHOLD, p[n]); p_dst++) {
        if (mozliwe[p_dst]) {
            for (int rep = 1; rep <= n; rep++) {  // Trzeba przepchać jedynki...
                for (int dst = 1; dst <= n; dst++) {
                    for (auto src : ones_rev[dst]) {
                        dp_n[p_dst][src] = max(dp_n[p_dst][src], min(dp_n[p_dst][dst], p[src]));
                    }
                }
            }
        }

        for (int dst = 1; dst <= n; dst++) {
            for (auto [src, w] : light_rev[dst]) {
                int p_src = p_dst * w;
                if (p_src <= THRESHOLD) {
                    dp_n[p_src][src] = max(dp_n[p_src][src], min(dp_n[p_dst][dst] / w, p[src]));
                }
            }
        }
    }

    plant_trees(1, 1, THRESHOLD);

    int wynik = (n == 1 ? 1 : 0);

    for (int p_src = 1; p_src <= THRESHOLD; p_src++) {
        if (mozliwe[p_src]) {

            // Jedna krawędź o wadze > sqrt(MAX).
            for (auto [u, v, w] : heavy) {
                // Po pierwsze musi być możliwe przejście do u z takim iloczynem.
                if (!dp_1[p_src][u]) continue;

                // Po drugie musi być możliwe przejście potem tą krawędzią.
                if (1LL * p_src * w > p[v]) continue;

                // Tu już się nie przekręci, bo p[v] <= 10^9.
                int p_v = p_src * w;

                int max_p_dst = query_tree(v, p_v);

                wynik = max(wynik, p_v * max_p_dst);
            }
        }
    }

    return (wynik == 0 ? -1 : wynik);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int tests = 1;
    cin >> tests;

    while (tests--) {
        cout << solve() << "\n";
    }
}