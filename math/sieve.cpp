struct Sieve {
    private:
    int n;
    vector<int> IdxtoVal, ValtoIdx;
    vector<bool> deleted;
    
    void build() {
        int sz = (n % 30 == 0 ? n / 30 : n / 30 + 1);
        sz *= 8;
        IdxtoVal = {1, 7, 11, 13, 17, 19, 23, 29};
        for (int i = 0; i < 8; i++) {
            ValtoIdx[IdxtoVal[i]] = i;
        }
        deleted.assign(sz, false);
        for (int i = 1; i < sz; i++) {
            if (deleted[i]) {
                continue;
            }
            int p = getval(i);
            for (int j = i; j < sz; j++) {
                int q = getval(j);
                if (q > n / p) {
                    break;
                }
                deleted[getidx(p * q)] = true;
            }
        }
    }
    
    int getval(int i) {
        return i / 8 * 30 + IdxtoVal[i % 8];
    }
    
    int getidx(int x) {
        return x / 30 * 8 + ValtoIdx[x % 30];
    }
    
    public:
    Sieve(int n_) : n(n_), IdxtoVal(8), ValtoIdx(30) {
        build();
    }
    
    bool isprime(int x) {
        if (x == 1) {
            return false;
        } else if (x == 2 || x == 3 || x == 5) {
            return true;
        } else if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) {
            return false;
        } else {
            return !deleted[getidx(x)];
        }
    }
    
    template <class T = int>
    vector<T> primes() {
        vector<T> res;
        for (T i = 2; i <= T(n); i++) {
            if (isprime(i)) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};
