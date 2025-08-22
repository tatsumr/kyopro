template <class F, F (*composition)(F, F), F (*id)()>
struct DualSegmentTree {
    private:
    int n;
    vector<F> lz;
    
    public:
    DualSegmentTree() {}
    DualSegmentTree(int n_) : n(n_), lz(n << 1, id()) {}
    DualSegmentTree(vector<F> &v) : n(v.size()), lz(n << 1) {
        for (int i = 0; i < n; i++) { lz[i + n] = v[i]; }
    }
    
    F get(int p) const {
        assert(0 <= p && p < n);
        F sum = id();
        p += n;
        while (p) {
            sum = composition(sum, lz[p]);
            p >>= 1;
        }
        return sum;
    }
    
    F operator[](int p) const { return get(p); }
    
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return;
        }
        if (l + n == r) {
            lz[1] = composition(lz[1], f);
            return;
        }
        l += n, r += n;
        while (l < r) {
            if (l & 1) {
                lz[l] = composition(lz[l], f);
                l++;
            }
            if (r & 1) {
                r--;
                lz[r] = composition(lz[r], f);
            }
            l >>= 1, r >>= 1;
        }
    }
    
    void apply(int p, F f) { apply(p, p + 1, f); }
};

template <class F, F (*composition)(F, F), F (*id)(), class C = int>
struct DualSegmentTree2D {
    private:
    using P = pair<C, C>;
    int n;
    C mn = numeric_limits<C>::min();
    vector<P> ps;
    vector<vector<P>> yxs;
    vector<DualSegmentTree<F, composition, id>> segs;
    
    F get(int i, P p) const {
        P q = {p.second, p.first};
        int j = lower_bound(yxs[i].begin(), yxs[i].end(), q) - yxs[i].begin();
        return segs[i].get(j);
    }
    
    void apply(int i, C yl, C yr, F f) {
        int l = lower_bound(yxs[i].begin(), yxs[i].end(), P{yl, mn}) - yxs[i].begin();
        int r = lower_bound(yxs[i].begin(), yxs[i].end(), P{yr, mn}) - yxs[i].begin();
        segs[i].apply(l, r, f);
    }
    
    public:
    DualSegmentTree2D() {}
    DualSegmentTree2D(vector<P> &v) {
        for (auto [x, y] : v) {
            add_point(x, y);
        }
        build();
    }
    
    void add_point(C x, C y) {
        ps.emplace_back(x, y);
    }
    
    void build() {
        sort(ps.begin(), ps.end());
        ps.erase(unique(ps.begin(), ps.end()), ps.end());
        n = ps.size();
        yxs.resize(n * 2);
        for (int i = 0; i < n; i++) {
            yxs[i + n].emplace_back(ps[i].second, ps[i].first);
        }
        for (int i = n - 1; i > 0; i--) {
            auto &l = yxs[i << 1];
            auto &r = yxs[(i << 1) | 1];
            merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(yxs[i]));
            yxs[i].erase(unique(yxs[i].begin(), yxs[i].end()), yxs[i].end());
        }
        for (int i = 0; i < n * 2; i++) {
            segs.emplace_back(DualSegmentTree<F, composition, id>(yxs[i].size()));
        }
    }
    
    F get(C x, C y) const {
        int i = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
        assert(i < n && ps[i].first == x && ps[i].second == y);
        i += n;
        F sum = id();
        while (i) {
            sum = composition(sum, get(i, P{x, y}));
            i >>= 1;
        }
        return sum;
    }
    
    void apply(C xl, C xr, C yl, C yr, F f) {
        assert(xl <= xr);
        assert(yl <= yr);
        int l = lower_bound(ps.begin(), ps.end(), P{xl, mn}) - ps.begin();
        int r = lower_bound(ps.begin(), ps.end(), P{xr, mn}) - ps.begin();
        l += n, r += n;
        while (l < r) {
            if (l & 1) {
                apply(l, yl, yr, f);
                l++;
            }
            if (r & 1) {
                r--;
                apply(r, yl, yr, f);
            }
            l >>= 1, r >>= 1;
        }
    }
};
