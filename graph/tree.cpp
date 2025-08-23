template <class T>
struct Tree {
    private:
    int n;
    StaticGraph<T> g;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<T> distance;
    int root;
    
    void build() {
        queue<int> q;
        depth[root] = 0;
        distance[root] = 0LL;
        q.push(root);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : g[v]) {
                int nv = e.to;
                T d = e.cost;
                if (depth[nv] == -1) {
                    depth[nv] = depth[v] + 1;
                    distance[nv] = distance[v] + d;
                    parent[nv][0] = v;
                    q.push(nv);
                }
            }
        }
        for (int j = 1; j < 30; j++) {
            for (int i = 0; i < n; i++) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
    
    public:
    Tree() {}
    Tree(StaticGraph<T> &g_, int root_ = 0) :n(g_.size()), g(g_), parent(n, vector<int>(30)), depth(n, -1), distance(n, -1LL), root(root_) {
        build();
    }
    
    int lca(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (dep(u) < dep(v)) {
            swap(u, v);
        }
        u = la(u, dep(u) - dep(v));
        if (u == v) {
            return u;
        }
        for (int j = 29; j >= 0; j--) {
            if (parent[u][j] != parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        return par(u);
    }
    
    int la(int v, int k) const {
        assert(0 <= v && v < n);
        int res = v;
        for (int j = 0; j < 30; j++) {
            if (k & (1 << j)) {
                res = parent[res][j];
            }
        }
        return res;
    }
    
    int jump(int u, int v, int i) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(0 <= i);
        int l = lca(u, v);
        int cnt = dep(u) + dep(v) - 2 * dep(l);
        if (cnt < i) {
            return -1;
        }
        if (i <= dep(u) - dep(l)) {
            return la(u, i);
        } else {
            return la(v, cnt - i);
        }
    }
    
    T dist(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        int l = lca(u, v);
        return distance[u] + distance[v] - T(2) * distance[l];
    }
    
    int par(int v) const {
        assert(0 <= v && v < n);
        return parent[v][0];
    }
    
    int dep(int v) const {
        assert(0 <= v && v < n);
        return depth[v];
    }
    
    bool onpath(int u, int v, int w) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(0 <= w && w < n);
        return dist(u, w) + dist(v, w) == dist(u, v);
    }
};
