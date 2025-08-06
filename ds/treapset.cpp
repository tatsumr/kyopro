template <class T, bool multi = false>
struct TreapSet {
    private:
    T none;
    int n;
    
    struct Node {
        Node *p, *l, *r;
        T val;
        int pri, sz;
        
        Node(T val_, int pri_) : 
            p(nullptr), l(nullptr), r(nullptr), 
            val(val_), pri(pri_), sz(1) {}
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
        if (t->l) { t->sz += t->l->sz; }
        if (t->r) { t->sz += t->r->sz; }
    }
    
    void rotr(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->l = t->r)) {
            t->r->p = x;
        }
        t->r = x;
        x->p = t;
        swap(t->sz, x->sz);
        update(x);
        if ((t->p = y)) {
            if (y->l == x) { y->l = t; }
            if (y->r == x) { y->r = t; }
            update(y);
        } else {
            root = t;
        }
    }
    
    void rotl(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->r = t->l)) {
            t->l->p = x;
        }
        t->l = x;
        x->p = t;
        swap(t->sz, x->sz);
        update(x);
        if ((t->p = y)) {
            if (y->l == x) { y->l = t; }
            if (y->r == x) { y->r = t; }
            update(y);
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
    
    void insert(Node *t) {
        if (!root) {
            root = t;
            return;
        }
        Node *par = find_par(t->val);
        if (!par) {
            return;
        }
        (par->val > t->val ? par->l : par->r) = t;
        t->p = par;
        while (t->p) {
            if (t->p->l == t && t->p->pri < t->pri) {
                rotr(t);
            } else if (t->p->r == t && t->p->pri < t->pri) {
                rotl(t);
            } else {
                break;
            }
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
    
    void erase(Node *t) {
        if (!t) {
            return;
        }
        while (t->l || t->r) {
            if (!t->r) { 
                rotr(t->l); 
            } else if (!t->l) { 
                rotl(t->r); 
            } else {
                (t->l->pri > t->r->pri ? rotr(t->l) : rotl(t->r));
            }
        }
        Node *cur = t->p;
        while (cur) {
            cur->sz--;
            cur = cur->p;
        }
        if (t->p) {
            (t->p->l == t ? t->p->l : t->p->r) = nullptr;
            t->p = nullptr;
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
    
    public:
    TreapSet(T none_) : none(none_), n(0) {}
    
    bool count(T x) { return find_node(x); }
    
    void insert(T x) { 
        if (!multi && count(x)) { return; }
        n++;
        insert(new Node(x, xorshift())); 
    }
    
    void erase(T x) {
        if (!count(x)) { return; }
        n--;
        erase(find_node(x));
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
