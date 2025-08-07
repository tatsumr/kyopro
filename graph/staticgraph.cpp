template <class T>
struct Edge {
    int from, to;
    T cost;
    int idx;
    
    Edge() {}
    Edge(int to_) : to(to_) {}
    Edge(int to_, T cost_) : to(to_), cost(cost_) {}
    Edge(int from_, int to_, int idx_) : from(from_), to(to_), idx(idx_) {}
    Edge(int from_, int to_, T cost_, int idx_) : from(from_), to(to_), cost(cost_), idx(idx_) {}
};

template <class T>
struct StaticGraph {
    private:
    template <class It>
    struct Es {
        It b, e;
        It begin() const { return b; }
        It end() const { return e; }
        int size() const { return int(e - b); }
        auto &&operator[](int i) const { return b[i]; }
    };
    
    int n;
    vector<pair<int, Edge<T>>> es;
    vector<int> start;
    vector<Edge<T>> eli;
    bool built;
    
    public:
    StaticGraph() {}
    StaticGraph(int n_) : n(n_), start(n + 1), built(false) {}
    
    void add(int u, int v) {
        assert(!built);
        assert(0 <= u && u < n); 
        assert(0 <= v && v < n);
        es.emplace_back(u, (Edge<T>){v});
    }
    
    void add(int u, int v, T w) {
        assert(!built);
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        es.emplace_back(u, (Edge<T>){v, w});
    }
    
    void add(int u, int u_, int v, int i) {
        assert(!built);
        assert(0 <= u && u < n);
        assert(u == u_);
        assert(0 <= v && v < n);
        es.emplace_back(u, (Edge<T>){u, v, i});
    }
    
    void add(int u, int u_, int v, T w, int i) {
        assert(!built);
        assert(0 <= u && u < n); 
        assert(0 <= v && v < n);
        assert(u == u_);
        es.emplace_back(u, (Edge<T>){u, v, w, i});
    }
    
    void build() {
        if (built) {
            return;
        }
        eli.resize(es.size());
        for (auto [v, e] : es) {
            start[v + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto [v, e] : es) {
            eli[counter[v]++] = e;
        }
        built = true;
    }
    
    int size() const { 
        return n; 
    }
    
    Es<typename vector<Edge<T>>::iterator> operator[](int v) {
        assert(built);
        assert(0 <= v && v < n);
        return {eli.begin() + start[v], eli.begin() + start[v + 1]};
    }
};
