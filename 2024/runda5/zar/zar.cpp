// Rozwiązanie do zadania 'Żarówki [5C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 10

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

constexpr int MAXN = 200005, MOD = 1'000'000'007;

void solve(int tc) {}
int zapalony[MAXN];
vector<int> g[MAXN];
int n, m;
vector<int> cc[MAXN];
int sz[MAXN], fac[MAXN];
int get_size(int v, int c) {
    cc[c].push_back(v);
    sz[v] = 1;
    for (auto u : g[v]) {
        if (!sz[u]) sz[v] += get_size(u, c);
    }
    return sz[v];
}

int color[MAXN];
bool is_bipartite(int v, int c) {
    color[v] = c;
    for (auto u : g[v]) {
        if (!color[u] && !is_bipartite(u, (c == 1 ? 2 : 1)))
            return false;
        else if (color[v] == color[u])
            return false;
    }

    return true;
}

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

int choose(int N, int K) { return (1LL * fac[N] * inv(fac[N - K]) % MOD) * inv(fac[K]) % MOD; }

int pot2[MAXN];
int32_t main() {
    boost;
    cin >> n >> m;
    fac[0] = pot2[0] = 1;
    for (int i = 1; i <= n; i++)
        cin >> zapalony[i], fac[i] = 1LL * fac[i - 1] * i % MOD,
                            pot2[i] = 1LL * pot2[i - 1] * 2 % MOD;

    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (!sz[i]) {
            int sz = get_size(i, i);
            if (is_bipartite(i, 1)) {
                int A = 0, B = 0;
                int C = 0, D = 0;
                for (auto j : cc[i]) {
                    if (color[j] == 1) {
                        A++;
                        if (zapalony[j]) C++;
                    } else {
                        B++;
                        if (zapalony[j]) D++;
                    }
                }

                debug() << imie(vector<int>{A, B, C, D});
                int mi = min(C, D);
                C -= mi;
                D -= mi;
                int bal = D - C;
                bal += A;

                debug() << imie(bal) << imie(sz);
                ans = 1LL * ans * choose(sz, bal) % MOD;
            } else {
                ans = 1LL * ans * pot2[sz - 1] % MOD;
            }
        }
    }

    cout << ans << "\n";
}