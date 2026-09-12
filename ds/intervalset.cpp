template <class S, class T, T e>
struct IntervalSet {
  public:
    struct Node {
        S l, r;
        T val;
        
        bool operator<(const Node &rhs) const {
            return (l != rhs.l ? l < rhs.l : r < rhs.r);
        }
    };
    
    IntervalSet() {
        s.insert({-SINF, -SINF, e});
        s.insert({SINF, SINF, e});
    }
    
    bool covered(S l, S r) {
        assert(l <= r);
        if (l == r) return true;
        auto it = prev(s.upper_bound({l, SINF, e}));
        return (it->l <= l && r <= it->r);
    }
    
    bool covered(S x) { return covered(x, x + 1); }
    
    // [l, r) を含む区間 なければ [l, r) のすぐ左の区間
    auto get(S l, S r) {
        assert(l < r);
        return prev(s.upper_bound({l, SINF, e}));
    }
    
    auto get(S x) { return get(x, x + 1); }
    
    template <class ADD, class DEL>
    void insert(S l, S r, T x, const ADD &add, const DEL &del) {
        assert(l <= r);
        if (l == r) return;
        auto it = prev(s.upper_bound({l, SINF, e}));
        if (it->l <= l && r <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            if (x == X) {
                goto adjust;
            }
            del_node(it, del);
            add_node(L, l, X, add);
            add_node(r, R, X, add);
            add_node(l, r, x, add);
            goto adjust;
        }
        if (it->l <= l && l <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            it = del_node(it, del);
            if (x == X) {
                l = L;
            } else {
                add_node(L, l, X, add);
            }
        } else {
            it = next(it);
        }
        while (it->r <= r) {
            it = del_node(it, del);
        }
        if (it->l <= r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del_node(it, del);
            if (x == X) {
                r = R;
            } else {
                add_node(r, R, X, add);
            }
        }
        add_node(l, r, x, add);
        
        adjust:
        auto merge = [&](auto a, auto b) {
            S L = a->l, R = b->r;
            T X = a->val;
            auto hint = next(b);
            del_node(a, del);
            del_node(b, del);
            add(L, R, X);
            return s.emplace_hint(hint, Node{L, R, X});
        };
        it = s.lower_bound({l, r, x});
        auto pit = prev(it);
        auto nit = next(it);
        if (pit->r == it->l && pit->val == it->val) it = merge(pit, it);
        if (it->r == nit->l && it->val == nit->val) it = merge(it, nit);
        return;
    }
    template <class ADD, class DEL>
    void insert(S l, S r, const ADD &add, const DEL &del) { 
        insert(l, r, e, add, del); 
    }
    void insert(S l, S r, T x = e) {
        auto func = [&](S l, S r, T x) {};
        insert(l, r, x, func, func);
    }
    void insert(S l) {
        insert(l, l + 1);
    }
    
    template <class ADD, class DEL>
    void erase(S l, S r, const ADD &add, const DEL &del) {
        assert(l <= r);
        if (l == r) return;
        auto it = prev(s.upper_bound({l, SINF, e}));
        if (it->l <= l && r <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del_node(it, del);
            add_node(L, l, X, add);
            add_node(r, R, X, add);
            return;
        }
        if (it->l <= l && l < it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            it = del_node(it, del);
            add_node(L, l, X, add);
        } else {
            it = next(it);
        }
        while (it->r <= r) {
            it = del_node(it, del);
        }
        if (it->l < r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del_node(it, del);
            add_node(r, R, X, add);
        }
        return;
    }
    void erase(S l, S r) {
        auto func = [&](S l, S r, T x) {};
        erase(l, r, func, func);
    }
    void erase(S l) {
        erase(l, l + 1);
    }
    
    int size() const { return (int)s.size() - 2; }
    
    S mex(S x = 0) {
        auto it = prev(s.upper_bound({x, SINF, e}));
        return ((it->l <= x && x < it->r) ? it->r : x);
    }
    
    void debug() {
        for (const auto &node : s) {
            if (abs(node.l) != SINF) {
                cerr << "[" << node.l << ", " << node.r << "):";
                cerr << node.val;
                cerr << " ";
            }
        }
        cerr << "\n";
    }
    
  private:
    set<Node> s;
    S SINF = numeric_limits<S>::max();
    using It = typename set<Node>::iterator;

    template <class ADD>
    void add_node(S l, S r, T x, const ADD &add) {
        if (l == r) return;
        add(l, r, x);
        s.insert({l, r, x});
    }
    
    template <class DEL>
    It del_node(It it, const DEL &del) {
        del(it->l, it->r, it->val);
        return s.erase(it);
    }
};

