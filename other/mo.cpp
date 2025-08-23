struct Mo {
    private:
    int n;
    vector<pair<int, int>> qs;
    
    public:
    Mo() {}
    Mo(int n_) : n(n_) {}
    
    void insert(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        qs.emplace_back(l, r);
    }
    
    template <class AL, class AR, class DL, class DR, class OUT>
    void build(const AL &add_left, const AR &add_right, const DL &del_left, const DR &del_right, const OUT &out) {
        int q = qs.size();
        int b = max<int>(1, 1.0 * n / max<double>(1.0, sqrt(q * 2.0 / 3.0)));
        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j) {
            if (qs[i].first / b != qs[j].first / b) {
                return qs[i].first < qs[j].first;
            }
            return qs[i].second < qs[j].second;
        });
        int l = 0, r = 0;
        for (int i : ord) {
            while (l > qs[i].first) {
                add_left(--l);
            }
            while (r < qs[i].second) {
                add_right(r++);
            }
            while (l < qs[i].first) {
                del_left(l++);
            }
            while (r > qs[i].second) {
                del_right(--r);
            }
            out(i);
        }
    }
    
    template <class A, class D, class O>
    void build(const A &add, const D &del, const O &out) {
        build(add, add, del, del, out);
    }
};
