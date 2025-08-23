namespace fastprime {

template <class T>
T modpow(T a, T b, T mod) {
    T cur = a % mod, res = 1 % mod;
    while (b) {
        if (b & 1) {
            res = (res * cur) % mod;
        }
        cur = (cur * cur) % mod;
        b >>= 1;
    }
    return res;
}

bool MillerRabin(long long n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2 || n == 7 || n == 61) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    
    vector<long long> A;
    if (n < 4759123141) {
        A = {2, 7, 61};
    } else {
        A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    }
    long long s = 0, d = n - 1;
    while (d % 2 == 0) {
        s++;
        d >>= 1;
    }
    for (auto a : A) {
        if (a % n == 0) {
            return true;
        }
        long long x = modpow<__int128_t>(a, d, n);
        if (x == 1) {
            continue;
        }
        bool ok = false;
        for (int i = 0; i < s; i++) {
            if (x == n - 1) {
                ok = true;
                break;
            }
            x = (__int128_t)x * x % n;
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}

long long gcd(long long x, long long y) {
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}

unsigned int xorshift() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

long long Pollard(long long n) {
    if (n % 2 == 0) {
        return 2LL;
    }
    if (MillerRabin(n)) {
        return n;
    }
    
    long long i = 0;
    while (true) {
        i++;
        long long r = xorshift();
        auto f = [&](long long x) {
            return (__int128_t(x) * x + r) % n;
        };
        long long x = i, y = f(x);
        while (true) {
            long long p = gcd(abs(y - x + n), n);
            if (p == 0 || p == n) {
                break;
            }
            if (p != 1) {
                return p;
            }
            x = f(x);
            y = f(f(y));
        }
    }
}

vector<long long> prime_factorize(long long n) {
    if (n == 1) {
        return {};
    }
    long long p = Pollard(n);
    if (p == n) {
        return {p};
    }
    vector<long long> l = prime_factorize(p);
    vector<long long> r = prime_factorize(n / p);
    for (auto x : r) {
        l.emplace_back(x);
    }
    sort(l.begin(), l.end());
    return l;
}

vector<long long> divisors(long long n) {
    if (n == 1) {
        return {1LL};
    }
    auto divisor_dfs = [&](auto divisor_dfs, vector<pair<long long, long long>> &p, long long t, int cur, vector<long long> &res) -> void {
        if (cur == p.size()) {
            res.emplace_back(t);
            return;
        }
        divisor_dfs(divisor_dfs, p, t, cur + 1, res);
        for (int i = 0; i < p[cur].second; i++) {
            t *= p[cur].first;
            divisor_dfs(divisor_dfs, p, t, cur + 1, res);
        }
    };
    
    vector<long long> res, pf = prime_factorize(n);
    
    vector<pair<long long, long long>> p;
    long long cnt = 1, now = pf[0];
    for (int i = 1; i < (int)pf.size(); i++) {
        if (pf[i] == now) {
            cnt++;
        } else {
            p.emplace_back(now, cnt);
            now = pf[i];
            cnt = 1;
        }
    }
    p.emplace_back(now, cnt);
    
    divisor_dfs(divisor_dfs, p, 1, 0, res);
    sort(res.begin(), res.end());
    return res;
}

} // namespace fastprime

using namespace fastprime;
