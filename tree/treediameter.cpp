// https://github.com/tatsumr/kyopro/blob/main/tree/treediameter.cpp
template <class T>
pair<T, vector<int>> TreeDiameter(StaticGraph<T> &g) {
    int n = g.size();
    vector<T> d(n, -1);
    vector<int> q(n), prev(n, -1);
    int pos = 0, s = 0, t = -1;
    T mx = 0;
    
    d[0] = 0, q[pos++] = 0;
    while (pos != 0) {
        int u = q[--pos];
        for (auto &e : g[u]) {
            int v = e.to;
            T w = e.cost;
            if (d[v] != -1) continue;
            d[v] = d[u] + w, q[pos++] = v;
            if (mx < d[v]) {
                mx = d[v], s = v;
            }
        }
    }

    fill(d.begin(), d.end(), -1);
    mx = 0, t = s;
    d[s] = 0, q[pos++] = s;
    while (pos != 0) {
        int u = q[--pos];
        for (auto &e : g[u]) {
            int v = e.to;
            T w = e.cost;
            if (d[v] != -1) continue;
            d[v] = d[u] + w, q[pos++] = v;
            if (mx < d[v]) {
                mx = d[v], t = v;
            }
            prev[v] = u;
        }
    }

    vector<int> path;
    int cur = t;
    while (cur != -1) {
        path.emplace_back(cur), cur = prev[cur];
    }
    return {d[t], path};
}
