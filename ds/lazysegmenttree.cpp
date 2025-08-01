template <class S, S (*op)(S, S), S (*e)(), class F, S (*mpg)(F, S), F (*cmp)(F, F), F (*id)()>
struct LazySegmentTree {
    private:
    int n, sz, lg;
    vector<S> d;
    vector<F> lz;

    void build() {
        while (sz < n) {
            sz *= 2, lg++;
        }
        d.resize(sz * 2, e());
        lz.resize(sz * 2, id());
    }

    void update(int k) { d[k] = op(d[k << 1], d[k << 1 | 1]); }

    void all_apply(int k, F f) {
        d[k] = mpg(f, d[k]);
        if (k < sz) { lz[k] = cmp(f, lz[k]); }
    }

    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }

    public:
    LazySegmentTree() {}
    LazySegmentTree(int n_) : n(n_), sz(1), lg(0) { build(); }
    LazySegmentTree(vector<S> &a) : n(a.size()), sz(1), lg(0) {
        build();
        for (int i = 0; i < n; i++) { d[i + sz] = a[i]; }
        for (int i = sz - 1; i >= 1; i--) { update(i); }
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) { push(p >> i); }
        d[p] = x;
        for (int i = 1; i <= lg; i++) { update(p >> i); }
    }

    S get(int p) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) { push(p >> i); }
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) { return e(); };
        l += sz, r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) { push(l >> i); }
            if (((r >> i) << i) != r) { push((r - 1) >> i); }
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) { sml = op(sml, d[l++]); }
            if (r & 1) { smr = op(d[--r], smr); }
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) { push(p >> i); }
        d[p] = mpg(f, d[p]);
        for (int i = 1; i <= lg; i++) { update(p >> i); }
    }
    
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) { return; }
        l += sz, r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) { push(l >> i); }
            if (((r >> i) << i) != r) { push((r - 1) >> i); }
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) { all_apply(l++, f); }
            if (r & 1) { all_apply(--r, f); }
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) { update(l >> i); }
            if (((r >> i) << i) != r) { update((r - 1) >> i); }
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= n);
        assert(g(e()));
        if (l == n) { return n; }
        l += sz;
        for (int i = lg; i >= 1; i--) { push(l >> i); }
        S sm = e();
        do {
            while (l % 2 == 0) { l >>= 1; }
            if (!g(op(sm, d[l]))) {
                while (l < sz) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= n);
        assert(g(e()));
        if (r == 0) { return 0; }
        r += sz;
        for (int i = lg; i >= 1; i--) { push((r - 1) >> i); }
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) { r >>= 1; }
            if (!g(op(d[r], sm))) {
                while (r < sz) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
