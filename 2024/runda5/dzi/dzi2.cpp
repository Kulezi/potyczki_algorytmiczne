#include "dzilib.h"
#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

#define sim template <class c
#define ris return *this
#define dor > debug& operator<<
#define eni(x) sim > typename enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge {
    c b, e;
};
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
    ~debug() { cerr << endl; }
    eni(!=) cerr << boolalpha << i;
    ris;
} eni(==) ris << range(begin(i), end(i));
}
sim, class b dor(pair<b, c> d) { ris << "(" << d.first << ", " << d.second << ")"; }
sim dor(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it;
    ris << "]";
}
#else
    sim dor(const c&) { ris; }
#endif
}
;

#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define dbg(x) cerr << #x << " = " << x << "\n"
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int T;
ll N;
ll C;
int Q;
constexpr int ALPHA = 26;
using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
vi pi(const basic_string<int>& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

ll match(const basic_string<int>& s, const basic_string<int>& pat) {
	vi p = pi(pat + -1 + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) return i - 2*sz(pat);
	return -1;
}

void subtask2() {
    vector<int> fdiv(N+Q+5, 0);
    fdiv[1] = 1;
    for (int i = 2; i <= N+Q; i++) {
        if (!fdiv[i]) {
            for (int j = i; j <= N + Q; j += i) {
                if (!fdiv[j])
                    fdiv[j] = i;
            }
        }
    }

    basic_string<int> divisor_count(N+Q, 1);
    divisor_count[1] = 1;
    for (int i = 2; i <= N + Q; i++) {
        ll czynnik = fdiv[i];
        int cnt = 0;

        int k = i;
        while (fdiv[k] != 1) {
            if (fdiv[k] == czynnik) cnt++;
            else {
                divisor_count[i] *= (cnt+1);
                cnt = 1;
                czynnik = fdiv[k];
            }

            k /= fdiv[k];
        }

        divisor_count[i] *= (cnt+1);

    }

    int max_moves = Q / T;
    for (int tc = 1; tc <= T; tc++) {
        basic_string<int> pattern;
        for (int i = 0; i < max_moves; i++) pattern.push_back((int)Ask(i));
        Answer(match(divisor_count, pattern));
    }
}

int32_t main() {
    boost;
    T = GetT();
    C = GetC();
    N = GetN();
    Q = GetQ();

    cerr << imie(T) << imie(C) << imie(N) << imie(Q) << endl;

    if (N <= 1000000) {
        subtask2();
        return 0;
    }
    
}

// Pierwsze co mi się przypomina, to że d(n) = iloczyn po krotnosciach czynnikow pierwszych + 1
// Z tego, że n <= 10^14 i d(n) <= 2*sqrt(n) wiemy że d(n) <= 10^7
// Jak rozłożymy d(n) na czynniki pierwsze 
// np. d(n) = 40 = 2 * 2 * 2 * 5
// Z tego możemy wywnioskować ile minimalnie i ile maksymalnie liczb pierwszych ma n w rozkładzie.
// -> jak czynnik w rozkładzie d(n) występuje tylko raz i jest pierwszy, to wiemy, że jest
// dokładnie jeden czynnik w rozkładzie liczby n który miał taką krotność

// Ogółem skoro d(n) <= 10^7 to suma krotności w jego rozkładzie to max ~24
// 

// Obs 1: Jak d(n + x), d(n + 2x), d(n + 3x) ...  są różne od 1 to n jest podzielne przez x.
// Jak długo trzeba tak chodzić? 

// Subtask 1 i 2: 
// x <= 10^6, q <= 5000, Tutaj mogę po prostu puścic najpierw sito i wyliczyć ile dzielników ma każda liczba od 1 do 10^6
// Potem dla każdej liczby pytam się o x, x+1, x+2, ..., x+10 i po prostu szukam tego w sicie.
// Ino nie wiem czy 11 liczb to wystarczający identyfikator ale bym się zdziwił jakby tak nie było.

// niech to nasze x = 2137,
// Pytam o dzielniki:
// d(x) = 2 -> wiem, że liczba pierwsza (nieparzysta)
// d(x+1) = 2 * 2 
// d(x+2) = 2 * 2 * 2
// d(x+3) = 3 * 2 * 2
// d(x+4) = 2
// d(x+5) = 2 * 2 * 2 * 3
// d(x+6) = 2
// d(x+7) = 6 * 2
// d(x+8) = 2 * 2 * 2 * 2
// d(x+9) = 2 * 2 * 2
// d(x+10) = 2 * 2

// Jak znaleźć jakąkolwiek liczbę która ma dokładnie d dzielników? 
// Nie wiem, ale załóżmy, że już znam te liczby i je mam.

// Dzięki czemuś takiemu mogę wnioskować znając d(n + x)
// że n >= smallest(d(n+x))