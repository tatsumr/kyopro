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

template <class T, bool multi = false>
struct OfflineSet {
    private:
    int n, sz;
    vector<T> a;
    T none;
    FenwickTree<int> fw;
    
    using P = pair<T, int>;
    
    T kth(int i) {
        int id = fw.lower_bound(i + 1) - 1;
        return a[id];
    }
    
    public:
    OfflineSet() {}
    OfflineSet(vector<T> &a_, T none_) : n(0), a(a_), none(none_) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        sz = a.size();
        fw = FenwickTree<int>(sz);
    }
    
    int count(T x) {
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        if (i == sz || a[i] != x) {
            return 0;
        }
        return fw.sum(i, i + 1);
    }
    
    void insert(T x) {
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        assert(i < sz && a[i] == x);
        if (!multi && fw.sum(i, i + 1) == 1) {
            return;
        }
        n++;
        fw.add(i, 1);
    }
    
    void erase(T x) {
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        if (i < sz && a[i] == x && fw.sum(i, i + 1) > 0) {
            n--;
            fw.add(i, -1);
        }
    }
    
    P ge(T x) {
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        if (i == sz) {
            return P({none, n});
        }
        int cnt = fw.sum(0, i);
        int id = fw.lower_bound(cnt + 1) - 1;
        return (id == sz ? P({none, n}) : P({a[id], cnt}));
    }
    
    
    P gt(T x) {
        int i = upper_bound(a.begin(), a.end(), x) - a.begin();
        if (i == sz) {
            return P({none, n});
        }
        int cnt = fw.sum(0, i);
        int id = fw.lower_bound(cnt + 1) - 1;
        return (id == sz ? P({none, n}) : P({a[id], cnt}));
    }
    
    P le(T x) {
        int i = gt(x).second - 1;
        if (0 <= i && i < n) {
            return P({kth(i), i});
        } else {
            return P({none, n});
        }
    }
    
    P lt(T x) {
        int i = ge(x).second - 1;
        if (0 <= i && i < n) {
            return P({kth(i), i});
        } else {
            return P({none, n});
        }
    }
    
    T operator[](int i) {
        assert(0 <= i && i < n);
        return kth(i);
    }
    
    int size() {
        return n;
    }
    
    bool empty() {
        return (n == 0);
    }
    
    void debug() {
        for (int i = 0; i < n; i++) {
            cerr << kth(i) << " ";
        }
        cerr << "\n";
    }
};
