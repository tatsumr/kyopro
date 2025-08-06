struct UndoableUnionFind {
    private:
    int n;
    vector<int> par;
    stack<pair<int, int>> history;
    
    public:
    UndoableUnionFind() {}
    UndoableUnionFind(int n_) : n(n_), par(n, -1) {}
    
    int merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int x = leader(a), y = leader(b);
        history.emplace(x, par[x]);
        history.emplace(y, par[y]);
        if (x == y) {
            return x;
        }
        if (-par[x] < -par[y]) {
            swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
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
        return leader(par[a]);
    }
    
    int size(int a) {
        assert(0 <= a && a < n);
        return -par[leader(a)];
    }
    
    void undo() {
        if (history.empty()) {
            return;
        }
        par[history.top().first] = history.top().second;
        history.pop();
        par[history.top().first] = history.top().second;
        history.pop();
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
