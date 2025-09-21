template <class T, class C = int>
struct FenwickTree2D {
    private:
    using P = pair<C, C>;
    int n;
    C MN = numeric_limits<C>::min();
    vector<P> ps;
    vector<vector<P>> yxs;
    vector<atcoder::fenwick_tree<T>> fws;

    void _add(int v, P p, T val) {
        P q = {p.second, p.first};
        int i = lower_bound(yxs[v].begin(), yxs[v].end(), q) - yxs[v].begin();
        fws[v].add(i, val);
    }

    T _sum(int v, C yl, C yr) {
        int il = lower_bound(yxs[v].begin(), yxs[v].end(), P{yl, MN}) - yxs[v].begin();
        int ir = lower_bound(yxs[v].begin(), yxs[v].end(), P{yr, MN}) - yxs[v].begin();
        return fws[v].sum(il, ir);
    }

    public:
    FenwickTree2D() {}

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
            fws.emplace_back(atcoder::fenwick_tree<T>(yxs[i].size()));
        }
    }

    void add(C x, C y, T val) {
        int i = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
        assert(i < n && ps[i].first == x && ps[i].second == y);
        for (i += n; i; i >>= 1) {
            _add(i, P{x, y}, val);
        }
    }

    T sum(C xl, C xr, C yl, C yr) {
        assert(xl <= xr);
        assert(yl <= yr);
        int l = lower_bound(ps.begin(), ps.end(), P{xl, MN}) - ps.begin();
        int r = lower_bound(ps.begin(), ps.end(), P{xr, MN}) - ps.begin();
        l += n;
        r += n;
        T res = 0;
        while (l < r) {
            if (l & 1) {
                res += _sum(l, yl, yr);
                l++;
            }
            if (r & 1) {
                r--;
                res += _sum(r, yl, yr);
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    
    T get(C x, C y) {
        return prod(x, x + 1, y, y + 1);
    }
};
