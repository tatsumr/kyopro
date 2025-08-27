template <class T>
struct Compression {
    vector<T> a;

    Compression() {}
    Compression(vector<T> &_a) : a(_a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int size() const { return a.size(); }

    T operator[](int i) const {
        assert(0 <= i && i < int(a.size()));
        return a[i]; 
    }

    int operator()(T x) const {
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        assert(a[i] == x);
        return i;
    }
};
