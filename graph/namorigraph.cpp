template <class T>
struct NamoriGraph {
    private:
    int n;
    vector<int> roots, arrive;
    vector<Edge<T>> es;
    
    public:
    NamoriGraph() {}
    NamoriGraph(StaticGraph<T> &g) : n(g.size()), roots(n, -1), arrive(n, -1) {
        vector<int> deg(n);
        queue<int> q;
        for (int v = 0; v < n; v++) {
            deg[v] = g[v].size();
            if (deg[v] == 1) {
                q.emplace(v);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : g[v]) {
                int nv = e.to;
                if (deg[nv] == 1) {
                    continue;
                }
                deg[nv]--;
                if (deg[nv] == 1) {
                    q.push(nv);
                }
            }
        }
        for (int v = 0; v < n; v++) {
            if (roots[v] == -1 && deg[v] > 1) {
                Edge<T> now;
                for (auto &e : g[v]) {
                    if (deg[e.to] > 1) {
                        now = e;
                        break;
                    }
                }
                do {
                    es.emplace_back(now);
                    int nv = now.to;
                    for (auto &ne : g[nv]) {
                        if (ne.idx != now.idx && deg[ne.to] > 1) {
                            now = ne;
                            break;
                        }
                    }
                } while (now.from != v);
                for (auto &e : es) {
                    roots[e.to] = e.to;
                    arrive[e.to] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (roots[i] == -1) {
                continue;
            }
            queue<int> q;
            q.emplace(i);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto &e : g[v]) {
                    int nv = e.to;
                    if (roots[nv] != -1) {
                        continue;
                    }
                    roots[nv] = roots[v];
                    arrive[nv] = arrive[v] + 1;
                    q.emplace(nv);
                }
            }
        }
    }
    
    int root(int v) const {
        assert(0 <= v && v < n);
        return roots[v];
    }
    
    int to_cycle(int v) const {
        assert(0 <= v && v < n);
        return arrive[v];
    }
    
    int len_cycle() const {
        return es.size();
    }
    
    vector<Edge<T>> cycle() const {
        return es;
    }
};
