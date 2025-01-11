// Rozwiązanie wolne do zadania 'Bardzo Ulubiony Ciąg 3 [5C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^4)
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

constexpr int ALPHA = 26;

void solve(int tc) {}

constexpr int MAX_N = 500, MAX_A = 20000;
constexpr int OFFSET = MAX_N * MAX_A;
int cnt[MAX_N * MAX_A * 2 + 5];
int32_t main() {
    boost;
    int n;
    cin >> n;


    vector<int> pref(n+1, 0), a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }


    vector<int> v;
    for (int i = 1; i <= n; i++) {
        int s = 0;
        for (int j = i; j <= n; j++) {
            s += a[j];
            v.push_back(s);
            cnt[s + OFFSET]++;
        }

    }

    sort(ALL(v));
    v.erase(unique(ALL(v)), v.end());
    int N = v.size();
    vector<int> sc;

    ll res = 1LL * cnt[OFFSET] * (cnt[OFFSET] - 1) * (cnt[OFFSET] - 2) / 6;
    ll trujki = 0;
    for (int i = 0; i < N; i++) {
        int c_i = cnt[v[i] + OFFSET];
        if (v[i] != 0)
            res += 1LL * c_i * (c_i - 1) * (cnt[OFFSET - 2 * v[i]]) / 2;
        for (int j = i + 1; j < N; j++) {
            int c_j = cnt[v[j] + OFFSET];
            int need = -(v[i] + v[j]);
            if (need == v[i] || need == v[j]) continue;
            trujki += 1LL * c_i * c_j * cnt[need + OFFSET];
        }
    }
    
    cout << res + trujki / 3 << "\n";

}