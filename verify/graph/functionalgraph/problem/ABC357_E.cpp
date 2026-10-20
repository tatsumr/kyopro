// https://atcoder.jp/contests/abc357/tasks/abc357_e
#include <bits/stdc++.h>
using namespace std;

// Functional Graph

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    cin >> N;
    StaticGraph<int> g(N);
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        a--;
        g.add(i, a, 1, i);
    }
    g.build();
    FunctionalGraph<int> fg(g);
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (long long)fg.to_cycle(i);
        ans += (long long)fg.len_cycle(i);
    }
    cout << ans << "\n";
}
