#include "dzilib.h"
#include <cstdio>
#include <cstdlib>
#include <random>
#include <chrono>
#include <iostream>

static int T = 1;
static long long N = 2137;
static int Q = 1000;
static long long C = 1900;

static long long hidden_x = 0;

static int queries = 0;
static int num_testcase = 0;
namespace {
int R(int a, int b) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(a, b)(rng);
}
}
void start_testcase() {
        num_testcase++;
        if (num_testcase <= T) {
                hidden_x = R(1, N);
                std::cerr << hidden_x << "\n";
        } else {
                hidden_x = -1;
                printf("Poprawnie rozwiązano w %d zapytań\n", queries);
        }
}

void init() {
        if (hidden_x != 0) {
                return;
        }
        if (scanf("%d%lld%d%lld", &T, &N, &Q, &C) != 4) {
                printf("Błąd wczytywania!\n");
                exit(0);
        }
        start_testcase();
}

int GetT() {
        init();
        return T;
}

long long GetN() {
        init();
        return N;
}

int GetQ() {
        init();
        return Q;
}

long long GetC() {
        init();
        return C;
}

long long Ask(long long y) {
        init();
        if (hidden_x == -1) {
                printf("ERROR: wywołanie funkcji Ask po zakończeniu wszystkich przypadków testowych\n");
                exit(0);
        }
        if (y < 0 || y > C) {
                printf("ERROR: niepoprawny argument funkcji Ask: %lld\n", y);
                exit(0);
        }
        queries++;
        if (queries > Q) {
                printf("ERROR: przekroczono limit zapytań\n");
                exit(0);
        }
        long long divisors = 0;
        for (long long i = 1; i <= hidden_x + y; i++)
                if ((hidden_x + y) % i == 0)
                        divisors++;
        return divisors;
}

void Answer(long long z) {
        init();
        if (hidden_x == -1) {
                printf("ERROR: wywołanie funkcji Answer po zakończeniu wszystkich przypadków testowych\n");
                exit(0);
        }
        if (z != hidden_x) {
                printf("ERROR: ukryty x wynosił %lld, a udzielona odpowiedź to %lld\n", hidden_x, z);
                exit(0);
        }
        start_testcase();
}