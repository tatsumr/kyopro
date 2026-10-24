template <class T, bool multi = false>
struct TreapSet {
    static constexpr int NIL = -1;

    T none;
    int n;

    struct Node {
        int p, l, r;
        T val;
        unsigned int pri;
        int sz;

        Node(T _val, unsigned int _pri)
            : p(NIL), l(NIL), r(NIL),
              val(_val), pri(_pri), sz(1) {}
    };

    vector<Node> tr;
    vector<int> free_ids;
    int root = NIL;

    unsigned int xorshift() {
        static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned int t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    int sz(int t) const {
        return t == NIL ? 0 : tr[t].sz;
    }

    void update(int t) {
        if (t == NIL) return;
        tr[t].sz = 1 + sz(tr[t].l) + sz(tr[t].r);
    }

    int new_node(T x, unsigned int pri) {
        if (!free_ids.empty()) {
            int id = free_ids.back();
            free_ids.pop_back();
            tr[id] = Node(x, pri);
            return id;
        }
        tr.emplace_back(x, pri);
        return (int)tr.size() - 1;
    }

    void rotate(int t) {
        int x = tr[t].p;
        int y = tr[x].p;

        if (tr[x].l == t) {
            tr[x].l = tr[t].r;
            if (tr[t].r != NIL) {
                tr[tr[t].r].p = x;
            }
            tr[t].r = x;
        } else {
            tr[x].r = tr[t].l;
            if (tr[t].l != NIL) {
                tr[tr[t].l].p = x;
            }
            tr[t].l = x;
        }

        tr[x].p = t;
        tr[t].p = y;

        if (y != NIL) {
            if (tr[y].l == x) tr[y].l = t;
            else tr[y].r = t;
        } else {
            root = t;
        }

        update(x);
        update(t);
    }

    int find_node(T x) const {
        int cur = root;
        while (cur != NIL) {
            if (tr[cur].val == x) return cur;
            cur = tr[cur].val > x ? tr[cur].l : tr[cur].r;
        }
        return NIL;
    }

    void insert_node(int t) {
        if (root == NIL) {
            root = t;
            return;
        }

        int cur = root;
        int par = NIL;

        while (cur != NIL) {
            par = cur;
            tr[cur].sz++;

            if (tr[cur].val > tr[t].val) {
                cur = tr[cur].l;
            } else {
                cur = tr[cur].r;
            }
        }

        tr[t].p = par;
        if (tr[par].val > tr[t].val) {
            tr[par].l = t;
        } else {
            tr[par].r = t;
        }

        while (tr[t].p != NIL &&
               tr[tr[t].p].pri < tr[t].pri) {
            rotate(t);
        }
    }

    void erase_node(int t) {
        while (tr[t].l != NIL || tr[t].r != NIL) {
            int c;
            if (tr[t].l == NIL) {
                c = tr[t].r;
            } else if (tr[t].r == NIL) {
                c = tr[t].l;
            } else {
                c = tr[tr[t].l].pri > tr[tr[t].r].pri
                    ? tr[t].l : tr[t].r;
            }
            rotate(c);
        }

        int par = tr[t].p;
        if (par != NIL) {
            if (tr[par].l == t) tr[par].l = NIL;
            else tr[par].r = NIL;

            for (int cur = par; cur != NIL; cur = tr[cur].p) {
                tr[cur].sz--;
            }
        } else {
            root = NIL;
        }

        free_ids.push_back(t);
    }

    pair<T, int> search_greater(T x, bool equal) {
        int cur = root;
        pair<T, int> res = {none, n};
        int cnt = 0;

        while (cur != NIL) {
            int id = cnt + sz(tr[cur].l);

            if (x < tr[cur].val ||
                (equal && x == tr[cur].val)) {
                res = {tr[cur].val, id};
                cur = tr[cur].l;
            } else {
                cur = tr[cur].r;
                cnt = id + 1;
            }
        }
        return res;
    }

    pair<T, int> search_less(T x, bool equal) {
        int cur = root;
        pair<T, int> res = {none, n};
        int cnt = 0;

        while (cur != NIL) {
            int id = cnt + sz(tr[cur].l);

            if (x > tr[cur].val ||
                (equal && x == tr[cur].val)) {
                res = {tr[cur].val, id};
                cur = tr[cur].r;
                cnt = id + 1;
            } else {
                cur = tr[cur].l;
            }
        }
        return res;
    }

    T kth(int k) {
        int cur = root;

        while (cur != NIL) {
            int id = sz(tr[cur].l) + 1;

            if (k == id) return tr[cur].val;

            if (k < id) {
                cur = tr[cur].l;
            } else {
                cur = tr[cur].r;
                k -= id;
            }
        }

        assert(false && "kth: index out of range");
        return none;
    }

    void debug(int t) {
        if (t == NIL) return;
        debug(tr[t].l);
        cerr << tr[t].val << " ";
        debug(tr[t].r);
    }

    TreapSet(T _none, int capacity = 0)
        : none(_none), n(0) {
        tr.reserve(capacity);
    }

    bool count(T x) {
        return find_node(x) != NIL;
    }

    void insert(T x) {
        if (!multi && count(x)) return;

        int t = new_node(x, xorshift());
        n++;
        insert_node(t);
    }

    void erase(T x) {
        int t = find_node(x);
        if (t == NIL) return;

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
        cerr << '\n';
    }
};
