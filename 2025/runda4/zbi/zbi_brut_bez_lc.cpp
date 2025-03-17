// Rozwiązanie testowe do zadania 'Zbieranie klocków [4B]' z Potyczek Algorytmicznych 2025.
// Służyło do sprawdzenia czy faza przed użyciem LCT działa poprawnie.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((k + q) * (n+m)^2))
// Złożoność pamięciowa: O(n + m + k + q)
// Punkty: ???

#include <bits/stdc++.h>
#define cerr \
    if (false) cerr
#define dbg(x) " " << #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
#define cross_apply(x, y, f) \
    f(x, y);                 \
    f(x + 1, y);             \
    f(x - 1, y);             \
    f(x, y - 1);             \
    f(x, y + 1)
#define sum_vert(x, y, f) (f(x, y - 1) + f(x, y + 1))
#define sum_hor(x, y, f) (f(x - 1, y) + f(x + 1, y))
#define aggregate_square(x, y, f, op) (f(x, y) op f(x + 1, y) op f(x, y + 1) op f(x + 1, y + 1))
#define big_square_apply(x, y, f, L)              \
    for (int nx = x - L; nx <= x + L; nx++) {     \
        int W = L - abs(nx - x);                  \
        for (int ny = y - W; ny <= y + W; ny++) { \
            f(nx, ny);                            \
        }                                         \
    }

#define flip(m, x, y)      \
    if (m.count({x, y})) { \
        m.erase({x, y});   \
    } else {               \
        m.insert({x, y});  \
    }

#define print_state(layer)                               \
    cerr << #layer << endl;                              \
    for (int macro_y = m; macro_y > 0; macro_y--) {      \
        for (int macro_x = 1; macro_x <= n; macro_x++) { \
            cerr << busy_##layer(macro_x, macro_y);      \
        }                                                \
        cerr << endl;                                    \
    }                                                    \
    cerr << endl;

#define apply_updates(layer)                            \
    while (!awaiting_updates_##layer.empty()) {         \
        auto [x, y] = awaiting_updates_##layer.front(); \
        awaiting_updates_##layer.pop();                 \
        update_state_##layer(x, y);                     \
    }

#define in_board(x, y) (x >= 1 && x <= n && y >= 1 && y <= m)

using namespace std;

constexpr int MAXN = 105, INF = 2'000'000'000;

int n, m, k, q;

// Plansza po wykonaniu 0, 1, 2... zdjęć wszystkiego co się da zdjąć naraz w danej chwili.
set<pair<int, int>> layer_0, layer_1, layer_2;

int busy_layer_0(int x, int y) { return layer_0.count({x, y}); }

int busy_layer_1(int x, int y) { return layer_1.count({x, y}); }

int busy_layer_2(int x, int y) { return layer_2.count({x, y}); }

queue<pair<int, int>> awaiting_updates_layer_2, awaiting_updates_layer_3;

void push_update_state_layer_2(int x, int y) {
    if (in_board(x, y)) awaiting_updates_layer_2.push({x, y});
}
void push_update_state_layer_3(int x, int y) {
    if (in_board(x, y)) awaiting_updates_layer_3.push({x, y});
}

int full_square(int x, int y) { return aggregate_square(x, y, busy_layer_2, +) == 4; }

bool is_in_some_square(int x, int y) { return aggregate_square(x - 1, y - 1, full_square, ||); }

enum {
    NOTHING,
    NORMAL,
    BLOCKER,
};

struct Diagonala {
    vector<int> t;

    Diagonala() : t(2137, 0) {}
};

Diagonala diag[4 * MAXN];

enum Layer3State {
    EMPTY,
    LEAF,
    DIAGONAL_A,
    DIAGONAL_B,
    DIAGONAL_C,
    DIAGONAL_D,
    IMMOVABLE,
};

Layer3State get_diagonal(int x, int y) {
    // In the middle
    if (busy_layer_2(x - 1, y) && busy_layer_2(x, y - 1)) return DIAGONAL_A;
    if (busy_layer_2(x + 1, y) && busy_layer_2(x, y + 1)) return DIAGONAL_B;
    if (busy_layer_2(x + 1, y) && busy_layer_2(x, y - 1)) return DIAGONAL_C;
    if (busy_layer_2(x - 1, y) && busy_layer_2(x, y + 1)) return DIAGONAL_D;

    return LEAF;
}

map<pair<int, int>, Layer3State> layer_3;
Layer3State get_layer_3_state(int x, int y) {
    auto it = layer_3.find({x, y});
    if (it == layer_3.end())
        return EMPTY;
    else
        return it->second;
}

Layer3State recalculate_layer_3_state(int x, int y) {
    if (!busy_layer_2(x, y)) return EMPTY;
    if (is_in_some_square(x, y)) return IMMOVABLE;
    return get_diagonal(x, y);
}

int leaves = 0;

// Returns {diagonal_id, pos_in_diagonal}.
pair<int, int> get_diagonal_info(Layer3State l, int x, int y) {
    if (l == DIAGONAL_A) return {x + (y - 1), 2 * (y - 1) + 1};
    if (l == DIAGONAL_B) return {x + y, 2 * y};
    if (l == DIAGONAL_C) return {n + m + (n - (x - (y - 1)) + 1), 2 * (y - 1) + 1};
    assert(l == DIAGONAL_D);
    return {n + m + (n - (x - y) + 1), 2 * y};
}

void remove_blocker(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);
    diag[d].t[pos] = NOTHING;
}

