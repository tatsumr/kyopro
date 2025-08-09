template <class T>
struct FunctionalGraph {
    private:
    int n, cnt;
    StaticGraph<T> g, gg;
    vector<int> roots, arrive, len, id;
    vector<vector<Edge<T>>> cycles;
    vector<vector<int>> dp;
    
    public:
    FunctionalGraph() {}
    FunctionalGraph(StaticGraph<T> &g_) : 
    n(g_.size()), cnt(0), g(g_), gg(n), roots(n, -1), arrive(n, -1), len(n, -1), id(n) {
        for (int v = 0; v < n; v++) {
            int nv = g[v][0].to;
            T c = g[v][0].cost;
            int i = g[v][0].idx;
            gg.add(nv, nv, v, c, i);
        }
        gg.build();
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
            if (roots[v] == -1 || len[v] != -1) {
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
                len[x] = len[y] = es.size();
                id[x] = id[y] = cnt - 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (roots[i] == -1) {
                continue;
            }
            queue<int> q;
            q.emplace(i);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto &e : gg[v]) {
                    int nv = e.to;
                    if (roots[nv] != -1) {
                        continue;
                    }
                    roots[nv] = roots[v];
                    arrive[nv] = arrive[v] + 1;
                    len[nv] = len[v];
                    id[nv] = id[v];
                    q.emplace(nv);
                }
            }
        }
    }
    
    int cc() const {
        return cnt;
    }
    
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
        return len[v];
    }
    
    vector<Edge<T>> cycle(int v) const {
        assert(0 <= v && v < n);
        return cycles[id[v]];
    }
    
    vector<vector<Edge<T>>> all_cycles() const {
        return cycles;
    }
    
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
    
    int next(int v, long long k) {
        assert(0 <= v && v < n);
        assert(0 <= k && k <= 1e18);
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
