// Rozwiązanie do zadania 'Łamigłówka 3 [4C]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*m)
// Złożoność pamięciowa: O(n*m)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

#define dbg(x) cerr << #x << " = " << x << "\n"
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
constexpr int MAXN = 2005, A = 26;
array<int, A> cnt[2][MAXN];
int n, m;
string s[2][MAXN];
int rozne[2][MAXN];
enum {
    ROW,
    COL,
};

vector<vector<int>> ans;
void dfs(int i, int TYP) {
    char ch;
    for (auto j : s[TYP][i])
        if (j >= 'A' && j <= 'Z') ch = j;
    assert(ch >= 'A' || ch <= 'Z');
    ans.push_back({TYP, i, ch});

    vector<int> pusc;
    for (int j = 0; j < s[TYP][i].size(); j++) {
        int c = s[TYP][i][j];
        if (c == '.') continue;
        s[TYP][i][j] = '.';
        s[1 - TYP][j][i] = '.';

        cnt[TYP][i][c - 'A']--;
        if (cnt[TYP][i][c - 'A'] == 0) rozne[TYP][i]--;

        cnt[1 - TYP][j][c - 'A']--;
        if (cnt[1 - TYP][j][c - 'A'] == 0) rozne[1 - TYP][j]--;

        if (rozne[1 - TYP][j] == 1) pusc.push_back(j);
    }

    for (auto j : pusc) {
        if (rozne[1 - TYP][j] == 1) dfs(j, 1 - TYP);
    }
}

int32_t main() {
    boost;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[ROW][i];
        for (int j = 0; j < m; j++) {
            char c = s[ROW][i][j];
            s[COL][j].push_back(c);

            cnt[ROW][i][c - 'A']++;
            if (cnt[ROW][i][c - 'A'] == 1) rozne[ROW][i]++;
            cnt[COL][j][c - 'A']++;
            if (cnt[COL][j][c - 'A'] == 1) rozne[COL][j]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (rozne[ROW][i] == 1) dfs(i, ROW);
    }

    for (int i = 0; i < m; i++) {
        if (rozne[COL][i] == 1) dfs(i, COL);
    }

    reverse(ALL(ans));
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << (i[0] == ROW ? "R" : "K") << " " << i[1] + 1 << " " << (char)i[2] << "\n";
    }
}