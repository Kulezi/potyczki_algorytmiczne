// Rozwiązanie do zadania 'Zbieranie klocków [4B]' z Potyczek Algorytmicznych 2025.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((k + q) * log(n))
// Złożoność pamięciowa: O(k + q)
// Punkty: 10

#define NDEBUG
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)

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

constexpr int MAXN = 200'005, INF = 2'000'000'000;

int n, m, k, q;

// Plansza po wykonaniu 0, 1, 2... zdjęć wszystkiego co się da zdjąć naraz w danej chwili.
set<pair<int, int>> layer_0, layer_1, layer_2;

int busy_layer_0(int x, int y) { return layer_0.count({x, y}); }

int busy_layer_1(int x, int y) { return layer_1.count({x, y}); }

int busy_layer_2(int x, int y) { return layer_2.count({x, y}); }

int full_square(int x, int y) { return aggregate_square(x, y, busy_layer_2, +) == 4; }

bool is_in_some_square(int x, int y) { return aggregate_square(x - 1, y - 1, full_square, ||); }

enum {
    NOTHING,
    NORMAL,
    BLOCKER,
};

// https://github.com/bqi343/cp-notebook/blob/292c614b7b83c355b188234966b3b336bc009f16/Implementations/content/graphs%20(12)/Advanced/LCT.h
typedef struct snode* LCT;
struct snode {           //////// VARIABLES
    LCT p, c[2];         // parent, children
    LCT extra;           // extra cycle node for "The Applicant"
    bool flip = 0;       // subtree flipped or not
    pair<int, int> val;  // value in node (diagonal, pos),
    int sz;              // # nodes in current splay tree
    int sub, vsub = 0;   // vsub stores sum of virtual children
    snode(pair<int, int> _val) : val(_val) {
        p = c[0] = c[1] = extra = NULL;
        calc();
    }
    friend int getSz(LCT x) { return x ? x->sz : 0; }
    friend int getSub(LCT x) { return x ? x->sub : 0; }
    void prop() {  // lazy prop
        if (!flip) return;
        swap(c[0], c[1]);
        flip = 0;
        F0R(i, 2) if (c[i]) c[i]->flip ^= 1;
    }
    void calc() {  // recalc vals
        F0R(i, 2) if (c[i]) c[i]->prop();
        sz = 1 + getSz(c[0]) + getSz(c[1]);
        sub = 1 + getSub(c[0]) + getSub(c[1]) + vsub;
    }
    //////// SPLAY TREE OPERATIONS
    int dir() {
        if (!p) return -2;
        F0R(i, 2) if (p->c[i] == this) return i;
        return -1;  // p is path-parent pointer
    }  // -> not in current splay tree
    // test if root of current splay tree
    bool isRoot() { return dir() < 0; }
    friend void setLink(LCT x, LCT y, int d) {
        if (y) y->p = x;
        if (d >= 0) x->c[d] = y;
    }
    void rot() {  // assume p and p->p propagated
        assert(!isRoot());
        int x = dir();
        LCT pa = p;
        setLink(pa->p, this, pa->dir());
        setLink(pa, c[x ^ 1], x);
        setLink(this, pa, x ^ 1);
        pa->calc();
    }
    void splay() {
        while (!isRoot() && !p->isRoot()) {
            p->p->prop(), p->prop(), prop();
            dir() == p->dir() ? p->rot() : rot();
            rot();
        }
        if (!isRoot()) p->prop(), prop(), rot();
        prop();
        calc();
    }
    LCT fbo(int b) {  // find by order
        prop();
        int z = getSz(c[0]);  // of splay tree
        if (b == z) {
            splay();
            return this;
        }
        return b < z ? c[0]->fbo(b) : c[1]->fbo(b - z - 1);
    }
    //////// BASE OPERATIONS
    void access() {  // bring this to top of tree, propagate
        for (LCT v = this, pre = NULL; v; v = v->p) {
            v->splay();  // now switch virtual children
            if (pre) v->vsub -= pre->sub;
            if (v->c[1]) v->vsub += v->c[1]->sub;
            v->c[1] = pre;
            v->calc();
            pre = v;
        }
        splay();
        assert(!c[1]);  // right subtree is empty
    }
    void makeRoot() {
        access();
        flip ^= 1;
        access();
        assert(!c[0] && !c[1]);
    }

