struct OfflineDynamicConnectivity {
    using edge = pair<int, int>;
    int n, q, sz;
    vector<vector<edge>> seg;
    UndoableUnionFind uf;
    map<edge, int> cnt, appear;
    vector<pair<edge, pair<int, int>>> times;
    
    OfflineDynamicConnectivity() {}
    OfflineDynamicConnectivity(int n_, int q_) : n(n_), q(q_), sz(1), uf(n) {
        while (sz < q) {
            sz *= 2;
        }
        seg.resize(sz * 2);
    }
    
    void insert(int t, int u, int v) {
        assert(1 <= t);
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u > v) {
            swap(u, v);
        }
        edge e = {u, v};
        if (cnt[e] == 0) {
            cnt[e]++;
            appear[e] = t;
        }
    }
    
    void erase(int t, int u, int v) {
        assert(1 <= t);
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u > v) {
            swap(u, v);
        }
        edge e = {u, v};
        if (cnt[e] == 1) {
            cnt[e]--;
            pair<int, int> lr = {appear[e], t};
            times.emplace_back(e, lr);
        }
    }
    
    void add(edge e, int l, int r) {
        l += sz;
        r += sz;
        while (l < r) {
            if (l & 1) {
                seg[l].emplace_back(e);
                l++;
            }
            if (r & 1) {
                r--;
                seg[r].emplace_back(e);
            }
            l >>= 1;
            r >>= 1;
        }
    }
    
    void build() {
        for (auto [e, x] : cnt) {
            if (x > 0) {
                pair<int, int> lr = {appear[e], q};
                times.emplace_back(e, lr);
            }
        }
        for (auto [e, lr] : times) {
            auto [l, r] = lr;
            add(e, l, r);
        }
    }
    
    void run(function<void(int)> f, int i = 1) {
        for (auto e : seg[i]) {
            auto [u, v] = e;
            uf.merge(u, v);
        }
        if (0 <= i - sz) {
            if (i - sz < q) {
                f(i - sz);
            }
        } else {
            run(f, i * 2);
            run(f, i * 2 + 1);
        }
        for (int j = 0; j < (int)seg[i].size(); j++) {
            uf.undo();
        }
    }
};
