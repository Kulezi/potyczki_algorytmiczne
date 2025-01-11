// Rozwiązanie do zadania 'Liderzy [1B]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
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

constexpr int ALPHA = 26, MAXN = 500005;

void solve(int tc) {}
int cnt[MAXN];
int32_t main() {
    boost;
    int n;
    cin >> n;

    vector<int> colors;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (cnt[x] == 0) colors.push_back(x);
        cnt[x]++;
    }

    auto counts = colors;
    for (auto& i : counts) i = cnt[i];

    sort(ALL(counts));

    int j = 0;
    int ans = 0;
    for (int i = counts.size() - 1; i >= 0; i--) {
        if (counts[i] > 0) {
            ans++;
            int rem = counts[i] - 1;
            while (j < i) {
                int take = min(rem, counts[j]);
                debug() << imie(i) << imie(j) << imie(take);
                counts[j] -= take;
                rem -= take;
                if (counts[j] > 0) break;
                j++;
            }
        }
    }

    cout << ans << "\n";
}