template <class S, S (*op)(S, S), S (*e)()>
struct Treap {
    private:
    struct Node {
        Node *l, *r;
        S val;
        int pri, sz;
        S sum;
        bool rev;
        
        Node(S val_, int pri_) : 
            l(nullptr), r(nullptr),
            val(val_), pri(pri_), sz(1),
            sum(val_), rev(0) {}
    };
    
    Node *root = nullptr;
    
    unsigned int xorshift() {
        static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned int t = (x ^ (x << 11));
        x = y;
        y = z;
        z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    
    int get_sz(Node *t) { return t ? t->sz : 0; }
    
    S get_sum(Node *t) { return t ? t->sum : e(); }
    
    void update(Node *t) {
        if (t) {
            t->sz = get_sz(t->l) + get_sz(t->r) + 1;
            t->sum = op(op(get_sum(t->l), t->val), get_sum(t->r));
        }
    }
    
    void push(Node *t) {
        if (t && t->rev) {
            t->rev = false;
            swap(t->l, t->r);
            if (t->l) { t->l->rev ^= 1; }
            if (t->r) { t->r->rev ^= 1; }
        }
    }
    
    Node *merge(Node *lt, Node *rt) {
        if (!lt || !rt) {
            return lt ? lt : rt;
        } else if (lt->pri > rt->pri) {
            push(lt);
            lt->r = merge(lt->r, rt);
            update(lt);
            return lt;
        } else {
            push(rt);
            rt->l = merge(lt, rt->l);
            update(rt);
            return rt;
        }
    }
    
    pair<Node *, Node *> split(Node *t, int k) {
        if (!t) {
            return {nullptr, nullptr};
        }
        push(t);
        if (k <= get_sz(t->l)) {
            auto [lt, rt] = split(t->l, k);
            t->l = rt;
            update(t);
            return {lt, t};
        } else {
            auto [lt, rt] = split(t->r, k - get_sz(t->l) - 1);
            t->r = lt;
            update(t);
            return {t, rt};
        }
    }
    
    void dump(Node *t) {
        if (t) {
            push(t);
            dump(t->l);
            cerr << t->val << " ";
            dump(t->r);
        }
    }
    
    public:
    Treap() {}
    Treap(vector<S> &a) {
        for (int i = 0; i < int(a.size()); i++) {
            insert(i, a[i]);
        }
    }
    Treap(int n) {
        for (int i = 0; i < n; i++) {
            insert(0, e());
        }
    }
    
    void set(int p, S x) {
        assert(0 <= p && p < get_sz(root));
        erase(p);
        insert(p, x);
    }
    
    void insert(int p, S x) {
        assert(0 <= p && p <= get_sz(root));
        auto [lt, rt] = split(root, p);
        root = merge(merge(lt, new Node(x, xorshift())), rt);
    }
    
    void erase(int p) {
        assert(0 <= p && p < get_sz(root));
        auto [lt_mt, rt] = split(root, p + 1);
        auto [lt, mt] = split(lt_mt, p);
        delete mt;
        root = merge(lt, rt);
    }
    
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= get_sz(root));
        if (l == r) {
            return e();
        }
        auto [lt_mt, rt] = split(root, r);
        auto [lt, mt] = split(lt_mt, l);
        S res = mt->sum;
        root = merge(merge(lt, mt), rt);
        return res;
    }
    
    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r <= get_sz(root));
        if (l == r) {
            return;
        }
        auto [lt_mt, rt] = split(root, r);
        auto [lt, mt] = split(lt_mt, l);
        mt->rev ^= 1;
        root = merge(merge(lt, mt), rt);
    }
    
    void rotate(int l, int r, int m) {
        assert(0 <= l && l <= r && r <= get_sz(root));
        assert(l <= m && m < r);
        reverse(l, r);
        reverse(l, l + r - m);
        reverse(l + r - m, r);
    }
    
    S operator[](int p) {
        assert(0 <= p && p < get_sz(root));
        return prod(p, p + 1);
    }
    
    int size() { return get_sz(root); }
    
    void dump() {
        dump(root);
        cerr << "\n";
    }
};
