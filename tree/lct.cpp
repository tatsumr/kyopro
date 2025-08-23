template <class S, S (*op)(S, S), S (*e)()>
struct LinkCutTree {
    private:
    struct Node {
        Node *p, *l, *r;
        int idx;
        S val, sum;
        int sz;
        bool rev;
        
        Node(int idx_) : p(nullptr), l(nullptr), r(nullptr), idx(idx_), val(e()), sum(e()), sz(1), rev(false) {}
        
        bool is_root() {
            return (!p || (p->l != this && p->r != this));
        }
    };
    
    void update(Node *t) {
        t->sz = 1;
        t->sum = t->val;
        if (t->l) {
            t->sz += t->l->sz;
            t->sum = op(t->l->sum, t->sum);
        }
        if (t->r) {
            t->sz += t->r->sz;
            t->sum = op(t->sum, t->r->sum);
        }
    }
    
    void toggle(Node *t) {
        swap(t->l, t->r);
        t->rev ^= true;
    }
    
    void push(Node *t) {
        if (t->rev) {
            if (t->l) {
                toggle(t->l);
            }
            if (t->r) {
                toggle(t->r);
            }
            t->rev = false;
        }
    }
    
    void rotr(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->l = t->r)) {
            t->r->p = x;
        }
        t->r = x;
        x->p = t;
        update(x);
        update(t);
        if ((t->p = y)) {
            if (y->l == x) {
                y->l = t;
            }
            if (y->r == x) {
                y->r = t;
            }
            update(y);
        }
    }
    
    void rotl(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->r = t->l)) {
            t->l->p = x;
        }
        t->l = x;
        x->p = t;
        update(x);
        update(t);
        if ((t->p = y)) {
            if (y->l == x) {
                y->l = t;
            }
            if (y->r == x) {
                y->r = t;
            }
            update(y);
        }
    }
    
    void splay(Node *t) {
        push(t);
        while (!t->is_root()) {
            Node *q = t->p;
            if (q->is_root()) {
                push(q);
                push(t);
                if (q->l == t) {
                    rotr(t);
                } else {
                    rotl(t);
                }
            } else {
                Node *r = q->p;
                push(r);
                push(q);
                push(t);
                if (r->l == q) {
                    if (q->l == t) {
                        rotr(q);
                        rotr(t);
                    } else {
                        rotl(t);
                        rotr(t);
                    }
                } else {
                    if (q->r == t) {
                        rotl(q);
                        rotl(t);
                    } else {
                        rotr(t);
                        rotl(t);
                    }
                }
            }
        }
    }
    
    Node *expose(Node *t) {
        Node *rp = nullptr;
        for (Node *cur = t; cur; cur = cur->p) {
            splay(cur);
            cur->r = rp;
            update(cur);
            rp = cur;
        }
        splay(t);
        return rp;
    }
    
    void link(Node *child, Node *parent) {
        expose(child);
        expose(parent);
        child->p = parent;
        parent->r = child;
        update(parent);
    }
    
    void cut(Node *child) {
        expose(child);
        Node *parent = child->l;
        child->l = nullptr;
        parent->p = nullptr;
        update(child);
    }
    
    void evert(Node *t) {
        expose(t);
        toggle(t);
        push(t);
    }
    
    void set(Node *t, S x) {
        expose(t);
        t->val = x;
        update(t);
    }
    
    Node *lca(Node *u, Node *v) {
        if (!is_connected(u, v)) {
            return nullptr;
        }
        expose(u);
        return expose(v);
    }
    
    bool is_connected(Node *u, Node *v) {
        expose(u);
        expose(v);
        return (u == v || u->p);
    }
    
    Node *get_root(Node *x) {
        expose(x);
        while (x->l) {
            push(x);
            x = x->l;
        }
        return x;
    }
    
    Node *get_kth(Node *x, int k) {
        expose(x);
        while (x) {
            push(x);
            if (x->r && x->r->sz > k) {
                x = x->r;
            } else {
                if (x->r) {
                    k -= x->r->sz;
                }
                if (k == 0) {
                    return x;
                }
                k--;
                x = x->l;
            }
        }
        return nullptr;
    }
    
    vector<int> get_path(Node *x) {
        vector<int> res;
        auto dfs = [&](auto dfs, Node *cur) -> void {
            if (!cur) {
                return;
            }
            push(cur);
            dfs(dfs, cur->r);
            res.emplace_back(cur->idx);
            dfs(dfs, cur->l);
        };
        expose(x);
        dfs(dfs, x);
        return res;
    }
    
    int n;
    vector<Node *> nodes;
    
    public:
    LinkCutTree() {}
    LinkCutTree(int n_) : n(n_), nodes(n) {
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }
    }
    
    int expose(int v) {
        assert(0 <= v && v < n);
        return expose(nodes[v])->idx;
    }
    
    void link(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        evert(nodes[u]);
        link(nodes[u], nodes[v]);
    }
    
    void cut(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        evert(nodes[u]);
        cut(nodes[v]);
    }
    
    void evert(int v) {
        assert(0 <= v && v < n);
        evert(nodes[v]);
    }
    
    void set(int v, S x) {
        assert(0 <= v && v < n);
        set(nodes[v], x);
    }
    
    S get(int v) {
        assert(0 <= v && v < n);
        return nodes[v]->val;
    }
    
    int lca(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        Node *l = lca(nodes[u], nodes[v]);
        return (l ? l->idx : -1);
    }
    
    S query(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        evert(nodes[u]);
        expose(nodes[v]);
        return nodes[v]->sum;
    }
    
    bool is_connected(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        return is_connected(nodes[u], nodes[v]);
    }
    
    int get_root(int v) {
        assert(0 <= v && v < n);
        return get_root(nodes[v])->idx;
    }
    
    int get_kth(int v, int k) {
        assert(0 <= v && v < n);
        assert(0 <= k);
        return get_kth(nodes[v], k)->idx;
    }
    
    vector<int> get_path(int v) {
        assert(0 <= v && v < n);
        return get_path(nodes[v]);
    }
};
