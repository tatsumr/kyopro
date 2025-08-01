template <class T>
struct FenwickTree {
    private:
    int n, sz;
    vector<T> data;
    
    T sum(int i) {
        T res = T(0);
        while (i > 0) {
            res += data[i];
            i -= (i & -i);
        }
        return res;
    }
    
    public:
    FenwickTree() {}
    FenwickTree(int n_) : n(n_), data(n + 1, T(0)) {}
    FenwickTree(vector<T> &a) : n(a.size()), data(n + 1, T(0)) {
        for (int i = 0; i < n; i++) {
            add(i, a[i]);
        }
    }
    
    void add(int i, T x) {
        assert(0 <= i && i < n);
        i++;
        while (i <= n) {
            data[i] += x;
            i += (i & -i);
        }
    }
    
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }
    
    int lower_bound(T w) {
        if (w <= 0) {
            return 0;
        }
        int x = 0, r = 1;
        while (r < n) {
            r <<= 1;
        }
        for (int len = r; len > 0; len >>= 1) {
            if (x + len <= n && data[x + len] < w) {
                w -= data[x + len];
                x += len;
            }
        }
        return x + 1;
    }
};
