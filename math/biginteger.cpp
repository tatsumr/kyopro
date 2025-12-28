struct BigInteger {
    vector<int> num;
    bool neg;
    
    BigInteger(string s = "0") : neg(false) { init(s); }
    BigInteger(long long x) : neg(false) { init(to_string(x)); }
    
    void init(string s) {
        if (s[0] == '-') { neg = true; }
        for (char c : s) {
            if (c != '-') { num.emplace_back(c - '0'); }
        }
        reverse(num.begin(), num.end());
    }
    
    vector<int> carry(vector<int> &a) {
        int n = a.size();
        for (int i = 0; i < n - 1; i++) {
            if (a[i] >= 10) {
                int k = a[i] / 10;
                a[i] -= k * 10, a[i + 1] += k;
            }
            if (a[i] < 0) {
                int k = (-a[i] - 1) / 10 + 1;
                a[i] += k * 10, a[i + 1] -= k;
            }
        }
        while (a.back() >= 10) {
            int k = a.back() / 10;
            a.back() -= k * 10;
            a.emplace_back(k);
        }
        while (a.size() >= 2 && a.back() == 0) { a.pop_back(); }
        return a;
    }
    
    vector<int> add_or_sub(const vector<int> &a, const vector<int> &b, bool add = true) {
        int n = a.size(), m = b.size();
        int k = max(n, m);
        vector<int> c(k);
        for (int i = 0; i < k; i++) {
            int x = (i < n ? a[i] : 0), y = (i < m ? b[i] : 0);
            if (!add) { y = -y; }
            c[i] = x + y;
        }
        return carry(c);
    }
    
    pair<bool, vector<int>> sub(const vector<int> &a, const vector<int> &b) {
        bool neg;
        vector<int> c;
        if (cmp_abs(a, b) >= 0) {
            neg = 0, c = add_or_sub(a, b, 0);
        } else {
            neg = 1, c = add_or_sub(b, a, 0);
        }
        return {neg, c};
    }
    
    int cmp_abs(const vector<int> &a, const vector<int> &b) const {
        int n = a.size(), m = b.size();
        if (n != m) { return (n > m ? 1 : -1); }
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] != b[i]) { return (a[i] > b[i] ? 1 : -1); }
        }
        return 0;
    }
    
    int cmp(const BigInteger &a, const BigInteger &b) const {
        if (a.neg != b.neg) { 
            return (a.neg ? -1 : 1); 
        } else {
            int res = cmp_abs(a.num, b.num);
            return (a.neg ? -res : res);
        }
    }
    
    BigInteger &operator+=(const BigInteger &a) {
        if (neg == a.neg) { 
            num = add_or_sub(num, a.num); 
        } else {
            auto [nneg, nnum] = (neg ? sub(a.num, num) : sub(num, a.num));
            neg = nneg, num = nnum;
        }
        return *this;
    }
    BigInteger &operator-=(const BigInteger &a) {
        if (neg != a.neg) {
            num = add_or_sub(num, a.num);
        } else {
            auto [nneg, nnum] = (neg ? sub(a.num, num) : sub(num, a.num));
            neg = nneg, num = nnum;
        }
        return *this;
    }
    BigInteger &operator*=(const BigInteger &a) {
        neg ^= a.neg;
        num = atcoder::convolution(num, a.num);
        carry(num);
        if (num.size() == 1 && num[0] == 0) { neg = false; }
        return *this;
    }
    
    BigInteger operator+(const BigInteger &a) const { return BigInteger(*this) += a; }
    BigInteger operator-(const BigInteger &a) const { return BigInteger(*this) -= a; }
    BigInteger operator*(const BigInteger &a) const { return BigInteger(*this) *= a; }
    
    bool operator==(const BigInteger &a) { return (cmp(*this, a) ==  0); }
    bool operator!=(const BigInteger &a) { return (cmp(*this, a) !=  0); }
    bool operator< (const BigInteger &a) { return (cmp(*this, a) == -1); }
    bool operator> (const BigInteger &a) { return (cmp(*this, a) ==  1); }
    bool operator<=(const BigInteger &a) { return (cmp(*this, a) <=  0); }
    bool operator>=(const BigInteger &a) { return (cmp(*this, a) >=  0); }
    
    friend istream &operator>>(istream &is, BigInteger &a) {
        string s; cin >> s;
        a = BigInteger(s);
        return is;
    }
    friend ostream &operator<<(ostream &os, BigInteger a) {
        string s = (a.neg ? "-" : "");
        for (int i = (int)a.num.size() - 1; i >= 0; i--) { 
            s += (a.num[i] + '0');
        }
        return os << s;
    }
};

using bint = BigInteger;
