template <class T>
struct Tree {
    int n, root;
    StaticGraph<T> g;
    vector<int> depth;
    vector<T> distance;
    int lg;
    vector<vector<int>> parent;
    
    void build() {
        lg = (n == 1 ? 1 : 32 - __builtin_clz(n - 1));
        parent.assign(n, vector<int>(lg, root));
        queue<int> q;
        q.emplace(root);
        depth[root] = 0;
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
                    q.emplace(nv);
                }
            }
        }
        for (int j = 1; j < lg; ++j) {
            for (int i = 0; i < n; ++i) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
    
    Tree() {}
    Tree(StaticGraph<T> &_g, int _root = 0) :
        n(_g.size()), root(_root), g(_g), 
        depth(_g.size(), -1), distance(_g.size(), T(0)) 
    {   
        assert(0 <= root && root < n);
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
        for (int j = lg - 1; j >= 0; --j) {
            if (parent[u][j] != parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        return par(u);
    }
    
    int la(int v, int k) const {
        assert(0 <= v && v < n);
        assert(0 <= k);
        if (k >= n) return root;
        int res = v;
        for (int j = 0; j < lg; j++) {
            if (k & (1LL << j)) {
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
};
