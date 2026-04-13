template <class T = int>
struct WaveletMatrix {
  private:
    int H, N;
    vector<T> A;
    // dat[h] := 高さ h+1->h の情報で, 2^h の位のビットを見る（高さ H は元の列そのもの）
    vector<vector<int>> dat; 

    void build() {
        for (int h = H - 1; h >= 0; h--) {
            vector<int> dir(N), left, right;
            for (int i = 0; i < N; i++) {
                dir[i] = A[i] >> h & 1;
                (dir[i] == 0 ? left : right).emplace_back(A[i]);
            }
            int a = left.size(), b = right.size();
            for (int i = 0; i < a; i++) A[i] = left[i];
            for (int i = 0; i < b; i++) A[a + i] = right[i];

            dat[h].resize(N + 1);
            for (int i = 0; i < N; i++) dat[h][i + 1] = dat[h][i] + dir[i];
        }
    }

    // 高さ h+1 で [l, r) の列の, 高さ h での区間
    tuple<int, int, int, int> get_subtree_range(int h, int l, int r) const {
        int a0 = l - dat[h][l], a1 = dat[h][l];
        int b0 = r - dat[h][r], b1 = dat[h][r];
        int c0 = N - dat[h][N];
        return {a0, b0, c0 + a1, c0 + b1};
    }

    // a 未満
    int freq(int l, int r, T a) const {
        T L = 0, R = T(1) << H; // 今見ているノードの値の範囲
        int res = 0;
        for (int h = H; h >= 0; h--) {
            if (h == 0) {
                if (L < a) res += r - l;
                continue;
            }
            auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
            T M = (L + R) / T(2);
            if (a <= M) {
                R = M;
                l = l0, r = r0;
            } else {
                int cnt1 = dat[h - 1][r] - dat[h - 1][l];
                int cnt0 = r - l - cnt1;
                res += cnt0;
                L = M;
                l = l1, r = r1;
            }
        }
        return res;
    }

  public:
    WaveletMatrix() {}
    WaveletMatrix(const vector<T> &_A, int _H = 30) : H(_H), N(_A.size()), A(_A), dat(H) {
        build();
    }

    // [l, r), k: 0-indexed
    T kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= N);
        assert(0 <= k && k < r - l);
        T res = 0;
        for (int h = H; h >= 1; h--) {
            auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
            int left_size = r0 - l0;
            if (k < left_size) {
                l = l0, r = r0;
            } else {
                res |= T(1) << (h - 1);
                l = l1, r = r1, k = k - left_size;
            }
        }
        return res;
    }

    // [l, r), [a, b)
    int range_freq(int l, int r, T a, T b) const {
        assert(0 <= l && l <= r && r <= N);
        assert(a <= b);
        if (l == r || a == b) return 0;
        return freq(l, r, b) - freq(l, r, a);
    }
};