    // # nodes above
    int distRoot() {
        access();
        return getSz(c[0]);
    }
    LCT getRoot() {  // get root of LCT component
        access();
        LCT a = this;
        while (a->c[0]) a = a->c[0], a->prop();
        a->access();
        return a;
    }
    LCT getPar(int b) {  // get b-th parent on path to root
        access();
        b = getSz(c[0]) - b;
        assert(b >= 0);
        return fbo(b);
    }  // can also get min, max on path to root, etc
    //////// MODIFICATIONS
    void set(pair<int, int> v) {
        access();
        val = v;
        calc();
    }
    friend void link(LCT parent, LCT child, bool force = 0) {
        if (force)
            child->makeRoot();  // make x par of y
        else {
            child->access();
            assert(!child->c[0]);
        }
        parent->access();
        setLink(child, parent, 0);
        child->calc();
    }
    friend void cut(LCT y) {  // cut y from its parent
        y->access();
        assert(y->c[0]);
        y->c[0]->p = NULL;
        y->c[0] = NULL;
        y->calc();
    }
    friend void cut(LCT x, LCT y) {  // if x, y adj in tree
        x->makeRoot();
        y->access();
        assert(y->c[0] == x && !x->c[0] && !x->c[1]);
        cut(y);
    }
};

// Parent in LCT has smaller position than child.
map<int, pair<LCT, LCT>> diag[4 * MAXN];

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

int leaves, from_diagonals;

// Returns {diagonal_id, pos_in_diagonal}.
pair<int, int> get_diagonal_info(Layer3State l, int x, int y) {
    if (l == DIAGONAL_A) return {x + (y - 1), 2 * (y - 1) + 1};
    if (l == DIAGONAL_B) return {x + y, 2 * y};
    if (l == DIAGONAL_C) return {n + m + (n - (x - (y - 1)) + 1), 2 * (y - 1) + 1};
    assert(l == DIAGONAL_D);
    return {n + m + (n - (x - y) + 1), 2 * y};
}

int is_blocker(int d, int pos) {
    auto it = diag[d].find(pos);
    assert(it != diag[d].end());
    return it->second.first != it->second.second;
}

string debug_node(LCT x) {
    stringstream s;
    int d = x->val.first;
    int pos = x->val.second;
    s << " LCT(" << d << "," << pos << "," << (is_blocker(d, pos) ? "BLOCKER" : "NORMAL") << ") ";
    return s.str();
}

int count_removable(LCT t) {
    LCT root = t->getRoot();
    int len = getSub(root);
    auto [d, pos_root] = root->val;
    int pos_leaf = pos_root + len - 1;

    int blockers = is_blocker(d, pos_root);

    if (pos_leaf != pos_root) blockers += is_blocker(d, pos_leaf);
    if (blockers == 2) return 0;
    return len - blockers;
}

void link_and_update(LCT parent, LCT child) {
    from_diagonals -= count_removable(parent);
    from_diagonals -= count_removable(child);

    link(parent, child);
    from_diagonals += count_removable(parent);
}

void cut_and_update(LCT parent, LCT child) {
    from_diagonals -= count_removable(parent);
    cut(child);
    from_diagonals += count_removable(parent);
    from_diagonals += count_removable(child);
}

void remove_blocker(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);

    assert(diag[d].find(pos) != diag[d].end());
    assert(diag[d][pos].first != diag[d][pos].second);

    auto para = diag[d][pos];
    LCT left = para.first;
    LCT right = para.second;

    // Try to add edge pos -> pos + 1
    auto bigger_pos = diag[d].find(pos + 1);
    if (bigger_pos != diag[d].end()) {
        cut_and_update(right, bigger_pos->second.first);
    }

    // Try to add edge pos-1 -> pos
    auto smaller_pos = diag[d].find(pos - 1);
    if (smaller_pos != diag[d].end()) {
        cut_and_update(smaller_pos->second.second, left);
    }

    diag[d].erase(pos);
}

