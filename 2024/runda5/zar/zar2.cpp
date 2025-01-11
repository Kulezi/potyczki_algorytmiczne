// Rozwiązanie brutalne do zadania 'Żarówki [5C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n)
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

constexpr int MOD = 1'000'000'007;

constexpr int MAXN = 200005;
vector<int> g[MAXN];

set<string> vis;
int n, m;
char inv(char c) {
    if (c == '1') return '0';
    return '1';
}

string parzystosc(string s) {
    int cnt = 0;
    for (auto i : s) {
        if (i == '0') cnt++;
    }

    if (cnt % 2 == s.size() % 2) return "tesame";
    return "rozne";
}

int res = 0;
vector<int> cc[MAXN];
string obetnij(int v, string s) {
    string ret;
    for (auto i : cc[v]) ret += s[i];
    return ret;
}

void dfs(string &s, int ccc) {
    vis.insert(obetnij(ccc, s));
    res++;
    // if (count_101(s) != count_101(id)) {
    //     cout << s << " " << id << "\n";
    //     exit(1);
    // }

    for (int i = 0; i < n; i++) {
        for (auto j : g[i]) {
            if (s[i] == s[j]) {
                s[i] = inv(s[i]);
                s[j] = inv(s[j]);
                if (!vis.count(obetnij(ccc, s))) dfs(s, ccc);
                s[i] = inv(s[i]);
                s[j] = inv(s[j]);
            }
        }
    }
}
int32_t main() {
    boost;
    cin >> n >> m;
    string input(n, '0');
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        input[i - 1] = x + '0';
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> viss(n, 0);
    auto get_cc = [&](int v, int COLOR, auto && self) -> void {
        cc[COLOR].push_back(v);
        viss[v] = COLOR;
        for (auto u : g[v]) if (!viss[u]) self(u, COLOR, self);
    };

    int colors = 0;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (!viss[i]) {
            get_cc(i, ++colors, get_cc);
            vis.clear();
            dfs(input, colors);
            ans = 1LL * ans * res % MOD;
            res = 0;
        }
    }

    cout << ans << "\n";
}

// 111111111111110101010101
//

// 1 - 3 - 5  4-2
// --------