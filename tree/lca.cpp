struct LCA {
    int N, K;
    vector<int> depth, in;
    vector<vector<int>> table;

    LCA() {}
    LCA(vector<vector<int>>& g, int root = 0) : N(g.size()), K(0), depth(N), in(N) {
        int M = 2 * N - 1;
        while (1 << (K + 1) <= M) K++;
        table.resize(K + 1);
        for (int k = 0; k <= K; ++k) {
            int sz = M - (1 << k) + 1;
            table[k].resize(sz);
        }
        
        int pos = 0;
        auto dfs = [&](auto dfs, int v, int d, int pv) -> void {
            depth[v] = d;
            in[v] = pos;
            table[0][pos++] = v;
            for (int nv : g[v]) {
                if (nv == pv) continue;
                dfs(dfs, nv, d + 1, v);
                table[0][pos++] = v;
            }
        };
        dfs(dfs, root, 0, -1);

        for (int k = 0; k < K; ++k) {
            for (int i = 0; i < table[k + 1].size(); ++i) {
                int x = table[k][i], y = table[k][i + (1 << k)];
                table[k + 1][i] = (depth[x] < depth[y] ? x : y);
            }
        }
    }

    int query(int u, int v) const {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        int L = in[u], R = in[v];
        if (L > R) swap(L, R);
        R++;
        int k = 31 - __builtin_clz(R - L);
        int x = table[k][L], y = table[k][R - (1 << k)];
        return (depth[x] < depth[y] ? x : y);
    }
};
