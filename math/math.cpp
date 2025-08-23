namespace math {

template <class T>
T div_floor(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a >= 0 ? a / b : (a + 1) / b - 1);
}

template <class T>
T div_ceil(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a > 0 ? (a - 1) / b + 1 : a / b);
}

template <class T>
T bin_gcd(T a_, T b_) {
    unsigned long long a = abs(a_), b = abs(b_);
    if (a == 0 || b == 0) {
        return (a == 0 ? b : a);
    }
    int x = __builtin_ctzll(a), y = __builtin_ctzll(b);
    a >>= x;
    b >>= y;
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }
        a -= b;
        a >>= __builtin_ctzll(a);
    }
    return (a << min(x, y));
}

template <class T>
T bin_gcd(const vector<T> &a) {
    T res = 0;
    for (T x : a) {
        res = bin_gcd(res, x);
    }
    return res;
}

template <class T = long long>
T ext_gcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }
    T g = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

template <class T = long long>
T bezout_coef(T a, T b, T c, T &x, T &y) {
    T g = ext_gcd(a, b, x, y);
    if (abs(c) % g) { 
        return -1; 
    }
    a /= g, b /= g, c /= g;
    if (b == 0) {
        x *= c;
        return g;
    }
    using bint = __int128_t;
    bint nx = bint(x) * bint(c);
    bint ny = bint(y) * bint(c);
    bint q = (b < 0 ? div_floor<bint>(-nx, b) : div_ceil<bint>(-nx, b));
    nx += b * q;
    ny -= a * q;
    x = nx;
    y = ny;
    return g;
}

} // namespace math

using namespace math;
