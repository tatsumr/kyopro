template <class T>
struct HLD {
    private:
    int n;
    vector<vector<int>> g;
    vector<int> par, sub, dep, in, out, head;
    
    void build() {
        auto dfs1 = [&](auto dfs1, int v) -> int {
            sub[v] = 1;
            for (int &nv : g[v]) {
                sub[v] += dfs1(dfs1, nv);
                if (sub[nv] > sub[g[v][0]]) {
                    swap(nv, g[v][0]);
                }
            }
            return sub[v];
        };
        dfs1(dfs1, 0);
        int t = 0;
        auto dfs2 = [&](auto dfs2, int v) -> void {
            in[v] = t;
            t++;
            for (int nv : g[v]) {
                dep[nv] = dep[v] + 1;
                head[nv] = (g[v][0] == nv ? head[v] : nv);
                dfs2(dfs2, nv);
            }
            out[v] = t;
        };
        dfs2(dfs2, 0);
    }
    
    vector<pair<int, int>> ascend(int u, int v) {
        vector<pair<int, int>> res;
        while (head[u] != head[v]) {
            res.emplace_back(in[u], in[head[u]]);
            u = par[head[u]];
        }
        if (u != v) {
            res.emplace_back(in[u], in[v] + 1);
        }
        return res;
    }
    
    vector<pair<int, int>> descend(int u, int v) {
        if (u == v) {
            return {};
        }
        if (head[u] == head[v]) {
            return {{in[u] + 1, in[v]}};
        }
        vector<pair<int, int>> res = descend(u, par[head[v]]);
        res.emplace_back(in[head[v]], in[v]);
        return res;
    }
    
    public:
    HLD() {}
    HLD(StaticGraph<T> &g_) : n(g_.size()), g(n), par(n, -1), sub(n), dep(n, 0), in(n), out(n), head(n) {
        auto init = [&](auto init, int v, int pv) -> void {
            par[v] = pv;
            for (auto &e : g_[v]) {
                int nv = e.to;
                if (nv == pv) {
                    continue;
                }
                g[v].emplace_back(nv);
                init(init, nv, v);
            }
        };
        init(init, 0, -1);
        build();
    }
    
    int idx(int v) {
        assert(0 <= v && v < n);
        return in[v];
    }
    
    int lca(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        while (head[u] != head[v]) {
            if (dep[head[u]] <= dep[head[v]]) {
                v = par[head[v]];
            } else {
                u = par[head[u]];
            }
        }
        return (dep[u] <= dep[v] ? u : v);
    }
    
    template <class F>
    void path_query_commutative(int u, int v, bool vertex, const F &f) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        int l = lca(u, v);
        for (auto &&[a, b] : ascend(u, l)) {
            int s = a + 1, t = b;
            s > t ? f(t, s) : f(s, t);
        }
        if (vertex) {
            f(in[l], in[l] + 1);
        }
        for (auto &&[a, b] : descend(l, v)) {
            int s = a, t = b + 1;
            s > t ? f(t, s) : f(s, t);
        }
    }
    
    template <class F>
    void path_query_noncommutative(int u, int v, bool vertex, const F &f) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        int l = lca(u, v);
        for (auto &&[a, b] : ascend(u, l)) {
            f(a + 1, b);
        }
        if (vertex) {
            f(in[l], in[l] + 1);
        }
        for (auto &&[a, b] : descend(l, v)) {
            f(a, b + 1);
        }
    }
    
    template <class F>
    void subtree_query(int v, bool vertex, const F &f) {
        assert(0 <= v && v < n);
        f(in[v] + int(!vertex), out[v]);
    }
    
    int dist(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        return dep[u] + dep[v] - dep[lca(u, v)] * 2;
    }
};
