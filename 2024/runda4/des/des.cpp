// Rozwiązanie do zadania 'Desant 3 [4B]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^(n/2) * (m + n^2))
// Złożoność pamięciowa: O(n + m)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

constexpr int MAXN = 36, MAXM = 1005;
int ans[MAXN], kaunter[MAXN], prefy[MAXN];
int A[MAXM], B[MAXM];
int n, m;

const string ioi = "101";
bool has_101(string& s) {
    int pos = 0;
    for (auto i : s) {
        if (i == ioi[pos]) {
            pos++;
            if (pos == 3) return 1;
        }
    }

    return 0;
}

int razy;
void policz(string s) {
    razy++;
    // for (int l = 0; l < n; l++) {
    //     for (int r = l; r < n; r++) {
    //         string k = s;
    //         int ones = 0;
    //         for (int j = 0; j < n; j++) {
    //             if (k[j] == '?') {
    //                 if (j >= l && j <= r) k[j] = '1';
    //                 else k[j] = '0';
    //             }
    //             if (k[j] == '1') ones++;
    //         }

    //         int inside = 0;
    //         for (int j = l; j <= r; j++) if (k[j] == '1') inside++;
    //         if (ones == inside && ones == r-l+1) debug() << imie(s) << imie(l) << imie(r);
    //         if (ones == inside && ones == r-l+1) ans[r-l+1] ^= 1;
    //     }
    // Wywal to, to jest O(n^3)
    // Policz to jakos w O(n)
    // Dobra ten stringor jak ma 101 jako podciag to niech sie...
    // Jak nie ma pewnych jedynek to ciag wyglada jakos tak ?????0???0?00?00?000
    // Czyli dasz +1 dla kazdego z k ktore sie miesci w samych pytajniczkach
    // Teraz masz jakies pewne jedynki ktore mieszcza sie przedziale [a, b]
    // Dla uproszczenia na poczatek i na koniec dodajemy 0, wtedy wszystkie szukane przedzialy
    // Niech z_l = max pozycja z zerem < a, z_r min pozycja z zerem > b
    // Sksorujemy 1 dla kazdego przedzialu zawartego w [z_l+1, z_r-1] i zawierajacego [a, b]

    if (s.find("1") == s.npos) {
        int pytajniki = 0;
        for (auto i : s) {
            if (i == '?')
                pytajniki++;
            else {
                // Dolicz wynik, daj ++ do jakiejs tablicy zeby to bylo liczone poza hotpathem.
                ++kaunter[pytajniki];
                pytajniki = 0;
            }
        }

        if (pytajniki > 0) kaunter[pytajniki] ^= 1;

        return;
    }
    if (has_101(s)) return;

    int z_l = -1, z_r = n, a = -1, b = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') b = i;
        if (s[i] == '0' && b != -1 && z_r == n) {
            z_r = i;
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') a = i;
        if (s[i] == '0' && a != -1 && z_l == -1) {
            z_l = i;
            break;
        }
    }

    // Juz mi sie nie chce klepac tego przypadku
    // Tez se wpaluje w jakas tablice zeby nie bylo w hotpathu i wylicze na pauke potem.
    // Ale najpiew pauka w n^2, albo nawet nie lol, zrobie z tego jakies prefiks sumy.
    for (int start = z_l + 1; start <= a; start++) {
        prefy[b - start + 1]++;
        prefy[(z_r - 1) - start + 1 + 1]--;
    }
}

string s;
void dfs(int ruch) {
    if (ruch == m + 1) {
        policz(s);
        return;
    }

    int a = A[ruch];
    int b = B[ruch];
    auto push = [&](char c_a, char c_b) {
        char old_a = s[a], old_b = s[b];
        s[a] = c_a;
        s[b] = c_b;
        dfs(ruch + 1);
        s[a] = old_a;
        s[b] = old_b;
    };

    if (s[a] == '?' && s[b] == '?') {
        push('0', '0');
        push('1', '1');
    } else if (s[a] == '?' && s[b] == '0') {
        push('0', '?');
    } else if (s[a] == '1' && s[b] == '?') {
        push('?', '1');
    } else if (s[a] == '1' && s[b] == '0') {
        push('0', '1');
    } else {
        push(s[a], s[b]);
    }
}

int32_t main() {
    boost;

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> A[i] >> B[i];
        A[i]--;
        B[i]--;
    }

    s = string(n, '?');
    dfs(1);

    // Wpałuj zliczone ciagi samych pytajnikow miedzy zerami.
    for (int pytajniki = 1; pytajniki <= n; pytajniki++) {
        for (int len = 1; len <= pytajniki; len++) {
            ans[len] ^= kaunter[pytajniki] * (pytajniki - len + 1) % 2;
        }
    }

    int s = 0;
    for (int len = 1; len <= n; len++) {
        s += prefy[len];
        ans[len] ^= s % 2;
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}