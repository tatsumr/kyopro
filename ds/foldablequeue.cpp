template <class T, T (*op)(T, T), T (*e)()>
struct FoldableQueue {
    private:
    stack<pair<T, T>> l, r;
    
    public:
    FoldableQueue() {}
    
    void push(T x) {
        if (r.empty()) {
            r.emplace(x, x);
        } else {
            T sum = r.top().second;
            r.emplace(x, op(sum, x));
        }
    }
    
    void pop() {
        assert(l.size() > 0 || r.size() > 0);
        if (!l.empty()) {
            l.pop();
        } else {
            T now = e();
            while (!r.empty()) {
                T t = r.top().first;
                r.pop();
                now = op(t, now);
                l.emplace(t, now);
            }
            l.pop();
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
