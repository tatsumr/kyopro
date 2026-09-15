// Static Graph ではなく配列から渡すタイプ
// 時空間省エネできる
// cycle, all_cycles は頂点列を返す
// 閉路をなす頂点列が不要な時は cycles への挿入を消すとさらに速くなるかも？

struct FunctionalGraph {
  private:
    int n, cnt;
    vector<int> a, roots, arrive, id;
    vector<vector<int>> cycles, dp;

    void next_init() {
        dp.resize(n, vector<int>(60));
        for (int v = 0; v < n; v++) {
            int nv = a[v];
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
    FunctionalGraph(vector<int> &_a) :
    n(_a.size()), cnt(0), a(_a), roots(n, -1), arrive(n), id(n, -1) {
        vector<int> deg(n);
        for (int v = 0; v < n; v++) {
            deg[a[v]]++;
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
            int nv = a[v];
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
            cycles.emplace_back(vector<int>{});
            int now = v;
            vector<int> vs;
            do {
                cycles[cnt].emplace_back(now);
                id[now] = cnt;
                now = a[now];
            } while (now != v);
            cnt++;
        }
        auto dfs = [&](auto dfs, int v) -> void {
            if (roots[v] != -1) return;
            int nv = a[v];
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
    
    vector<int> cycle(int v) const {
        assert(0 <= v && v < n);
        return cycles[id[v]];
    }
    
    vector<vector<int>> all_cycles() const { return cycles; }
    
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
