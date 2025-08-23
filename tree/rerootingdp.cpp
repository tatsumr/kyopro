template <class T, class E, T (*merge)(T, T), T (*add_edge)(Edge<E>, T), T (*add_node)(int, T), T (*id)()>
struct RerootingDP {
    private:
    int n;
    StaticGraph<E> g;
    vector<vector<T>> dp, l, r;
    
    T dfs1(int v, int pv) {
        T res = id();
        for (int i = 0; i < (int)g[v].size(); i++) {
            int nv = g[v][i].to;
            if (nv == pv) {
                continue;
            }
            dp[v][i] = dfs1(nv, v);
            res = merge(add_edge(g[v][i], dp[v][i]), res);
        }
        return add_node(v, res);
    }
    
    void dfs2(int v, int pv, T num) {
        int sz = g[v].size();
        for (int i = 0; i < sz; i++) {
            int nv = g[v][i].to;
            if (nv == pv) {
                dp[v][i] = add_node(pv, num);
            }
        }
        l[v][0] = r[v][sz] = id();
        for (int i = 0; i < sz; i++) {
            l[v][i + 1] = merge(add_edge(g[v][i], dp[v][i]), l[v][i]);
            r[v][sz - i - 1] = merge(add_edge(g[v][sz - i - 1], dp[v][sz - i - 1]), r[v][sz - i]);
        }
        for (int i = 0; i < sz; i++) {
            int nv = g[v][i].to;
            if (nv == pv) {
                continue;
            }
            T nnum = merge(l[v][i], r[v][i + 1]);
            dfs2(nv, v, nnum);
        }
    }
    
    public:
    RerootingDP(StaticGraph<E> &g_) : n(g_.size()), g(g_), dp(n), l(n), r(n) {
        for (int i = 0; i < n; i++) {
            dp[i].resize(g[i].size());
            l[i].resize(g[i].size() + 1);
            r[i].resize(g[i].size() + 1);
        }
        dfs1(0, -1);
        dfs2(0, -1, id());
    }
    
    T get(int v) {
        T res = id();
        for (int i = 0; i < (int)g[v].size(); i++) {
            res = merge(add_edge(g[v][i], dp[v][i]), res);
        }
        return add_node(v, res);
    }
    
    void dump() {
        for (int v = 0; v < n; v++) {
            for (int i = 0; i < (int)g[v].size(); i++) {
                cout << v + 1 << "->" << g[v][i].to + 1 << " : ";
                cout << dp[v][i];
                cout << endl;
            }
        }
    }
};
