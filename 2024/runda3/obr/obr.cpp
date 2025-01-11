
// Rozwiązanie do zadania 'Obrazy [3C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
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

int32_t main() {
    boost;
    int h, w;
    cin >> h >> w;

    int n;
    cin >> n;

    vector<int> d(n);
    for (auto &i: d) cin >> i;

    if (h % d[0] != 0 || w % d[0] != 0 || d[0] > min(h, w)) { 
        cout << "-1\n";
        return 0;
    }

    auto solve = [&](int large, int small, auto &&solve) -> ll {
        debug() << imie(large) << imie(small);
        if (large < small) swap(large, small);
        if (large == 0 || small == 0) return 0;
        for (int i = n - 1; i >= 0; i--) {
            if (large == small && large == d[i]) return 1;
            if (d[i] <= small) {
                return (large / d[i]) * solve(d[i], small, solve) + solve(large % d[i], small, solve); 
            }
        }
    };

    

    cout << solve(h, w, solve) << "\n";
}