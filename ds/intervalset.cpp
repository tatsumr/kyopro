template <class S, class T, T e = 0>
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
        if (l == r) {
            return true;
        }
        auto it = prev(s.upper_bound({l, SINF, e}));
        return (it->l <= l && r <= it->r);
    }
    
    bool covered(S x) {
        return covered(x, x + 1);
    }
    
    // [l, r) を含む区間 なければ [l, r) のすぐ左の区間
    auto get(S l, S r) {
        assert(l < r);
        return prev(s.upper_bound({l, SINF, e}));
    }
    
    auto get(S x) {
        return get(x, x + 1);
    }
    
    template <class ADD, class DEL>
    void insert(S l, S r, T x, const ADD &add, const DEL &del) {
        assert(l <= r);
        if (l == r) {
            return;
        }
        auto it = prev(s.upper_bound({l, SINF, e}));
        if (it->l <= l && r <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            if (x == X) {
                goto adjust;
            }
            del(L, R, X);
            s.erase(it);
            if (L < l) {
                add(L, l, X);
                s.insert({L, l, X});
            }
            if (r < R) {
                add(r, R, X);
                s.insert({r, R, X});
            }
            add(l, r, x);
            s.insert({l, r, x});
            goto adjust;
        }
        if (it->l <= l && l <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del(L, R, X);
            it = s.erase(it);
            if (x == X) {
                l = L;
            } else {
                if (L < l) {
                    add(L, l, X);
                    s.insert({L, l, X});
                }
            }
        } else {
            it = next(it);
        }
        while (it->r <= r) {
            del(it->l, it->r, it->val);
            it = s.erase(it);
        }
        if (it->l <= r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del(L, R, X);
            s.erase(it);
            if (x == X) {
                r = R;
            } else {
                if (r < R) {
                    add(r, R, X);
                    s.insert({r, R, X});
                }
            }
        }
        add(l, r, x);
        s.insert({l, r, x});
        
        adjust:
        it = s.lower_bound({l, r, x});
        auto pit = prev(it);
        auto nit = next(it);
        if (pit->r == it->l && pit->val == it->val) {
            if (it->r == nit->l && it->val == nit->val) {
                S L = pit->l, R = nit->r;
                T X = it->val;
                del(pit->l, pit->r, pit->val);
                s.erase(pit);
                del(it->l, it->r, it->val);
                s.erase(it);
                del(nit->l, nit->r, nit->val);
                s.erase(nit);
                add(L, R, X);
                s.insert({L, R, X});
            } else {
                S L = pit->l, R = it->r;
                T X = it->val;
                del(pit->l, pit->r, pit->val);
                s.erase(pit);
                del(it->l, it->r, it->val);
                s.erase(it);
                add(L, R, X);
                s.insert({L, R, X});
            }
        } else if (it->r == nit->l && it->val == nit->val) {
            S L = it->l, R = nit->r;
            T X = it->val;
            del(it->l, it->r, it->val);
            s.erase(it);
            del(nit->l, nit->r, nit->val);
            s.erase(nit);
            add(L, R, X);
            s.insert({L, R, X});
        }
        return;
    }
    
    template <class ADD, class DEL>
    void insert(S l, S r, const ADD &add, const DEL &del) {
        insert(l, r, e, add, del);
    }
    
    void insert(S l, S r, T x = e) {
        auto func = [](S l, S r, T x) {};
        insert(l, r, x, func, func);
    }
    
    void insert(S l) {
        auto func = [](S l, S r, T x) {};
        insert(l, l + 1, e, func, func);
    }
    
    template <class ADD, class DEL>
    void erase(S l, S r, const ADD &add, const DEL &del) {
        assert(l <= r);
        if (l == r) {
            return;
        }
        auto it = prev(s.upper_bound({l, SINF, e}));
        if (it->l <= l && r <= it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del(L, R, X);
            s.erase(it);
            if (L < l) {
                add(L, l, X);
                s.insert({L, l, X});
            }
            if (r < R) {
                add(r, R, X);
                s.insert({r, R, X});
            }
            return;
        }
        if (it->l <= l && l < it->r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del(L, R, X);
            it = s.erase(it);
            if (L < l) {
                add(L, l, X);
                s.insert({L, l, X});
            }
        } else {
            it = next(it);
        }
        while (it->r <= r) {
            del(it->l, it->r, it->val);
            it = s.erase(it);
        }
        if (it->l < r) {
            S L = it->l, R = it->r;
            T X = it->val;
            del(L, R, X);
            s.erase(it);
            add(r, R, X);
            s.insert({r, R, X});
        }
        return;
    }
    
    void erase(S l, S r) {
        auto func = [](S l, S r, T x) {};
        erase(l, r, func, func);
    }
    
    void erase(S l) {
        auto func = [](S l, S r, T x) {};
        erase(l, l + 1, func, func);
    }
    
    int size() const { return (int)s.size() - 2; }
    
    S mex(S x = 0) {
        auto it = prev(s.upper_bound({x, SINF, e}));
        if (it->l <= x && x < it->r) {
            return it->r;
        } else {
            return x;
        }
    }
    
    void debug() {
        for (auto node : s) {
            if (abs(node.l) != SINF) {
                cerr << "[" << node.l << ", " << node.r << "):";
                cerr << node.val;
                cerr << " ";
            }
        }
        cerr << endl;
    }
    
    private:
    set<Node> s;
    S SINF = numeric_limits<S>::max();
};
