template <class S, S (*op)(S, S), bool inv>
struct UnionFindSemigroup {
    private:
    int n;
    vector<int> par;
    vector<S> d, acc;
    
    public:
    UnionFindSemigroup() {}
    UnionFindSemigroup(vector<S> &d_) : n(d_.size()), par(n, -1), d(d_), acc(d_) {}
    
    int merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int x = leader(a), y = leader(b);
        if (x == y) {
            return x;
        }
        if (-par[x] < -par[y]) {
            swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
        acc[x] = op(acc[x], acc[y]);
        return x;
    }
    
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return leader(a) == leader(b);
    }
    
    int leader(int a) {
        assert(0 <= a && a < n);
        if (par[a] < 0) {
            return a;
        }
        return par[a] = leader(par[a]);
    }
    
    int size(int a) {
        assert(0 <= a && a < n);
        return -par[leader(a)];
    }
    
    S prod(int a) {
        assert(0 <= a && a < n);
        return acc[leader(a)];
    }
    
    S get(int a) {
        assert(0 <= a && a < n);
        return d[a];
    }
    
    template <class F>
    void set(int a, S x, F &inv_op) {
        assert(0 <= a && a < n);
        assert(inv);
        int r = leader(a);
        S px = get(a);
        acc[r] = inv_op(acc[r], px);
        d[a] = x;
        acc[r] = op(acc[r], x);
    }
    
    void set(int a, S x) {
        auto inv_op = [&](S rx, S x) {
            return rx - x;
        };
        set(a, x, inv_op);
    }
    
    vector<vector<int>> groups() {
        vector<vector<int>> member(n);
        for (int i = 0; i < n; i++) {
            member[leader(i)].emplace_back(i);
        }
        vector<vector<int>> res;
        for (int i = 0; i < n; i++) {
            if (member[i].size() > 0) {
                res.emplace_back(member[i]);
            }
        }
        return res;
    }
};