void insert_blocker(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);

    assert(diag[d].find(pos) == diag[d].end());

    LCT left = new snode({d, pos});
    LCT right = new snode({d, pos});
    diag[d][pos] = {left, right};

    // Try to add edge pos -> pos + 1
    auto bigger_pos = diag[d].find(pos + 1);
    if (bigger_pos != diag[d].end()) {
        link_and_update(right, bigger_pos->second.first);
    }

    // Try to add edge pos-1 -> pos
    auto smaller_pos = diag[d].find(pos - 1);
    if (smaller_pos != diag[d].end()) {
        link_and_update(smaller_pos->second.second, left);
    }
}

void remove_normal(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);

    assert(diag[d].find(pos) != diag[d].end());
    assert(diag[d][pos].first == diag[d][pos].second);

    LCT node = diag[d][pos].first;

    // Try to remove edge pos -> pos + 1
    auto bigger_pos = diag[d].find(pos + 1);
    if (bigger_pos != diag[d].end()) {
        cut_and_update(node, bigger_pos->second.first);
    }

    // Try to remove edge pos-1 -> pos
    auto smaller_pos = diag[d].find(pos - 1);
    if (smaller_pos != diag[d].end()) {
        cut_and_update(smaller_pos->second.second, node);
    }

    diag[d].erase(pos);
    from_diagonals--;
}

void insert_normal(int d, int pos) {
    assert(d >= 1 && d <= 2 * (n + m));
    assert(pos >= 1 && pos <= 2 * m);

    assert(diag[d].find(pos) == diag[d].end());

    from_diagonals++;
    LCT node = new snode({d, pos});
    diag[d][pos] = {node, node};

    // Try to add edge pos -> pos + 1
    auto bigger_pos = diag[d].find(pos + 1);
    if (bigger_pos != diag[d].end()) {
        link_and_update(node, bigger_pos->second.first);
    }

    // Try to add edge pos-1 -> pos
    auto smaller_pos = diag[d].find(pos - 1);
    if (smaller_pos != diag[d].end()) {
        link_and_update(smaller_pos->second.second, node);
    }
}

void update_state_layer_3(int x, int y) {
    Layer3State old_state = get_layer_3_state(x, y);
    Layer3State new_state = recalculate_layer_3_state(x, y);
    if (old_state != new_state) {
        // Undo what was in the structures before.
        if (old_state == LEAF)
            leaves--;
        else if (old_state == IMMOVABLE) {
            for (int diag_type = DIAGONAL_A; diag_type <= DIAGONAL_D; diag_type++) {
                auto [diag_id, diag_pos] = get_diagonal_info((Layer3State)diag_type, x, y);
                remove_blocker(diag_id, diag_pos);
            }
        } else if (old_state != EMPTY) {
            auto [diag_id, diag_pos] = get_diagonal_info(old_state, x, y);
            remove_normal(diag_id, diag_pos);
        }

        // And redo with new state.
        if (new_state == LEAF)
            leaves++;
        else if (new_state == IMMOVABLE) {
            for (int diag_type = DIAGONAL_A; diag_type <= DIAGONAL_D; diag_type++) {
                auto [diag_id, diag_pos] = get_diagonal_info((Layer3State)diag_type, x, y);
                insert_blocker(diag_id, diag_pos);
            }
        } else if (new_state != EMPTY) {
            auto [diag_id, diag_pos] = get_diagonal_info(new_state, x, y);
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
    }
}

void update_state_layer_1(int x, int y) {
    if (!in_board(x, y)) return;

    int old_state = busy_layer_1(x, y);
    int new_state =
        busy_layer_0(x, y) && sum_hor(x, y, busy_layer_0) > 0 && sum_vert(x, y, busy_layer_0) > 0;
    if (old_state != new_state) {
        flip(layer_1, x, y);
    }
}

void flip_cell(int x, int y) {
    assert(in_board(x, y));
    // Update layer_0.
    flip(layer_0, x, y);

    // Update rest of layers in order.
    big_square_apply(x, y, update_state_layer_1, 1);
    big_square_apply(x, y, update_state_layer_2, 2);
    big_square_apply(x, y, update_state_layer_3, 3);
}

int ile() {
    int first_step = layer_0.size() - layer_1.size();
    int second_step = layer_1.size() - layer_2.size();

    return first_step + second_step + from_diagonals + leaves;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> q;

    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        flip_cell(x, y);
    }

    cout << ile() << "\n";
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        flip_cell(x, y);

        cout << ile() << "\n";
    }
}