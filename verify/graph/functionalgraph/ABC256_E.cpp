// https://atcoder.jp/contests/abc256/tasks/abc256_e
#include <bits/stdc++.h>
using namespace std;

// Functional Graph

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> X(N);
    vector<long long> C(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        X[i]--;
    }
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    StaticGraph<long long> g(N);
    for (int i = 0; i < N; i++) {
        g.add(i, X[i], C[i], i);
    }
    g.build();
    FunctionalGraph<long long> fg(g);
    auto cs = fg.all_cycles();
    long long ans = 0;
    for (auto& es : cs) {
        long long mn = LLONG_MAX;
        for (auto& e : es) {
            mn = min(mn, e.cost);
        }
        ans += mn;
    }
    cout << ans << "\n";
}