void insert_blocker(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);
    diag[d].t[pos] = BLOCKER;
}

void remove_normal(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);
    diag[d].t[pos] = NOTHING;
}

void insert_normal(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);
    diag[d].t[pos] = NORMAL;
}

void update_state_layer_3(int x, int y) {
    cerr << __func__ << dbg(x) << dbg(y) << endl;
    Layer3State old_state = get_layer_3_state(x, y);
    Layer3State new_state = recalculate_layer_3_state(x, y);
    cerr << dbg(old_state) << dbg(new_state) << endl;
    if (old_state != new_state) {
        // Undo what was in the structures before.
        if (old_state == LEAF)
            leaves--;
        else if (old_state == IMMOVABLE) {
            for (int diag_type = DIAGONAL_A; diag_type <= DIAGONAL_D; diag_type++) {
                auto [diag_id, diag_pos] = get_diagonal_info((Layer3State)diag_type, x, y);
                cerr << "REMOVE_BLOCKER " << dbg(x) << dbg(y) << dbg(diag_id) << dbg(diag_pos)
                     << endl;
                remove_blocker(diag_id, diag_pos);
            }
        } else if (old_state != EMPTY) {
            auto [diag_id, diag_pos] = get_diagonal_info(old_state, x, y);

            cerr << "POP " << dbg(x) << dbg(y) << dbg(diag_id) << dbg(diag_pos) << endl;
            remove_normal(diag_id, diag_pos);
        }

        // And redo with new state.
        if (new_state == LEAF)
            leaves++;
        else if (new_state == IMMOVABLE) {
            for (int diag_type = DIAGONAL_A; diag_type <= DIAGONAL_D; diag_type++) {
                auto [diag_id, diag_pos] = get_diagonal_info((Layer3State)diag_type, x, y);
                cerr << "INSERT_BLOCKER " << dbg(x) << dbg(y) << dbg(diag_id) << dbg(diag_pos)
                     << endl;
                insert_blocker(diag_id, diag_pos);
            }
        } else if (new_state != EMPTY) {
            auto [diag_id, diag_pos] = get_diagonal_info(new_state, x, y);
            cerr << "PUSH " << dbg(x) << dbg(y) << dbg(diag_id) << dbg(diag_pos) << endl;
            insert_normal(diag_id, diag_pos);
        }

        layer_3[{x, y}] = new_state;
    }
}

constexpr int L = 3;
void update_state_layer_2(int x, int y) {
    int old_state = busy_layer_2(x, y);
    int new_state =
        busy_layer_1(x, y) && sum_hor(x, y, busy_layer_1) > 0 && sum_vert(x, y, busy_layer_1) > 0;
    if (old_state != new_state) {
        flip(layer_2, x, y);
        //     for (int nx = x - L; nx <= x + L; nx++) {
        //         for (int ny = y - L; ny <= y + L; ny++) {
        //             push_update_state_layer_3(nx, ny);
        //         }
        //     }
    }
}

void update_state_layer_1(int x, int y) {
    if (!in_board(x, y)) return;

    int old_state = busy_layer_1(x, y);
    int new_state =
        busy_layer_0(x, y) && sum_hor(x, y, busy_layer_0) > 0 && sum_vert(x, y, busy_layer_0) > 0;
    if (old_state != new_state) {
        flip(layer_1, x, y);
        // cross_apply(x, y, push_update_state_layer_2);
    }
}

void flip_cell(int x, int y) {
    assert(in_board(x, y));
    cerr << __func__ << dbg(x) << dbg(y) << endl;

    // Update layer_0.
    flip(layer_0, x, y);

    // Update layer_1.
    // cross_apply(x, y, update_state_layer_1);
    big_square_apply(x, y, update_state_layer_1, 1);
    big_square_apply(x, y, update_state_layer_2, 2);
    big_square_apply(x, y, update_state_layer_3, 3);

    // apply_updates(layer_2);
    // apply_updates(layer_3);
}

int diagonal_brute(int d) {
    int res = 0;
    for (int i = 1; i <= 2 * m; i++) {
        if (diag[d].t[i] == NORMAL) {
            int l = i, r = i;
            while (diag[d].t[l] == NORMAL) --l;
            while (diag[d].t[r] == NORMAL) ++r;
            if (diag[d].t[l] != BLOCKER || diag[d].t[r] != BLOCKER) res++;
        }
    }

    return res;
}

int ile() {
    int first_step = layer_0.size() - layer_1.size();
    int second_step = layer_1.size() - layer_2.size();
    int from_diagonals = 0;
    for (int i = 1; i <= 2 * (n + m); i++) from_diagonals += diagonal_brute(i);

    cerr << dbg(first_step) << dbg(second_step) << dbg(from_diagonals) << dbg(leaves) << endl;

    return first_step + second_step + from_diagonals + leaves;
    // throw logic_error("unimplemented");
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m >> k >> q;

    for (int i = 1; i <= k; i++) {
        cerr << "______ POINT _________" << dbg(i) << endl;
        int x, y;
        cin >> x >> y;
        flip_cell(x, y);

        print_state(layer_0);
        print_state(layer_1);
        print_state(layer_2);
    }

    cout << ile() << "\n";
    for (int i = 1; i <= q; i++) {
        cerr << "____ QUERY _________" << dbg(i) << endl;
        int x, y;
        cin >> x >> y;
        flip_cell(x, y);

        print_state(layer_0);
        print_state(layer_1);
        print_state(layer_2);
        cout << ile() << "\n";
    }
}