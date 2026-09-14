#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for(int i = (a); i < (b); i++)
#define rep(i, n) For(i, 0, n)
#define SZ(v) ((int)(v).size())

// (Edge, Static Graph)
// Functional Graph

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    rep(i, N) {
        cin >> A[i];
        A[i]--;
    }

    StaticGraph<int> g(N);
    rep(i, N) {
        g.add(i, A[i], 1, i);
    }
    g.build();
    FunctionalGraph<int> fg(g);

    // cc
    cout << fg.cc() << "\n";

    // root
    rep(i, N) {
        cout << fg.root(i) + 1;
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // to_cycle
    rep(i, N) {
        cout << fg.to_cycle(i);
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // len_cycle
    rep(i, N) {
        cout << fg.len_cycle(i);
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // cycle
    rep(i, N) {
        auto c = fg.cycle(i);
        bool ok = true;
        if (SZ(c) != fg.len_cycle(i)) {
            ok = false;
        }
        rep(x, SZ(c)) {
            int y = (x + 1) % SZ(c);
            if (c[x].to != c[y].from) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "cycle (" << i + 1 << ")\n";
            for (auto& e : c) {
                cout << e.from + 1 << " -> " << e.to + 1 << "\n";
            }
        }
    }

    // next
    rep(v, N) {
        rep(k, K) {
            cout << fg.next(v, k) + 1;
            if (k < K - 1) cout << " ";
        }
        cout << "\n";
    }
}
