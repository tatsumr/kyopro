template <class T>
struct FunctionalGraph {
  private:
    int n, cnt;
    StaticGraph<T> g;
    vector<int> roots, arrive, id;
    vector<vector<Edge<T>>> cycles;
    vector<vector<int>> dp;

    void next_init() {
        dp.resize(n, vector<int>(60));
        for (int v = 0; v < n; v++) {
            int nv = g[v][0].to;
            dp[v][0] = nv;
        }
        for (int j = 1; j < 60; j++) {
            for (int i = 0; i < n; i++) {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }
    
  public:
    FunctionalGraph() {}
    FunctionalGraph(StaticGraph<T> &g_) : 
    n(g_.size()), cnt(0), g(g_), roots(n, -1), arrive(n), id(n, -1) {
        vector<int> deg(n);
        for (int v = 0; v < n; v++) {
            int nv = g[v][0].to;
            deg[nv]++;
        }
        queue<int> q;
        for (int v = 0; v < n; v++) {
            if (deg[v] == 0) {
                q.emplace(v);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int nv = g[v][0].to;
            deg[nv]--;
            if (deg[nv] == 0) {
                q.emplace(nv);
            }
        }
        for (int v = 0; v < n; v++) {
            if (deg[v] > 0) {
                roots[v] = v;
                arrive[v] = 0;
            }
        }
        for (int v = 0; v < n; v++) {
            if (roots[v] == -1 || id[v] != -1) {
                continue;
            }
            cnt++;
            auto now = g[v][0];
            vector<Edge<T>> es;
            do {
                es.emplace_back(now);
                int nv = now.to;
                now = g[nv][0];
            } while (now.from != v);
            cycles.emplace_back(es);
            for (auto &e : es) {
                int x = e.from, y = e.to;
                id[x] = id[y] = cnt - 1;
            }
        }
        auto dfs = [&](auto dfs, int v) -> void {
            if (roots[v] != -1) return;
            int nv = g[v][0].to;
            dfs(dfs, nv);
            roots[v] = roots[nv];
            arrive[v] = arrive[nv] + 1;
            id[v] = id[nv];
        };
        for (int v = 0; v < n; v++) {
            dfs(dfs, v);
        }
    }
    
    int cc() const { return cnt; }
    
    int root(int v) const {
        assert(0 <= v && v < n);
        return roots[v];
    }
    
    int to_cycle(int v) const {
        assert(0 <= v && v < n);
        return arrive[v];
    }
    
    int len_cycle(int v) const {
        assert(0 <= v && v < n);
        return (int)cycles[id[v]].size();
    }
    
    vector<Edge<T>> cycle(int v) const {
        assert(0 <= v && v < n);
        return cycles[id[v]];
    }
    
    vector<vector<Edge<T>>> all_cycles() const { return cycles; }
    
    int next(int v, long long k) {
        assert(0 <= v && v < n);
        assert(0 <= k && k < (1LL << 60));
        if (dp.size() != n) {
            next_init();
        }
        int res = v;
        for (long long j = 0; j < 60; j++) {
            if (k & (1LL << j)) {
                res = dp[res][j];
            }
        }
        return res;
    }
};
