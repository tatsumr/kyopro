template <class T = int>
struct WaveletMatrix {
  private:
    int H, N;
    vector<T> A;
    vector<vector<int>> dat; // dat[h] := 高さ h+1->h の情報で, 2^h の位のビットを見る

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

  public:
    WaveletMatrix() {}
    WaveletMatrix(const vector<T> &_A, int _H = 30) : H(_H), N(_A.size()), A(_A), dat(H) {
        build();
    }

    // [l, r), k: 0-indexed
    T kth_smallest(int l, int r, int k) const {
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
};
