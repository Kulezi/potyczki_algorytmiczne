// Rozwiązanie do zadania próbnego 'Mrówki' z Potyczek Algorytmicznych 2024.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 10

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
using namespace std;

constexpr int ALPHA = 26;

struct Block {
    char c;
    int l, r;
};

int32_t main() {
    boost;

    int n;
    cin >> n;

    string s;
    cin >> s;

    deque<Block> blocks = {{s[0], 1, 1}};
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] != s[i + 1]) {
            blocks.emplace_back(s[i + 1], i + 2, i + 2);
        } else
            blocks.back().r++;
    }

    vector<int> da(n + 5, 0);
    while (blocks.size() > 1) {
        if (blocks.front().c == 'L') {
            blocks.pop_front();
            continue;
        }

        if (blocks.front().c == 'P' && blocks[1].c == 'P') {
            blocks[1].l = blocks.front().l;
            blocks.pop_front();
            continue;
        }

        int l1 = blocks.front().l;
        int r1 = blocks.front().r;

        int l2 = blocks[1].l;
        int r2 = blocks[1].r;

        auto add_range = [&](int l, int r, int delta) {
            da[l - 1] += delta;
            da[l] -= delta;
            da[r] -= delta;
            da[r + 1] += delta;
        };

        add_range(l1, r1, 1);
        add_range(r2 - (r1 - l1), r2, 1);

        int W_twos = r2 - l2;
        if (W_twos > 0) {
            da[l1] += 2;
            da[l1 + W_twos] -= 2;

            da[r2 - W_twos] -= 2;
            da[r2] += 2;
        }

        int diff = blocks.front().r - blocks.front().l;
        blocks.front().r = blocks[1].r;
        blocks.front().l = blocks.front().r - diff;
        swap(blocks.front(), blocks[1]);
        blocks.pop_front();
    }

    int sum = 0, d = da[0];
    for (int i = 1; i <= n; i++) {
        sum += d;
        cout << sum << " ";
        d += da[i];
    }

    cout << "\n";
}