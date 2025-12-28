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
    
    bool operator==(const Matrix &b) const { 
        return (m == b.height() && n == b.width() && a == b.a);
    }
    bool operator!=(const Matrix &b) const {
        return (m != b.height() || n != b.width() && a != b.a);
    }
};

// 掃き出し法
// {rank, 行列式} を返す
template <class T>
pair<int, T> GaussJordan(Matrix<T> &a, bool LE = false) {
    int m = a.height(), n = a.width();
    int rank = 0;
    T det = 1;
    for (int j = 0; j < (LE ? n - 1 : n); j++) {            // 掃き出したい列. 拡大係数行列のときは一番右の行は掃き出さない
        int piv = -1;                                       // 掃き出す基準にする行
        for (int i = rank; i < m; i++) {
            if (a[i][j] != 0) {
                piv = i;
                break;
            }
        }
        if (piv == -1) {                                    // その列を掃き出せない (その列が全部 0)
            det = 0;                                        // -> a は正則でない
            continue;                                       // -> 行列式が 0
        }                                       
        if (rank != piv) {
            det = -det;                                     // 行の入れ替え. 入れ替えると det は -1 倍
            swap(a[rank], a[piv]);
        }
        det *= a[rank][j];                                  // 次数を下げる公式 (第 1 列の 2 番目以降の成分が全部 0 のとき)
        if (LE && a[rank][j] != 1) {
            T val = a[rank][j];
            for (int j2 = j; j2 < n; j2++) {                // 第 rank 列を 1/val 倍
                a[rank][j2] /= val;
            }
        }
        for (int i = (LE ? 0 : rank + 1); i < m; i++) {     // 第 j 列の掃き出し. rank と det を求める場合は piv 以上の行は実際に掃き出す必要はない
            if (i == rank) { continue; }
            if (a[i][j] != 0) {
                T val = a[i][j] / a[rank][j];
                for (int j2 = 0; j2 < n; j2++) {
                    a[i][j2] -= a[rank][j2] * val;          // 第 i 行に第 rank 行 * -val を足す行基本変形. det は変わらない
                }
            }
        }
        rank++;
    }
    return {rank, det};
}

// 未知数 a.width() 個の連立方程式
// 解を持つとき
//      {v, x_1, x_2, ..., x_s} を返し, 任意の解は
//      x = v + c_1*x_1 + c_2*x_2 + ... + c_s*x_s と表せる
//      {x1, x2, ..., xs} は解空間の基底
// 解を持たないとき
//      {} を返す
template <class T>
vector<vector<T>> LinearEquation(Matrix<T> a, vector<T> b) {
    int m = a.height(), n = a.width();
    assert(a.height() == (int)b.size());
    for (int i = 0; i < m; i++) {               // 拡大係数行列 [A, b] にする
        a[i].emplace_back(b[i]);
    }
    a.n++;
    int rank = GaussJordan(a, true).first;
    for (int i = rank; i < m; i++) {
        if (a[i][n] != 0) { return {}; }        // rank [A, b] != rank A のとき解なし
    }
    vector<vector<T>> res(1, vector<T>(n));
    vector<int> piv(n, -1);                     // piv[j] := j 列目において要素が 1 なのは何行目か
    int j = 0;
    for (int i = 0; i < rank; i++) {
        while (a[i][j] == 0) { j++; }
        res[0][j] = a[i][n];                    // 定数項ベクトルの値を記録
        piv[j] = i;
    }
    for (int j = 0; j < n; j++) {               // 基底を構成していく
        if (piv[j] == -1) {                     // 列 j には 1 がない -> 未知数 x_j に任意定数を置く
            vector<T> x(n);
            x[j] = 1;
            for (int j2 = 0; j2 < j; j2++) {
                if (piv[j2] != -1) { x[j2] = -a[piv[j2]][j]; }
            }
            res.emplace_back(x);
        }
    }
    return res;
}

// 逆行列
// {rank, 逆行列} を返す. rank != n のときは正則でない
// A^-1 は, A の階段行列を求めるときの変形を I に行うと求まる
template <class T>
pair<int, Matrix<T>> InverseMatrix(Matrix<T> a) {
    assert(a.height() == a.width());
    int n = a.height();
    for (int i = 0; i < n; i++) {           // 単位行列をくっつける
        for (int j = 0; j < n; j++) {
            a[i].emplace_back(i == j);
        }
    }
    int rank = 0;
    for (int j = 0; j < n; j++) {           // 左 n 列だけ掃き出す
        int piv = -1;
        for (int i = rank; i < n; i++) {
            if (a[i][j] != 0) {
                piv = i;
                break;
            }
        }
        if (piv == -1) { continue; }
        swap(a[rank], a[piv]);
        T val = a[rank][j];
        for (int j2 = j; j2 < 2 * n; j2++) {
            a[rank][j2] /= val;
        }
        for (int i = 0; i < n; i++) {
            if (i == rank) { continue; }
            if (a[i][j] != 0) {
                T val = a[i][j];
                for (int j2 = 0; j2 < 2 * n; j2++) {
                    a[i][j2] -= a[rank][j2] * val;
                }
            }
        }
        rank++;
    }
    Matrix<T> res(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j + n];
        }
    }
    return {rank, res};
}
