// Rozwiązanie do zadania 'Alchemik Bajtazar [2B]' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;
using pii = pair<int,int>;
struct Move {
    char ch;
    int a, b;
};

int ROOT = 1;

vector<Move> get_moves(int n) {
    int m;
    cin >> m;

    vector g(n+1, (vector<int>()));
    set<pii> edges;

    auto add_edge = [&](int a, int b) -> bool {
        if (a > b) swap(a, b);
        if (edges.count({a, b})) return false;
        edges.insert({a, b});
        return true;
    };

    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        add_edge(a, b);
    }

    vector<Move> res;
    vector vis(n+1, 0);
    auto put_edges = [&](int v, auto &&put_edges) -> void {
        vis[v] = 1;
        if (v != ROOT) {
            if (add_edge(ROOT, v)) res.emplace_back('+', ROOT, v);
        }
        for (auto u : g[v]) {
            if (!vis[u]) put_edges(u, put_edges);
        }
    };

    put_edges(ROOT, put_edges);

    // Root is connected to everything now, remove all edges
    for (auto [a, b] : edges) {
        if (a != 1 && b != 1) {
            res.emplace_back('-', a, b);
        }
    }

    return res;
}

int32_t main() {
    boost;
    int n;
    cin >> n;
    vector<Move> moves_to_star = get_moves(n);
    vector<Move> moves_from_star = get_moves(n);

    reverse(ALL(moves_from_star));
    for (auto &i : moves_from_star) i.ch = (i.ch == '+' ? '-' : '+');

    int r = moves_to_star.size() + moves_from_star.size();
    cout << r << "\n";
    for (auto i : moves_to_star) cout << i.ch << " " << i.a << " " << i.b << "\n";
    for (auto i : moves_from_star) cout << i.ch << " " << i.a << " " << i.b << "\n";
}