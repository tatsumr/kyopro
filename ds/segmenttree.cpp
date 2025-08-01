template <class S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
    private:
    int n, sz, lg;
    vector<S> d;

    void build() {
        while (sz < n) {
            sz *= 2, lg++;
        }
        d.resize(sz * 2, e());
    }

    void update(int k) {
        d[k] = op(d[k << 1], d[k << 1 | 1]);
    }

    public:
    SegmentTree() {}
    SegmentTree(int n_) : n(n_), sz(1), lg(0) { build(); }
    SegmentTree(vector<S> &a) : n(a.size()), sz(1), lg(0) {
        build();
        for (int i = 0; i < n; i++) { d[i + sz] = a[i]; }
        for (int i = sz - 1; i >= 1; i--) { update(i); }
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += sz;
        d[p] = x;
        for (int i = 1; i <= lg; i++) {
            update(p >> i);
        }
    }

    S get(int p) const {
        assert(0 <= p && p < n);
        return d[p + sz];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        S sml = e(), smr = e();
        l += sz, r += sz;
        while (l < r) {
            if (l & 1) { sml = op(sml, d[l++]); }
            if (r & 1) { smr = op(d[--r], smr); }
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)>
    int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= n);
        assert(f(e()));
        if (l == n) { return n; }
        l += sz;
        S sm = e();
        do {
            while (l % 2 == 0) { l >>= 1; }
            if (!f(op(sm, d[l]))) {
                while (l < sz) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - sz;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= n);
        assert(f(e()));
        if (r == 0) { return 0; }
        r += sz;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) { r >>= 1; }
            if (!f(op(d[r], sm))) {
                while (r < sz) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - sz;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
