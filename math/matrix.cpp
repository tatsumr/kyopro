template <class T>
struct Matrix {
    vector<vector<T>> a;
    int m, n;
    
    Matrix() {}
    Matrix(int _m, int _n) : m(_m), n(_n), a(_m, vector<T>(_n)) {}
    Matrix(int n) : Matrix<T>(n, n) {}
    
    vector<T> &operator[](int k) { return a[k]; }             
    const vector<T> &operator[](int k) const { return a[k]; }
    
    int height() const { return m; }
    int width() const { return n; }
    
    static Matrix I(int n) {
        Matrix mat(n);
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
        return mat;
    }
    
    Matrix &operator+=(const Matrix &b) {
        assert(m == b.height() && n == b.width());
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                (*this)[i][j] += b[i][j];
            }
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &b) {
        assert(m == b.height() && n == b.width());
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                (*this)[i][j] -= b[i][j];
            }
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &b) {
        assert(n == b.height());
        int l = b.width();
        vector<vector<T>> c(m, vector<T>(l, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < l; j++) {
                for (int k = 0; k < n; k++) {
                    c[i][j] += (*this)[i][k] * b[k][j];
                }
            }
        }
        a.swap(c);
        return (*this);
    }
    Matrix &operator^=(long long k) {
        Matrix b = Matrix::I(m);
        while (k) {
            if (k & 1) { b *= *this; }
            *this *= *this;
            k >>= 1;
        }
        a.swap(b.a);
        return *this;
    }
    
    Matrix operator+(const Matrix &b) const { return (Matrix(*this) += b); }
    Matrix operator-(const Matrix &b) const { return (Matrix(*this) -= b); }
    Matrix operator*(const Matrix &b) const { return (Matrix(*this) *= b); }
    Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }
};

template <class T>
int GaussJordan(Matrix<T> &a) {
    int m = a.height(), n = a.width();
    int rank = 0;
    for (int col = 0; col < n; col++) {         
        int piv = -1;                           
        for (int row = rank; row < m; row++) {
            if (a[row][col] != 0) {
                piv = row;
                break;
            }
        }
        if (piv == -1) {
            continue;
        }
        T val = a[piv][col];
        for (int col2 = 0; col2 < n; col2++) {  
            a[piv][col2] /= val;
        }
        swap(a[piv], a[rank]);                  
        for (int row = 0; row < m; row++) {     
            if (row != rank && a[row][col] != 0) {
                T val = a[row][col];
                for (int col2 = 0; col2 < n; col2++) {
                    a[row][col2] -= a[rank][col2] * val;
                }
            }
        }
        rank++;
    }
    return rank;
}
