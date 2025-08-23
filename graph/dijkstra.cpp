namespace dijkstra {

template <class T>
vector<T> Dijkstra(StaticGraph<T> &g, int s) {
    T mx = (is_same<T, int>::value ? 2000000000 : 1000000000000000000);
    vector<T> d(g.size(), mx);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
    d[s] = T(0);
    pq.emplace(d[s], s);
    while (!pq.empty()) {
        auto [c, v] = pq.top();
        pq.pop();
        if (d[v] < c) {
            continue;
        }
        for (auto &e : g[v]) {
            int nv = e.to;
            T nc = c + e.cost;
            if (d[nv] > nc) {
                d[nv] = nc;
                pq.emplace(d[nv], nv);
            }
        }
    }
    return d;
}

template <class T>
struct DijkstraRestore {
    private:
    int s;
    T mx;
    vector<T> d;
    vector<Edge<T>> prev;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
    
    public:
    DijkstraRestore() {}
    DijkstraRestore(StaticGraph<T> &g, int s_) : s(s_), prev(g.size()) {
        mx = (is_same<T, int>::value ? 2000000000 : 1000000000000000000);
        d.resize(g.size(), mx);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        d[s] = T(0);
        pq.emplace(d[s], s);
        while (!pq.empty()) {
            auto [c, v] = pq.top();
            pq.pop();
            if (d[v] < c) {
                continue;
            }
            for (auto &e : g[v]) {
                int nv = e.to;
                T nc = c + e.cost;
                if (d[nv] > nc) {
                    d[nv] = nc;
                    prev[nv] = e;
                    pq.emplace(d[nv], nv);
                }
            }
        }
    }
    
    vector<T> dists() const { 
        return d; 
    }
    
    T dist(int t) const {
        assert(0 <= t && t < (int)d.size());
        return d[t]; 
    }
    
    vector<Edge<T>> route(int t) const {
        assert(0 <= t && t < (int)d.size());
        if (s == t || d[t] == mx) {
            return {};
        }
        vector<Edge<T>> res;
        int cur = t;
        while (cur != s) {
            res.emplace_back(prev[cur]);
            cur = prev[cur].from;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

} // namespace dijkstra

using namespace dijkstra;
