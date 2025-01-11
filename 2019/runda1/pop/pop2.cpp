// Nieudane przyśpieszenie bruta do zadania 'Muzyka pop [1A]' Z Potyczek Algorytmicznych 2019.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m)
// Złożoność pamięciowa: O(n * m)
// Punkty: 2 (upsolve)

#include <bits/stdc++.h>
#define int ll
#define dbg(x) #x << " = " << x << " "
#define is_lit(n, k) (n >> k & 1)
#define flip(n, k) n ^= (1LL << (ll)k)
using namespace std;
using ll = long long;
int highest_bit(ll n) {
    int ret = -1;
    while (n > 0) {
        n >>= 1;
        ret++;
    }

    return ret;
}

// Zwraca największa liczbę o k bitach mniejszą od n.
// Złożoność czasowa: O(log(n)).
ll largest_k_bit_under_n_fast(ll n, ll k) {
    int h = highest_bit(n);
    int have = __builtin_popcount(n);
    if (have <= k) {
        int zeros = 0, ones = 0;
        int want_zeros = k - have + 1;
        for (int i = 0; i <= h; i++) {
            if (!is_lit(n, i))
                zeros++;
            else
                ones++;

            if (zeros >= want_zeros && is_lit(n, i)) {
                flip(n, i);

                int want_ones = (k - have + 1) + (ones - 1);
                for (int j = i - 1; j >= 0; j--) {
                    if (want_ones) {
                        want_ones--;
                        if (!is_lit(n, j)) flip(n, j);
                    } else {
                        if (is_lit(n, j)) flip(n, j);
                    }
                }

                return n;
            }
        }
    } else {
        for (int i = 0; i <= h; i++) {
            if (have > k && is_lit(n, i)) {
                flip(n, i);
                have--;
            }
        }
        return n;
    }

    return -1;
}

ll R(ll a, ll b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(a, b)(rng);
}

map<pair<int, ll>, ll> dp;
constexpr int MAXN = 205, MAXB = 60;
constexpr ll INF = 1e18;
ll a[MAXN];
int states = 0;
ll get_dp(int n, ll m) {
    if (n == 0) return 0;
    if (dp.count({n, m})) return dp[{n, m}];
    states++;
    ll best = -INF;

    if (a[n] == 0) {
        return dp[{n, m}] = get_dp(n - 1, m - 1);
    }

    vector<pair<ll, int>> pary;
    for (int b = MAXB - 1; b >= 0; b--) {
        ll new_m = largest_k_bit_under_n_fast(m, b);
        if (new_m < n - 1) continue;
        pary.emplace_back(new_m, b);
    }

    for (auto [m1, b1] : pary) {
        int byl_lepszy = false;
        for (auto [m2, b2] : pary) {
            if (a[n] > 0 && m1 < m2 && b2 > b1) {
                byl_lepszy = true;
            } else if (a[n] < 0 && m1 < m2 && b2 < b1) {
                byl_lepszy = true;
            }
        }

        if (!byl_lepszy) best = max(best, get_dp(n - 1, m1) + a[n] * b1);
    }

    return dp[{n, m}] = best;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    ll k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cout << get_dp(n, k + 1) << "\n";

    // Oj tych stanów to niewiele mniej wychodzi...
    cerr << "fast: " << dp.size() << "\n";
}