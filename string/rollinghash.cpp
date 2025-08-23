namespace rollinghash {

struct Hash {
    using ulint = unsigned long long;
    static constexpr ulint mod = (1ULL << 61) - 1;
    static constexpr ulint mask30 = (1ULL << 30) - 1;
    static constexpr ulint mask31 = (1ULL << 31) - 1;
    ulint v;
    
    Hash() : v(0) {}
    Hash(long long v_) {
        while (v_ < 0) { v_ += mod; }
        v = calcmod(v_);
    }
    
    ulint calcmod(ulint v) {
        ulint vu = v >> 61;
        ulint vd = v & mod;
        ulint res = vu + vd;
        if (res >= mod) { res -= mod; }
        return res;
    }
    
    Hash &operator+=(const Hash &rhs) {
        v += rhs.v;
        if (v >= mod) { v -= mod; }
        return *this;
    }
    Hash &operator-=(const Hash &rhs) {
        if (v < rhs.v) { v += mod; }
        v -= rhs.v;
        return *this;
    }
    Hash &operator*=(const Hash &rhs) {
        ulint lu = v >> 31, ld = v & mask31;
        ulint ru = rhs.v >> 31, rd = rhs.v & mask31;
        ulint mid = ld * ru + lu * rd;
        ulint midu = mid >> 30, midd = mid & mask30;
        v = calcmod(lu * ru * 2ULL + midu + (midd << 31) + ld * rd);
        return *this;
    }
    
    friend Hash operator+(const Hash &lhs, const Hash &rhs) {
        return Hash(lhs) += rhs;
    }
    friend Hash operator-(const Hash &lhs, const Hash &rhs) {
        return Hash(lhs) -= rhs;
    }
    friend Hash operator*(const Hash &lhs, const Hash &rhs) {
        return Hash(lhs) *= rhs;
    }
    friend bool operator==(const Hash &lhs, const Hash &rhs) {
        return lhs.v == rhs.v;
    }
    friend bool operator!=(const Hash &lhs, const Hash &rhs) {
        return lhs.v != rhs.v;
    }
};

struct RandomNumberGenerator {
    random_device seed_gen;
    mt19937_64 engine;
    
    RandomNumberGenerator() : engine(seed_gen()) {}
    
    template <class T>
    T operator()(T a, T b) {
        uniform_int_distribution<T> dist(a, b - 1);
        return dist(engine);
    }
    
    long double operator()() {
        uniform_real_distribution<long double> dist;
        return dist(engine);
    }
} rng;

struct RollingHash {
    int n;
    Hash base;
    vector<Hash> hash, power;
    
    RollingHash() {}
    RollingHash(string s, long long base_) : 
        n(s.size()), base(Hash(base_)), hash(n + 1), power(n + 1) {
        for (int i = 1; i <= n; i++) {
            hash[i] = hash[i - 1] * base + Hash(s[i - 1]);
        }
        power[0] = Hash(1);
        for (int i = 1; i <= n; i++) {
            power[i] = power[i - 1] * base;
        }
    }
    
    Hash get(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return hash[r] - hash[l] * power[r - l];
    }
    
    Hash connect(Hash h1, Hash h2, int len) {
        return h1 * power[len] + h2;
    }
};

int Lcp(RollingHash &rh1, int l1, int r1, RollingHash &rh2, int l2, int r2) {
    assert(l1 <= r1);
    assert(l2 <= r2);
    if (l1 == r1 || l2 == r2) { 
        return 0; 
    }
    int len = min(r1 - l1, r2 - l2);
    if (rh1.get(l1, l1 + len) == rh2.get(l2, l2 + len)) {
        return len;
    }
    int ac = 0, wa = len;
    while (wa - ac > 1) {
        int wj = (ac + wa) / 2;
        (rh1.get(l1, l1 + wj) == rh2.get(l2, l2 + wj) ? ac : wa) = wj;
    }
    return ac;
}

} // namsepace rollinghash

using namespace rollinghash;
