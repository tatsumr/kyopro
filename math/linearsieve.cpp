struct LinearSieve {
    int n;
    vector<int> primes, spf;
    
    LinearSieve(int n_) : n(n_), spf(n + 1, 0) {
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.emplace_back(i);
            }
            for (int p : primes) {
                if (p * i > n || p > spf[i]) {
                    break;
                }
                spf[p * i] = p;
            }
        }
    }
    
    bool isprime(int x) {
        return (x >= 2 && spf[x] == x);
    }
    
    vector<int> mobius() {
        vector<int> res(n + 1, 0);
        res[1] = 1;
        for (int p : primes) {
            res[p] = -1;
        }
        for (int i = 2; i <= n; i++) {
            if (res[i] == 0) {
                continue;
            }
            for (int p : primes) {
                if (p * i > n || p >= spf[i]) {
                    break;
                }
                res[p * i] = -res[i];
            }
        }
        return res;
    }
};
