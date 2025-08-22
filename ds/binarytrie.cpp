template <class T = int, int B = 32>
struct BinaryTrie {
    private:
    struct Node {
        int cnt;
        T lazy;
        Node *ch[2];
        
        Node() : cnt(0), lazy(0), ch{nullptr, nullptr} {}
    };
    
    Node *root;
    bool multi;
    
    void push(Node *t, int b) {
        if ((t->lazy >> (T)b) & (T)1) {
            swap(t->ch[0], t->ch[1]);
        }
        if (t->ch[0]) {
            t->ch[0]->lazy ^= t->lazy;
        }
        if (t->ch[1]) {
            t->ch[1]->lazy ^= t->lazy;
        }
        t->lazy = 0;
        return;
    }
    
    Node *insert(Node *t, T x, int b) {
        if (!t) {
            t = new Node();
        }
        if (b < 0) {
            t->cnt = (multi ? t->cnt + 1 : 1);
            return t;
        }
        push(t, b);
        bool f = ((x >> (T)b) & (T)1);
        t->ch[f] = insert(t->ch[f], x, b - 1);
        t->cnt = (t->ch[0] ? t->ch[0]->cnt : 0) + (t->ch[1] ? t->ch[1]->cnt : 0);
        return t;
    }
    
    Node *erase(Node *t, T x, int b) {
        assert(t);
        t->cnt--;
        if (t->cnt == 0) {
            return nullptr;
        }
        if (b < 0) {
            return t;
        }
        push(t, b);
        bool f = ((x >> (T)b) & (T)1);
        t->ch[f] = erase(t->ch[f], x, b - 1);
        return t;
    }
    
    T get(Node *t, int k, int b) {
        if (b < 0) {
            return 0;
        }
        push(t, b);
        int m = (t->ch[0] ? t->ch[0]->cnt : 0);
        if (k < m) {
            return get(t->ch[0], k, b - 1);
        } else {
            return get(t->ch[1], k - m, b - 1) | ((T)1 << (T)b);
        }
    }
    
    int lower(Node *t, T x, int b) {
        if (!t || b < 0) {
            return 0;
        }
        push(t, b);
        bool f = ((x >> (T)b) & (T)1);
        return (f && t->ch[0] ? t->ch[0]->cnt : 0) + lower(t->ch[f], x, b - 1);
    }
    
    public:
    BinaryTrie(bool multi_ = false) : root(nullptr), multi(multi_) {}
    
    int size() {
        return root ? root->cnt : 0;
    }
    
    bool empty() {
        return !root;
    }
    
    void insert(T x) {
        assert(0 <= x && x <= numeric_limits<T>::max());
        root = insert(root, x, B - 1);
    }
    
    void erase(T x) {
        root = erase(root, x, B - 1);
    }
    
    void xor_all(T x) {
        if (root) {
            root->lazy ^= x;
        }
    }
    
    T operator[](int k) {
        assert(0 <= k && k < size());
        return get(root, k, B - 1);
    }
    
    int lower(T x) {
        return lower(root, x, B - 1);
    }
    
    int upper(T x) {
        return lower(root, x + 1, B - 1);
    }
    
    int count(T x) {
        if (!root) {
            return 0;
        }
        Node *t = root;
        for (int i = B - 1; i >= 0; i--) {
            push(t, i);
            t = t->ch[(x >> (T)i) & (T)1];
            if (!t) {
                return 0;
            }
        }
        return t->cnt;
    }
};
