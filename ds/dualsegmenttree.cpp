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
