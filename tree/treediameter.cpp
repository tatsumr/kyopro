// https://github.com/tatsumr/kyopro/blob/main/tree/treediameter.cpp
template <class T>
pair<T, vector<int>> TreeDiameter(StaticGraph<T> &g) {
    int n = g.size(), pos = 0;
    vector<T> d(n, -1);
    vector<int> q(n), prev(n, -1);

    auto bfs = [&](int st, bool pv = false) -> int {
        d[st] = 0, q[pos++] = st;
        T mx = 0;
        int res = st;
        
        while (pos != 0) {
            int u = q[--pos];
            for (auto &e : g[u]) {
                int v = e.to;
                T w = e.cost;
                if (d[v] != -1) continue;
                d[v] = d[u] + w, q[pos++] = v;
                if (mx < d[v]) mx = d[v], res = v;
                if (pv) prev[v] = u;
            }
        }

        return res;
    };

    int s = bfs(0);
    fill(d.begin(), d.end(), -1);
    int t = bfs(s, true);

    vector<int> path;
    int cur = t;
    while (cur != -1) {
        path.emplace_back(cur), cur = prev[cur];
    }
    return {d[t], path};
}
