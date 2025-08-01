template <class T>
struct PrefixSum2D {
    int h, w;
    vector<vector<T>> s;
    
    PrefixSum2D() {}
    PrefixSum2D(vector<vector<T>> &a) : h(a.size()), w(a[0].size()), s(h + 1, vector<T>(w + 1)) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
            }
        }
    }
    
    // [x1, x2) × [y1, y2)
    T prod(int x1, int x2, int y1, int y2) const {
        assert(0 <= x1 && x1 <= x2 && x2 <= h);
        assert(0 <= y1 && y1 <= y2 && y2 <= w);
        if (x1 == x2 || y1 == y2) {
            return T(0);
        }
        return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
    }
};
