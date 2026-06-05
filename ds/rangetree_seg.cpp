template <class S, S (*op)(S, S), S (*e)(), class C = int>
struct RangeTree {
    private:
    using P = pair<C, C>;
    int n;
    C MN = numeric_limits<C>::min();
    vector<P> ps;
    vector<vector<P>> yxs;
    vector<atcoder::segtree<S, op, e>> segs;
    
    void set(int v, P p, S val) {
        P q = {p.second, p.first};
        int i = lower_bound(yxs[v].begin(), yxs[v].end(), q) - yxs[v].begin();
        segs[v].set(i, val);
    }
    
    void add(int v, P p, S val) {
        P q = {p.second, p.first};
        int i = lower_bound(yxs[v].begin(), yxs[v].end(), q) - yxs[v].begin();
        segs[v].set(i, op(segs[v].get(i), val));
    }
    
    S prod(int v, C yl, C yr) {
        int il = lower_bound(yxs[v].begin(), yxs[v].end(), P{yl, MN}) - yxs[v].begin();
        int ir = lower_bound(yxs[v].begin(), yxs[v].end(), P{yr, MN}) - yxs[v].begin();
        return segs[v].prod(il, ir);
    }
    
    public:
    RangeTree() {}
    RangeTree(vector<P> &v) {
        for (auto [x, y] : v) {
            add_point(x, y);
        }
        build();
    }
    RangeTree(vector<tuple<C, C, S>> &v) {
        for (auto [x, y, w] : v) {
            add_point(x, y);
        }
        build();
        for (auto [x, y, w] : v) {
            add(x, y, w);
        }
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
            auto l = yxs[i * 2];
            auto r = yxs[i * 2 + 1];
            merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(yxs[i]));
            yxs[i].erase(unique(yxs[i].begin(), yxs[i].end()), yxs[i].end());
        }
        for (int i = 0; i < n * 2; i++) {
            segs.emplace_back(atcoder::segtree<S, op, e>(yxs[i].size()));
        }
    }
    
    void set(C x, C y, S val) {
        int i = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
        assert(i < n && ps[i].first == x && ps[i].second == y);
        for (i += n; i; i >>= 1) {
            set(i, P{x, y}, val);
        }
    }
    
    void add(C x, C y, S val) {
        int i = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
        assert(i < n && ps[i].first == x && ps[i].second == y);
        for (i += n; i; i >>= 1) {
            add(i, P{x, y}, val);
        }
    }
    
    S prod(C xl, C xr, C yl, C yr) {
        assert(xl <= xr);
        assert(yl <= yr);
        int l = lower_bound(ps.begin(), ps.end(), P{xl, MN}) - ps.begin();
        int r = lower_bound(ps.begin(), ps.end(), P{xr, MN}) - ps.begin();
        l += n;
        r += n;
        S res = e();
        while (l < r) {
            if (l & 1) {
                res = op(res, prod(l, yl, yr));
                l++;
            }
            if (r & 1) {
                r--;
                res = op(res, prod(r, yl, yr));
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    
    S get(C x, C y) {
        return prod(x, x + 1, y, y + 1);
    }
};
