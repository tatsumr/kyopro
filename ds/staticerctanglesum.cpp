struct StaticRectangleSum {
    vector<int> L, R;
    vector<pair<int, int>> ps;
    WaveletMatrix<int> wm;
    
    StaticRectangleSum() {}

    void add_point(int x, int y) {
        ps.emplace_back(x, y);
    }

    void build() {
        sort(ps.begin(), ps.end());
        for (auto [x, y] : ps) {
            L.emplace_back(x);
            R.emplace_back(y);
        }
        wm = WaveletMatrix(R);
    }

    // [l, r) x [d, u)
    int query(int l, int r, int d, int u) {
        int il = lower_bound(L.begin(), L.end(), l) - L.begin();
        int ir = lower_bound(L.begin(), L.end(), r) - L.begin();
        return wm.range_freq(il, ir, d, u);
    }
};
