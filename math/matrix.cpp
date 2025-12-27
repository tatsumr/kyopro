template <class T>
struct Matrix {
    vector<vector<T>> a;
    int m, n;
    
    Matrix() {}
    Matrix(int _m, int _n) : m(_m), n(_n), a(_m, vector<T>(_n)) {}  // 縦 m * 横 n
    Matrix(int n) : Matrix<T>(n, n) {}
    
    vector<T> &operator[](int k) { return a[k]; }                   // 書き換えられるように
    const vector<T> &operator[](int k) const { return a[k]; }       // 読み取れるように
    
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

// 掃き出し法
// {ランク, 行列式} を返す
template <class T>
pair<int, T> GaussJordan(Matrix<T> &a) {
    int m = a.height(), n = a.width();
    int rank = 0;
    T det = 1;
    for (int j = 0; j < n; j++) {                   // 掃き出したい列
        int piv = -1;                               // 掃き出す基準にする行
        for (int i = rank; i < m; i++) {
            if (a[i][j] != 0) {
                piv = i;
                break;
            }
        }
        if (piv == -1) {                            // その列を掃き出せない (その列が全部 0)
            det = 0;                                // -> a は正則でない
            continue;                               // -> 行列式が 0
        }                                       
        if (rank != piv) {
            det = -det;                             // 行の入れ替え. 入れ替えると det は -1 倍
            swap(a[rank], a[piv]);
        }
        det *= a[rank][j];                          // 次数を下げる公式 (第 1 列の 2 番目以降の成分が全部 0 のとき)
        for (int i = rank + 1; i < m; i++) {        // 第 j 列の掃き出し. rank と det を求める場合は piv 以上の行は実際に掃き出す必要はない
            if (a[i][j] != 0) {
                T val = a[i][j] / a[rank][j];
                for (int j2 = 0; j2 < n; j2++) {
                    a[i][j2] -= a[rank][j2] * val;  // 第 i 行に第 rank 行 * -val を足す行基本変形. det は変わらない
                }
            }
        }
        rank++;
    }
    return {rank, det};
}
