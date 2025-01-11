// Rozwiązanie błędne do zadania 'Kraniki [5B]'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2 / 64)
// Złożoność pamięciowa: O(n)
// Punkty: 1

#include <bits/stdc++.h>
#pragma GCC target("lzcnt,popcnt")
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

constexpr int MAXN = 500010;
constexpr int BITSET_SIZE = 1024;
vector<int> g[MAXN];
vector<int> rev[MAXN];
constexpr int MOD = 1'000'000'007;
int ancestors[MAXN];
int tree[2 * 4 * MAXN];
bitset<BITSET_SIZE> reach[MAXN];

int power(int x, int y) {
    int res = 1;
    int pot = x;
    while (y) {
        if (y & 1) res = 1LL * res * pot % MOD;
        pot = 1LL * pot * pot % MOD;
        y >>= 1;
    }

    return res;
}

int inv(int x) { return power(x, MOD - 2); }

int pytaj(int pos, int l, int r, int x) {
    int res = -1;
    while (l < r) {
        res = max(res, tree[pos]);
        int mid = (l + r) / 2;
        pos *= 2;
        if (x <= mid) {
            r = mid;
        } else {
            pos++;
            l = mid + 1;
        }
    }

    res = max(res, tree[pos]);
    return res;
}

void maluj(int pos, int l, int r, int ql, int qr, int color) {
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        tree[pos] = color;
        return;
    }

    int mid = (l + r) >> 1;
    maluj(pos * 2, l, mid, ql, qr, color);
    maluj(pos * 2 + 1, mid + 1, r, ql, qr, color);
}

void fin(int &x) {
    x = 0;
    char c; // Undefined behaviour !!!
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}

int32_t main() {
    int n;
    fin(n);
    // n = 250000;
    auto add_edge = [&](int l, int r) {
        if (r == -1) return;
        g[r].push_back(l);
    };

    for (int i = 0; i < n; i++) {
        int l, r;
        // l = i+1, r = 2*n-i;
        fin(l);
        fin(r);

        int kto_l = pytaj(1, 1, 2 * n, l) - 1;
        int kto_r = pytaj(1, 1, 2 * n, r) - 1;
        add_edge(i, kto_l);

        if (kto_l != kto_r) add_edge(i, kto_r);

        maluj(1, 1, 2 * n, l, r, i + 1);
    }

    for (int l = 0; l < n; l += BITSET_SIZE) {
        for (int i = min(n - 1, l + BITSET_SIZE); i >= 0; --i) {
            reach[i].reset();
        }
        for (int i = l; i <= min(n - 1, l + BITSET_SIZE - 1); ++i) {
            reach[i][i - l] = 1;
        }

        for (int i = min(l + BITSET_SIZE - 1, n - 1); i >= 0; --i) {
            for (auto anc : g[i]) {
                reach[i] |= reach[anc];
            }
        }

        for (int i = 0; i <= min(n - 1, l + BITSET_SIZE - 1); ++i) {
            ancestors[i] += reach[i].count();
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += inv(ancestors[i]);
        if (res >= MOD) res -= MOD;
    }

    cout << res << "\n";
}