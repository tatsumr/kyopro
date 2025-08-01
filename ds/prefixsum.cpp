template <class T>
struct PrefixSum {
    int n;
    vector<T> s;
    
    PrefixSum() {}
    PrefixSum(vector<T> &a) : n(a.size()), s(n + 1, T(0)) {
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + a[i];
        }
    }
   
    // [l, r)
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return s[r] - s[l];
    }
};
