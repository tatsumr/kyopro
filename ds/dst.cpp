template <class T, T (*op)(T, T), T (*e)()>
struct DST {
    private:
    int n, h = 1, w;
    vector<vector<T>> table;
    vector<int> get;
    
    public:
    DST() {}
    DST(vector<T> &v) : n(v.size()) {
        while ((1 << h) < n) {
            h++;
        }
        int w = (1 << h);
        table.assign(h, vector<T>(w, e()));
        for (int i = 0; i < h; i++) {
            int len = (1 << (h - i - 1));
            for (int pos = (1 << (h - i - 1)) - 1; pos < w; pos += (len << 1)) {
                for (int j = pos; j >= pos - len + 1; j--) {
                    table[i][j] = (j == pos ? v[j] : op(v[j], table[i][j + 1]));
                }
                for (int j = pos + 1; j <= pos + len; j++) {
                    table[i][j] = (j == pos + 1 ? v[j] : op(table[i][j - 1], v[j]));
                }
            }
        }
        get.resize(w);
        for (int i = 1; i < w; i++) {
            get[i] = __builtin_clz(i) - (32 - h);
        }
    }
    
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return e();
        }
        if (r - l == 1) {
            return table[h - 1][l];
        }
        int i = get[l ^ (r - 1)];
        return op(table[i][l], table[i][r - 1]);
    }
};
