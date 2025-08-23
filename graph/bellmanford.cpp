template <class T>
vector<T> BellmanFord(StaticGraph<T> &g, int s) {
    int n = g.size();
    T mx = (is_same<T, int>::value ? 2000000000 : 1000000000000000000);
    vector<T> dist(n, mx);
    vector<bool> nega(n, false);
    dist[s] = 0;
    for (int step = 0; step < n - 1; step++) {
        bool update = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == mx) {
                continue;
            }
            for (auto &e : g[u]) {
                int v = e.to;
                T w = e.cost;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    update = true;
                }
            }
        }
        if (!update) {
            break;
        }
    }
    for (int step = 0; step < n; step++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == mx) {
                continue;
            }
            for (auto &e : g[u]) {
                int v = e.to;
                T w = e.cost;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    nega[v] = true;
                }
                if (nega[u]) {
                    nega[v] = true;
                }
            }
        }
    }
    for (int v = 0; v < n; v++) {
        if (nega[v]) {
            dist[v] = -mx;
        }
    }
    return dist;
}
