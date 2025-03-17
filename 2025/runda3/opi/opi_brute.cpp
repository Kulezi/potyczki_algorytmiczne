// Rozwiązanie brutalne do zadania 'Opieka [3A]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(L^n * n^2)
// Złożoność pamięciowa: O(1)
// Punkty: ???

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

struct rational {
    int p, q;

    void print() { cout << p << "/" << q << "\n"; }
};

bool compare(rational a, rational b) { return 1LL * a.p * b.q < 1LL * b.p * a.q; }

rational normalize(int a, int b) {
    if (a == 0) return {a, abs(b)};

    if (b < 0) {
        a = -a;
        b = -b;
    }

    int g = abs(__gcd(a, b));
    return {a / g, b / g};
}
constexpr int MAXN = 19, MAXL = 10005, MAXL_NATURALIZED = MAXL * MAXN;
bitset<MAXL> blocked[MAXN];
bitset<MAXL_NATURALIZED> wolny[MAXN];
int dostepni[MAXL_NATURALIZED];

int n, L, T;
bool jest_git(int opiekun, int l, int r) {
    for (int i = l; i < r; i++)
        if (!wolny[opiekun][i] || dostepni[i] <= 1) return false;
    return true;
}

bool bergentruckung(int opiekun) {
    if (opiekun == n) return true;
    for (int start = 0; start + T <= L; start++) {
        int mini = MAXN;
        if (jest_git(opiekun, start, start + T)) {
            for (int i = start; i < start + T; i++) {
                dostepni[i]--;
                wolny[opiekun][i].flip();
            }
            if (bergentruckung(opiekun + 1)) return true;
            for (int i = start; i < start + T; i++) {
                dostepni[i]++;
                wolny[opiekun][i].flip();
            }
        }
    }

    return false;
}

int q = 1;

void solve(int tc) {
    int L_original;
    cin >> n >> L_original;

    vector good(L_original, false);
    for (int row = 0; row < n; row++) {
        string s;
        cin >> s;
        for (int col = 0; col < L_original; col++) {
            blocked[row][col] = (s[col] == 'X' ? 1 : 0);
            if (!blocked[row][col]) good[col] = true;
        }
    }

    for (auto covered : good) {
        if (!covered) {
            cout << "-1\n";
            return;
        }
    }

    if (n == 1) {
        cout << "0/1\n";
        return;
    }

    vector<rational> ulamki;
    for (int mianownik = 1; mianownik <= n; mianownik++) {
        for (int licznik = 0 + (mianownik > 1); licznik <= mianownik * L_original; licznik++) {
            if (__gcd(mianownik, licznik) == 1) {
                ulamki.push_back(rational{licznik, mianownik});
            }
        }
    }

    sort(ulamki.begin(), ulamki.end(),
         [](const auto &lhs, const auto &rhs) { return compare(lhs, rhs); });

    auto check = [&](rational mid) {
        T = mid.p;
        L = L_original * mid.q;
        for (int c = 0; c < L; c++) dostepni[c] = 0;

        for (int row = 0; row < n; row++) {
            int col_expanded = 0;
            for (int col = 0; col < L_original; col++) {
                for (int rep = 0; rep < mid.q; rep++) {
                    if (!blocked[row][col]) dostepni[col_expanded]++;
                    wolny[row][col_expanded] = !blocked[row][col];
                    col_expanded++;
                }
            }
        }

        bool ret = bergentruckung(0);
        // cerr << dbg(mid.p) << dbg(mid.q) << dbg(ret) << endl;
        return ret;
    };

    int lo = 0, hi = ulamki.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(ulamki[mid]))
            lo = mid;
        else
            hi = mid - 1;
    }

    ulamki[lo].print();
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int q = 1;
    cin >> q;
    for (int tc = 1; tc <= q; tc++) {
        if (tc % 1000 == 0) cerr << q - tc << endl;
        solve(tc);
    }
}