// Rozwiązanie do zadania 'Mnożenie cyfr [3B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(Ψ(N, D) * log(N) * D +  Ψ(N, D)' * q), gdzie:
// Ψ(n, D) to liczba liczb D-gładkich mniejszych od n, ~66000,
// Ψ(n, D) to liczba liczb D-gładkich nie zawierających cyfry 0, ~1000,
// D to liczba cyfr,
// N to maksymalne n z wejścia,
// Złożoność pamięciowa: O(Ψ(N, D) * log(N) * D)
// Punkty: 10


#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
constexpr ll MAX_LEN = 19, MAX_CYFRA = 9, MAX_GENERATORKI = 66063;

ll MAX_N;

// dp[g][l][c] = Ile liczb o l cyfrach (bez zer) tż. najbardziej znacząca cyfra jest <= c trafia w
// pierwszym ruchu do g-tej generatorki.
ll dp[MAX_GENERATORKI + 5][MAX_LEN + 5][MAX_CYFRA + 5];
ll cnt[MAX_CYFRA + 5][MAX_LEN + 5][MAX_CYFRA + 5];

int GENERATORKI, WAZNE_GENERATORKI;
ll generatorki[MAX_GENERATORKI];
int wazne_generatorki[MAX_GENERATORKI];
int generatorki_konce[MAX_GENERATORKI];
int tnij[MAX_GENERATORKI][MAX_CYFRA + 2];

int ktora(ll x) {
    int l = 0, r = GENERATORKI - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (generatorki[m] == x)
            return m;
        else if (generatorki[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return l;
}

int cyfra(ll n) {
    while (n >= 10) {
        ll nowe_n = 1;
        while (n > 0) nowe_n *= n % 10, n /= 10;
        n = nowe_n;
    }

    return (int)n;
}

void preprocess() {
    // Generujemy wszystkie możliwe liczby, do których można trafić po pierwszym mnożeniu cyfr.
    // Jest ich 66061, czyli 'jakoś mało'.
    for (ll a = 1; a <= MAX_N; a *= 2) {
        for (ll b = a; b <= MAX_N; b *= 3) {
            for (ll c = b; c <= MAX_N; c *= 5) {
                for (ll d = c; d <= MAX_N; d *= 7) {
                    generatorki[GENERATORKI++] = d;
                }
            }
        }
    }

    sort(generatorki, generatorki + GENERATORKI);

    for (int g = 0; g < GENERATORKI; g++) {
        ll G = generatorki[g];
        generatorki_konce[g] = cyfra(G);
        if (generatorki_konce[g] != 0) wazne_generatorki[WAZNE_GENERATORKI++] = g;
        for (int c = 0; c <= MAX_CYFRA; c++) {
            if (c == 0 || G % c != 0)
                tnij[g][c] = -1;
            else
                tnij[g][c] = ktora(G / c);
        }
    }

    // Przypadek bazowy: Pojedyńcze cyfry są osiągalne tylko z siebie.
    for (int g = 0; g < MAX_CYFRA; g++) {
        int c = g + 1;
        assert(generatorki[g] == c);
        for (int i = c; i <= MAX_CYFRA; i++) dp[g][1][i] = 1;
    }

    for (int l = 2; l <= MAX_LEN; l++) {
        for (int g = 0; g < GENERATORKI; g++) {
            for (int c = 1; c <= MAX_CYFRA; c++) {
                dp[g][l][c] = dp[g][l][c - 1];
                int g_trimmed = tnij[g][c];
                if (g_trimmed != -1) {
                    dp[g][l][c] += dp[g_trimmed][l - 1][9];
                    cnt[generatorki_konce[g]][l][c] += dp[g_trimmed][l - 1][c];
                }
            }
        }
    }
}

void solve(ll n) {
    vector<ll> ile(MAX_CYFRA + 1, 0);
    ile[0] = n;

    string s = to_string(n);
    int L = (int)s.size();

    for (int w = 0; w < WAZNE_GENERATORKI; w++) {
        int g = wazne_generatorki[w];
        ll sum = 0;
        // Dodajemy wszystkie liczby, które sa krótsze.
        for (int l = 1; l <= L - 1; l++) {
            sum += dp[g][l][9];
        }

        int g_trimmed = g;
        // Zakładamy, że pierwsza różnica jest na sufiksie o długości L.
        for (int l = L, s_idx = 0; l >= 1; l--, s_idx++) {
            int c = s[s_idx] - '0';

            // Jak mamy już zero w liczbie to wliczymy je z dopełnienia, saga.
            if (c == 0) break;

            // cerr << dbg(g) << dbg(l) << dbg(c-1) << dbg(dp[g][l][c-1]) << endl;
            // Dodajemy wszystkie liczby, które mają mniejszą najbardziej znaczącą cyfrę.
            sum += (c < 1 ? 0 : dp[g_trimmed][l][c - (l == 1 ? 0 : 1)]);

            g_trimmed = tnij[g_trimmed][c];
            if (g_trimmed == -1) break;
            // cerr << dbg(G) << dbg(l) << dbg(c) << dbg(sum) << endl;
        }

        // cerr << dbg(g) << dbg(generatorki[g]) << dbg(generatorki_konce[g]) <<
        // dbg(dp[g][1][generatorki[g]]) << dbg(sum) << endl;
        ile[generatorki_konce[g]] += sum;
        ile[0] -= sum;
    }

    for (int i = 0; i <= MAX_CYFRA; i++) cout << ile[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int q;
    cin >> q;
    vector<ll> zapytania(q);
    for (auto &n : zapytania) cin >> n;

    MAX_N = max(10000LL, *max_element(all(zapytania)));
    preprocess();

    for (auto n : zapytania) solve(n);
}