template <class T = long long>
struct WeightedUnionFind {
    private:
    int n;
    vector<int> par;
    vector<T> diff_weight;
    
    public:
    WeightedUnionFind() {}
    WeightedUnionFind(int n_) : n(n_), par(n, -1), diff_weight(n, T(0)) {}
    
    int leader(int x) {
        assert(0 <= x && x < n);
        if (par[x] < 0) {
            return x;
        } else {
            int r = leader(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }
    
    T weight(int x) {
        assert(0 <= x && x < n);
        leader(x);
        return diff_weight[x];
    }
    
    T diff(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        return weight(y) - weight(x);
    }
    
    int merge(int x, int y, T w) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        w += weight(x);
        w -= weight(y);
        x = leader(x);
        y = leader(y);
        if (x == y) {
            return x;
        }
        if (-par[x] < -par[y]) {
            swap(x, y);
            w *= T(-1);
        }
        par[x] += par[y];
        par[y] = x;
        diff_weight[y] = w;
        return x;
    }
    
    bool same(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        return leader(x) == leader(y);
    }
    
    int size(int x) {
        assert(0 <= x && x < n);
        return -par[leader(x)];
    }
    
    vector<vector<int>> groups() {
        vector<vector<int>> buf(n);
        for (int i = 0; i < n; i++) {
            buf[leader(i)].emplace_back(i);
        }
        vector<vector<int>> res;
        for (int i = 0; i < n; i++) {
            if (buf[i].size() > 0) {
                res.emplace_back(buf[i]);
            }
        }
        return res;
    }
};
