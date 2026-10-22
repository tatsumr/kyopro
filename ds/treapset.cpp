template <class T, bool multi = false>
struct TreapSet {
    T none;
    int n;
    
    struct Node {
        Node *p, *l, *r;
        T val;
        unsigned int pri;
        int sz;
        
        Node(T _val, unsigned int _pri) : 
            p(nullptr), l(nullptr), r(nullptr), 
            val(_val), pri(_pri), sz(1) {}
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
    
    void update(Node *t) {
        t->sz = 1;
        if (t->l) t->sz += t->l->sz;
        if (t->r) t->sz += t->r->sz;
    }
    
    void rotate(Node *t) {
        Node *x = t->p, *y = x->p;
        if (x->l == t) {
            if ((x->l = t->r)) t->r->p = x;
            t->r = x;
        } else {
            if ((x->r = t->l)) t->l->p = x;
            t->l = x;
        }
        x->p = t;
        swap(t->sz, x->sz);
        update(x);
        if ((t->p = y)) {
            (y->l == x ? y->l : y->r) = t;
        } else {
            root = t;
        }
    }
    
    Node *find_par(T x) {
        Node *cur = root;
        while (cur) {
            cur->sz++;
            if (cur->val > x) {
                if (cur->l) { cur = cur->l; }
                else { return cur; }
            } else {
                if (cur->r) { cur = cur->r; }
                else { return cur; }
            }
        }
        return nullptr;
    }
    
    void insert_node(Node *t) {
        if (!root) {
            root = t;
            return;
        }
        Node *par = find_par(t->val);
        (par->val > t->val ? par->l : par->r) = t;
        t->p = par;
        while (t->p && t->p->pri < t->pri) {
            rotate(t);
        }
    }
    
    Node *find_node(T x) {
        Node *cur = root;
        while (cur) {
            if (cur->val == x) {
                return cur;
            } else {
                cur = (cur->val > x ? cur->l : cur->r);
            }
        }
        return cur;
    }
    
    void erase_node(Node *t) {
        while (t->l || t->r) {
            Node *c;
            if (!t->r) c = t->l;
            else if (!t->l) c = t->r;
            else c = (t->l->pri > t->r->pri ? t->l : t->r);
            rotate(c);
        }
        Node *cur = t->p;
        while (cur) {
            cur->sz--;
            cur = cur->p;
        }
        if (t->p) {
            (t->p->l == t ? t->p->l : t->p->r) = nullptr;
        } else {
            root = nullptr;
        }
        delete t;
    }
    
    pair<T, int> search_greater(T x, bool equal) {
        Node *cur = root;
        pair<T, int> res = {none, n};
        int cnt = 0;
        while (cur) {
            int id = cnt + (cur->l ? cur->l->sz : 0);
            if (x < cur->val || (equal && x == cur->val)) {
                res = {cur->val, id};
                cur = cur->l;
            } else {
                cur = cur->r;
                cnt = id + 1;
            }
        }
        return res;
    }
    
    pair<T, int> search_less(T x, bool equal) {
        Node *cur = root;
        pair<T, int> res = {none, n};
        int cnt = 0;
        while (cur) {
            int id = cnt + (cur->l ? cur->l->sz : 0);
            if (x > cur->val || (equal && x == cur->val)) {
                res = {cur->val, id};
                cur = cur->r;
                cnt = id + 1;
            } else {
                cur = cur->l;
            }
        }
        return res;
    }
    
    T kth(int k) {
        Node *cur = root;
        while (true) {
            int id = (cur->l ? cur->l->sz : 0) + 1;
            if (k == id) {
                return cur->val;
            } else if (k < id) {
                cur = cur->l;
            } else {
                cur = cur->r;
                k -= id;
            }
        }
    }
    
    void debug(Node *t) {
        if (t) {
            debug(t->l);
            cerr << t->val << " ";
            debug(t->r);
        }
    }
    
    TreapSet(T _none) : none(_none), n(0) {}
    
    bool count(T x) { return find_node(x); }
    
    void insert(T x) { 
        if (!multi && count(x)) return;
        n++;
        insert_node(new Node(x, xorshift())); 
    }
    
    void erase(T x) {
        Node *t = find_node(x);
        if (!t) return;
        n--;
        erase_node(t);
    }
    
    pair<T, int> gt(T x) { return search_greater(x, false); }
    
    pair<T, int> ge(T x) { return search_greater(x, true); }
    
    pair<T, int> lt(T x) { return search_less(x, false); }
    
    pair<T, int> le(T x) { return search_less(x, true); }
    
    T operator[](int i) {
        assert(0 <= i && i < size());
        return kth(i + 1);
    }
    
    int size() { return n; }
    
    bool empty() { return n == 0; }
    
    void debug() { 
        debug(root); 
        cerr << "\n";
    }
};
