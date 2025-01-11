// Rozwiązanie wolne do zadania 'Grupa permutacji [2A]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 5

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

#define sim template <class c
#define ris return *this
#define dor > debug& operator<<
#define eni(x) sim > typename enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge {
    c b, e;
};
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
    ~debug() { cerr << endl; }
    eni(!=) cerr << boolalpha << i;
    ris;
} eni(==) ris << range(begin(i), end(i));
}
sim, class b dor(pair<b, c> d) { ris << "(" << d.first << ", " << d.second << ")"; }
sim dor(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it;
    ris << "]";
}
#else
    sim dor(const c&) { ris; }
#endif
}
;

#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define dbg(x) cerr << #x << " = " << x << "\n"
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

const int MOD = 1'000'000'007;
int power(int x, int y) {
    int res = 1;
    int pot = x;
    while (y) {
        if (y & 1) res = 1LL * res * pot % MOD;
        pot = 1LL * pot * pot % MOD;

        y /= 2;
    }

    return res;
}

int inv(int x) { return power(x, MOD - 2); }

constexpr int MAXN = 3005;
int perm[MAXN][MAXN];

int n, k;
int color[MAXN][MAXN];
int res;
int COLOR;
pii ulamki[MAXN * MAXN];
vector<pii> g[MAXN][MAXN];

void bfs(int pos_i, int pos_j) {
    COLOR++;
    queue<pii> q;
    q.push({pos_i, pos_j});
    color[pos_i][pos_j] = COLOR;

    while (!q.empty()) {
        auto [pos_i, pos_j] = q.front();
        q.pop();
        ulamki[COLOR].second++;
        if (pos_i > pos_j) ulamki[COLOR].first++;
        for (int p = 0; p < k; p++) {
            int x = perm[p][pos_i];
            int y = perm[p][pos_j];
            if (!color[x][y]) {
                color[x][y] = COLOR;
                q.push({x, y});
            }
        }
    }
}

int32_t main() {
    boost;
    cin >> n >> k;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            perm[i][j] = x - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            COLOR++;
            if (!color[i][j]) bfs(i, j);
            res += 1LL * ulamki[color[i][j]].first * inv(ulamki[color[i][j]].second) % MOD;
            if (res >= MOD) res -= MOD;
        }
    }

    cout << res << "\n";
}