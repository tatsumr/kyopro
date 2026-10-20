// https://atcoder.jp/contests/abc377/tasks/abc377_e
#include <bits/stdc++.h>
using namespace std;

// Functional Graph

template <class T>
T modpow(T a, T b, T mod) {
    T res = 1;
    while (b) {
        if (b & 1) { res = (res * a) % mod; }
        a = (a * a) % mod; b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    long long K;
    cin >> N >> K;
    StaticGraph<int> g(N);
    for (int i = 0; i < N; i++) {
        int P;
        cin >> P;
        P--;
        g.add(i, P, 1, i);
    }
    g.build();
    FunctionalGraph<int> fg(g);
    for (int i = 0; i < N; i++) {
        long long len = fg.len_cycle(i);
        long long dist = modpow<long long>(2LL, K, len);
        cout << fg.next(i, dist) + 1 << " ";
    }
    cout << "\n";
}
