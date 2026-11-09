template <class S, S (*op)(S, S), S (*e)()>
struct SparseTable {
    int N, K;
    vector<vector<S>> table;

    SparseTable() {}
    SparseTable(const vector<S>& A) : N(A.size()), K(0) {
        while (1 << (K + 1) <= N) ++K;

        table.resize(K + 1);
        table[0] = A;
        for (int k = 0; k < K; ++k) {
            int m = N - (1 << (k + 1)) + 1;
            table[k + 1].resize(m);
            for (int i = 0; i < m; ++i) {
                table[k + 1][i] = op(table[k][i], table[k][i + (1 << k)]);
            }
        }
    }

    S prod(int L, int R) {
        assert(0 <= L && L <= R && R <= N);
        if (L == R) return e();
        int k = 31 - __builtin_clz(R - L);
        return op(table[k][L], table[k][R - (1 << k)]);
    }
};
