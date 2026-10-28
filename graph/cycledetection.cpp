// https://github.com/tatsumr/kyopro/blob/main/graph/cycledetection.cpp
template <class T>
struct CycleDetection {
    int n;
    StaticGraph<T> g;
    bool directed;
    vector<bool> visit, finish;
    vector<Edge<T>> history;
    
    CycleDetection() {}
    CycleDetection(StaticGraph<T> &g_, bool directed_) : 
    n(g_.size()), g(g_), directed(directed_), visit(n, false), finish(n, false) {}
    
    int dfs(int v, Edge<T> e) {
        visit[v] = true;
        history.emplace_back(e);
        for (auto ne : g[v]) {
            int nv = ne.to;
            if (!directed && e.from == nv && e.idx == ne.idx) {
                continue;
            }
            if (finish[nv]) {
                continue;
            }
            if (visit[nv] && !finish[nv]) {
                history.emplace_back(ne);
                return nv;
            }
            int pos = dfs(nv, ne);
            if (pos != -1) {
                return pos;
            }
        }
        finish[v] = true;
        history.pop_back();
        return -1;
    }
    
    vector<Edge<T>> reconstruct(int pos) {
        vector<Edge<T>> res;
        while (!history.empty()) {
            Edge e = history.back();
            res.emplace_back(e);
            history.pop_back();
            if (e.from == pos) {
                break;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    vector<Edge<T>> find() {
        int pos = -1;
        for (int v = 0; v < n && pos == -1; v++) {
            if (visit[v]) {
                continue;
            }
            history.clear();
            pos = dfs(v, (Edge<T>){-1, -1, -1, -1});
            if (pos != -1) {
                return reconstruct(pos);
            }
        }
        return {};
    }
};
