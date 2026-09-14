#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for(int i = (a); i < (b); i++)
#define rep(i, n) For(i, 0, n)
#define SZ(v) ((int)(v).size())

#include <atcoder/dsu>
#include <atcoder/scc>

int main() {
    // 入力
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    rep(i, N) {
        cin >> A[i];
        A[i]--;
    }

    // 準備
    atcoder::dsu uf(N);
    rep(i, N) {
        uf.merge(i, A[i]);
    }
    
    atcoder::scc_graph g(N);
    rep(i, N) {
        g.add_edge(i, A[i]);
    }
    vector<int> id(N);
    vector<bool> is_cycle(N, false);
    auto scc = g.scc();
    rep(i, SZ(scc)) {
        auto& vs = scc[i];
        for (int v : vs) id[v] = i;
        if (SZ(vs) >= 2) {
            for (int v : vs) is_cycle[v] = true;
        } else {
            int v = vs[0];
            if (A[v] == v) is_cycle[v] = true;
        }
    }

    vector<int> root(N), dist(N, 0);
    rep(i, N) {
        int now = i;
        while (!is_cycle[now]) {
            now = A[now], dist[i]++;
        }
        root[i] = now;
    }

    // cc
    cout << SZ(uf.groups()) << "\n";

    // root
    rep(i, N) {
        cout << root[i] + 1;
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // to_cycle
    rep(i, N) {
        cout << dist[i];
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // len_cycle
    rep(i, N) {
        cout << SZ(scc[id[root[i]]]);
        if (i < N - 1) cout << " ";
    }
    cout << "\n";

    // cycle

    
    // next
    rep(v, N) {
        rep(k, K) {
            int now = v;
            rep(_, k) {
                now = A[now];
            }
            cout << now + 1;
            if (k < K - 1) cout << " ";
        }
        cout << "\n";
    }

}
