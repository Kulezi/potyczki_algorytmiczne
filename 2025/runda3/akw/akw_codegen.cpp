#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgv(x)                        \
    #x << " = [";                      \
    for (auto i : x) cerr << " " << i; \
    cerr << " ] "
using namespace std;

int ans[5005];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;

    for (int a = 1; a <= 5000; a++) {
        cerr << a << "\n";
        int A = a * a;
        for (int b = a; b <= 5000; b++) {
            int B = A + b * b;
            for (int c = 1; c <= 5000; c++) {
                int C = B + c * c;

                int c_sqrt = sqrt(C);
                if (c_sqrt > 5000) break;
                if (c_sqrt * c_sqrt == C) ans[c_sqrt]++;
            }
        }
    }

    cout << "vector<int> odp = {0, ";
    for (int i = 2; i <= 5000; i++) {
        ans[i] += ans[i - 1];
        cout << "," << ans[i];
    }

    cout << "}\n";
}