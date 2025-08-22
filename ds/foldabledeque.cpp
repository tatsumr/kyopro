template <class T, T (*op)(T, T), T (*e)()>
struct FoldableDeque {
    private:
    stack<pair<T, T>> l, r;
    
    public:
    FoldableDeque() {}
    
    void push_front(T x) {
        if (l.empty()) {
            l.emplace(x, x);
        } else {
            T sum = l.top().second;
            l.emplace(x, op(x, sum));
        }
    }
    
    void push_back(T x) {
        if (r.empty()) {
            r.emplace(x, x);
        } else {
            T sum = r.top().second;
            r.emplace(x, op(sum, x));
        }
    }
    
    void pop_front() {
        assert(l.size() > 0 || r.size() > 0);
        if (!l.empty()) {
            l.pop();
        } else {
            vector<T> v;
            while (!r.empty()) {
                v.emplace_back(r.top().first);
                r.pop();
            }
            int n = v.size(), h = n / 2;
            T now = e();
            for (int i = h; i <= n - 2 && h <= n - 2; i++) {
                now = op(v[i], now);
                l.emplace(v[i], now);
            }
            now = e();
            for (int i = h - 1; i >= 0 && h - 1 >= 0; i--) {
                now = op(now, v[i]);
                r.emplace(v[i], now);
            }
        }
    }
    
    void pop_back() {
        assert(l.size() > 0 || r.size() > 0);
        if (!r.empty()) {
            r.pop();
        } else {
            vector<T> v;
            while (!l.empty()) {
                v.emplace_back(l.top().first);
                l.pop();
            }
            int n = v.size(), h = n / 2;
            T now = e();
            for (int i = h - 1; i >= 0 && h - 1 >= 0; i--) {
                now = op(v[i], now);
                l.emplace(v[i], now);
            }
            now = e();
            for (int i = h; i <= n - 2 && h <= n - 2; i++) {
                now = op(now, v[i]);
                r.emplace(v[i], now);
            }
        }
    }
    
    int size() {
        return l.size() + r.size();
    }
    
    bool empty() {
        return l.size() == 0 && r.size() == 0;
    }
    
    T prod() {
        T sl = (l.empty() ? e() : l.top().second);
        T sr = (r.empty() ? e() : r.top().second);
        return op(sl, sr);
    }
};
