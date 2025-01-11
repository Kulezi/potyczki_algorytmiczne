// Rozwiązanie wolne do zadania 'Kraniki [5B]'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2/64)
// Złożoność pamięciowa: O(n)
// Punkty: 4

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

constexpr int MAXN = 500005;
vector<int> g[MAXN];
constexpr int MOD = 1'000'000'007;

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

ll reach[MAXN];
int ancestors[MAXN];
int tree[8 * MAXN];
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

    int mid = (l + r) / 2;
    maluj(pos * 2, l, mid, ql, qr, color);
    maluj(pos * 2 + 1, mid + 1, r, ql, qr, color);
}

int32_t main() {
    boost;
    int n;
    cin >> n;
    // n = 100000;
    auto add_edge = [&](int l, int r) {
        if (r == -1) return;
        g[r].push_back(l);
    };

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        // l = i;
        // r = 2*n-i+1;

        int kto_l = pytaj(1, 1, 2 * n, l) - 1;
        int kto_r = pytaj(1, 1, 2 * n, r) - 1;
        add_edge(i, kto_l);

        if (kto_l != kto_r) add_edge(i, kto_r);

        maluj(1, 1, 2 * n, l, r, i + 1);
    }

    for (int l = 0; l < n; l += 64) {
        for (int i = n - 1; i >= 0; --i) {
            reach[i] = 0;
            if (i >= l && i < l + 64) reach[i] |= (1LL << (i - l));
            for (auto anc : g[i]) {
                reach[i] |= reach[anc];
            }
            ancestors[i] += __builtin_popcountll(reach[i]);
        }
    }

    int res = 0;
    ll sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        res += inv(ancestors[i]);
        sum += ancestors[i];
        if (res >= MOD) res -= MOD;
    }

    cerr << cnt << "\n";

    cout << res << "\n";
}