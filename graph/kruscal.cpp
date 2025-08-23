template <class T>
pair<T, vector<Edge<T>>> Kruscal(StaticGraph<T> &g, int m) {
    int n = g.size();
    vector<Edge<T>> es(m);
    for (int v = 0; v < n; v++) {
        for (auto &e : g[v]) {
            es[e.idx] = e;
        }
    }
    sort(es.begin(), es.end(), [](const Edge<T> &a, const Edge<T> &b) { return a.cost < b.cost; });
    atcoder::dsu uf(n);
    T sum = 0;
    vector<Edge<T>> res;
    for (auto &e : es) {
        int u = e.from, v = e.to;
        T w = e.cost;
        if (!uf.same(u, v)) {
            uf.merge(u, v);
            sum += w;
            res.emplace_back(e);
        }
    }
    if ((int)uf.groups().size() > 1) {
        T mx = (is_same<T, int>::value ? 2000000000 : 1000000000000000000);
        return {mx, {}};
    }
    return {sum, res};
}
