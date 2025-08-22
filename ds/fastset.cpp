struct FastSet {
    using uint = unsigned int;
    using ulint = unsigned long long;
    
    private:
    int n, sz, cnt;
    uint B = 64;
    vector<vector<ulint>> seg;
    
    int bsf(ulint x) const { return __builtin_ctzll(x); }
    
    int bsr(ulint x) const { return 63 - __builtin_clzll(x); }
    
    public:
    FastSet() {}
    FastSet(int n_) : n(n_), cnt(0) {
        do {
            n_ = (n_ + B - 1) / B;
            seg.emplace_back(vector<ulint>(n_));
        } while (n_ > 1);
        sz = seg.size();
    }
    
    bool count(int x) const {
        assert(0 <= x && x < n);
        return (seg[0][x / B] & (1ULL << (x % B)));
    }
    
    void insert(int x) {
        assert(0 <= x && x < n);
        if (count(x)) {
            return;
        }
        cnt++;
        for (int i = 0; i < sz; i++) {
            seg[i][x / B] |= 1ULL << (x % B);
            x /= B;
        }
    }
    
    void erase(int x) {
        assert(0 <= x && x < n);
        if (!count(x)) {
            return;
        }
        cnt--;
        ulint y = 0;
        for (int i = 0; i < sz; i++) {
            seg[i][x / B] &= ~(1ULL << (x % B));
            seg[i][x / B] |= y << (x % B);
            y = (seg[i][x / B] ? 1ULL : 0ULL);
            x /= B;
        }
    }
    
    // x 以上で最小 なければ -1
    int next(int x) const {
        if (x >= n) {
            return -1;
        }
        for (int i = 0; i < sz; i++) {
            if (x / B == seg[i].size()) {
                break;
            }
            ulint d = seg[i][x / B] >> (x % B);
            if (!d) {
                x = x / B + 1;
                continue;
            }
            x += bsf(d);
            for (int j = i - 1; j >= 0; j--) {
                x *= B;
                x += bsf(seg[j][x / B]);
            }
            return x;
        }
        return -1;
    }
    
    // x 以下で最大 なければ -1
    int prev(int x) const {
        if (x <= -1) {
            return -1;
        }
        for (int i = 0; i < sz; i++) {
            if (x == -1) {
                break;
            }
            ulint d = seg[i][x / B] << (63 - x % B);
            if (!d) {
                x = x / B - 1;
                continue;
            }
            x += bsr(d) - (B - 1);
            for (int j = i - 1; j >= 0; j--) {
                x *= B;
                x += bsr(seg[j][x / B]);
            }
            return x;
        }
        return -1;
    }
    
    int min() const { return next(0); }
    
    int max() const { return prev(n - 1); }
    
    int size() const { return cnt; }
    
    bool empty() const { return cnt == 0; }
};
