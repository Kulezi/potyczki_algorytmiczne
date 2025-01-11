// Rozwiązanie do zadania 'Modernizacja Bajtocji [1A]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 10 (upsolve)

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
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAXN = 300'005, MAXQ = 1'000'005;
int SETS;
int r[MAXN];
set<int> ppl[MAXN + MAXQ];

void Split(int x) {
    if (x == -1) return;
    for (auto i : ppl[x]) r[i] = -1;
}

int32_t main() {
    boost;

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        r[i] = ++SETS;
        ppl[SETS] = {i};
    }

    string ans;
    while (q--) {
        debug();
        for (int i = 1; i <= SETS; i++) debug() << imie(i) << imie(ppl[i]);
        string typ;
        cin >> typ;
        if (typ == "+") {
            int a, b;
            cin >> a >> b;
            int ra = r[a];
            int rb = r[b];

            if (ra == -1 || ra == rb) {
                Split(rb);
            } else if (rb == -1) {
                Split(ra);
            } else {
                if (ppl[ra].size() > ppl[rb].size()) swap(ra, rb);
                for (auto i : ppl[ra]) {
                    r[i] = rb;
                    ppl[rb].insert(i);
                }
            }
        } else if (typ == "-") {
            int a;
            cin >> a;

            if (r[a] != -1) ppl[r[a]].erase(a);
            r[a] = ++SETS;
            ppl[SETS] = {a};
        } else if (typ == "?") {
            int a;
            cin >> a;

            if (r[a] == -1)
                ans += "1";
            else if (ppl[r[a]].size() == 1)
                ans += "0";
            else
                ans += "?";
        }
    }

    cout << ans << "\n";
}
