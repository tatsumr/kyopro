struct Fraction {
    using lint = long long;
    
    private:
    lint gcd(lint a_, lint b_) {
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
    
    void reduce() {
        if (p != 0) {
            lint g = gcd(abs(p), abs(q));
            p /= g;
            q /= g;
        } else {
            q = 1;
        }
    }
    
    int comp(lint a, lint b, lint c, lint d) const {
        if (a == c && b == d) {
            return 0;
        }
        return (a * d < c * b ? -1 : 1);
    }

    public:
    lint p, q;
    
    Fraction() : p(0), q(1) {}
    Fraction(lint p_, lint q_) : p(p_), q(q_) {
        assert(q_ != 0);
        if (q < 0) {
            p = -p;
            q = -q;
        }
        reduce();
    }
    Fraction(lint p_) : p(p_), q(1) {}
    
    Fraction &operator+=(const Fraction &a) {
        lint np = p * a.q + q * a.p;
        lint nq = q * a.q;
        *this = Fraction(np, nq);
        return *this;
    }
    
    Fraction &operator-=(const Fraction &a) {
        lint np = p * a.q - q * a.p;
        lint nq = q * a.q;
        *this = Fraction(np, nq);
        return *this;
    }
    
    Fraction &operator*=(const Fraction &a) {
        lint np = p * a.p;
        lint nq = q * a.q;
        *this = Fraction(np, nq);
        return *this;
    }
    
    Fraction &operator/=(const Fraction &a) {
        assert(a.p != 0);
        lint np = p * a.q;
        lint nq = q * a.p;
        *this = Fraction(np, nq);
        return *this;
    }
    
    Fraction operator+(const Fraction &a) {
        return Fraction(*this) += a;
    }
    
    Fraction operator-(const Fraction &a) {
        return Fraction(*this) -= a;
    }
    
    Fraction operator*(const Fraction &a) {
        return Fraction(*this) *= a;
    }
    
    Fraction operator/(const Fraction &a) {
        return Fraction(*this) /= a;
    }
    
    Fraction operator-() {
        p = -p;
        return *this;
    }
    
    bool operator==(const Fraction &a) const {
        return comp(p, q, a.p, a.q) == 0;
    }
    
    bool operator!=(const Fraction &a) const {
        return comp(p, q, a.p, a.q) != 0;
    }
    
    bool operator<(const Fraction &a) const {
        return comp(p, q, a.p, a.q) == -1;
    }
    
    bool operator>(const Fraction &a) const {
        return comp(p, q, a.p, a.q) == 1;
    }
    
    bool operator<=(const Fraction &a) const {
        return comp(p, q, a.p, a.q) <= 0;
    }
    
    bool operator>=(const Fraction &a) const {
        return comp(p, q, a.p, a.q) >= 0;
    }
    
    friend ostream &operator<<(ostream &os, Fraction a) {
        return os << a.p << "/" << a.q;
    }
};
