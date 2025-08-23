template <class T>
pair<T, vector<int>> TreeDiameter(StaticGraph<T> &g) {
    auto d1 = Dijkstra(g, 0);
    int s = max_element(d1.begin(), d1.end()) - d1.begin();
    DijkstraRestore dij(g, s);
    auto d2 = dij.dists();
    int t = max_element(d2.begin(), d2.end()) - d2.begin();
    auto route = dij.route(t);
    vector<int> res;
    for (int i = 0; i < (int)route.size(); i++) {
        Edge<T> &e = route[i];
        if (i == 0) {
            res.emplace_back(e.from);
        }
        res.emplace_back(e.to);
    }
    return {d2[t], res};
}
