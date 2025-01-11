// Rozwiązanie błędne do zadania 'Modernizacja Bajtocji [1A]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 1

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
constexpr int MIN_N = 1, MAX_N = 300'000;
constexpr int MIN_Q = 1, MAX_Q = 1'000'000;

enum { ADD, REMOVE };
struct Op {
    int op, a, b;
};
vector<Op> ops;
int n, ADDS;
void answer(int x) {
    int N = ADDS;
    int has = false, nohas = false;
    for (int mask = 0; mask < (1 << N); mask++) {
        vector<int> has_puter(n + 1, 0);
        int i = 0;
        bool valid = true;
        for (auto op : ops) {
            if (op.op == REMOVE) {
                if (has_puter[op.a] == 1) {
                    has_puter[op.a] = 0;
                } else {
                    valid = false;
                    break;
                }
            } else {
                if (mask >> i & 1) {
                    // assume a has puter
                    if (has_puter[op.a])
                        valid = false;
                    else
                        has_puter[op.a] = 1;
                } else {
                    // assume b has puter
                    if (has_puter[op.b])
                        valid = false;
                    else
                        has_puter[op.b] = 1;
                }

                i++;
            }
        }

        if (valid) {
            if (has_puter[x])
                has = 1;
            else
                nohas = 1;
        }
    }

    if (has && nohas)
        cout << "?";
    else if (has)
        cout << "1";
    else
        cout << "0";
    assert(has || nohas);
}

int32_t main() {
    boost;

    int q;
    cin >> n;
    assert(n >= MIN_N);
    assert(n <= MAX_N);

    cin >> q;
    assert(q >= MIN_Q);
    assert(q <= MAX_Q);

    while (q--) {
        string op;
        cin >> op;
        if (op == "?") {
            int a;
            cin >> a;
            answer(a);
        } else if (op == "-") {
            int x;
            cin >> x;
            ops.push_back({REMOVE, x});
        } else {
            int a, b;
            cin >> a >> b;
            ops.push_back({ADD, a, b});
            ADDS++;
        }
    }

    cout << "\n";
}