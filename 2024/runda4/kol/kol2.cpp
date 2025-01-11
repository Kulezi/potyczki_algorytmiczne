// Rozwiązanie brutalne do zadania 'Kolorowy las [4A]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * (log(n) + n)
// Złożoność pamięciowa: O(n)
// Punkty: 2

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

constexpr int MAXN = 200005;
int n, m, q;
set<pii> g[MAXN];
int kolor[MAXN];

void maluj(int v, int par, ll z, int k) {
    if (z < 0) return;
    kolor[v] = k;
    for (auto [u, d] : g[v]) {
        if (u != par) maluj(u, v, z - d, k);
    }
}


int32_t main() {
    boost;
    cin >> n >> m >> q;

    for (int i = 1; i <= m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].insert({b, w});
        g[b].insert({a, w});
    }

    while (q--) {
        int typ;
        cin >> typ;

        if (typ == 1) {
            int a, b, d;
            cin >> a >> b >> d;
            g[a].insert({b, d});
            g[b].insert({a, d});
        } else if (typ == 2) {
            int a, b;
            cin >> a >> b;
            g[a].erase(g[a].lower_bound({b, 0}));
            g[b].erase(g[b].lower_bound({a, 0}));
        } else if (typ == 3) {
            int v, k;
            ll z;
            cin >> v >> z >> k;
            maluj(v, -1, z, k);
        } else {
            int v;
            cin >> v;
            cout << kolor[v] << "\n";
        }
    }

}