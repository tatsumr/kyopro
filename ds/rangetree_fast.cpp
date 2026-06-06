// 速くなっている...はず
// 演算が和のとき
// 高速化のために添字を予め管理することで二分探索を省略、Fenwick Tree を一本の配列にする、などをしている
// 点の数が多そうなら LG=20 を変更しよう
// 実験の歴史...https://atcoder.jp/contests/awc0082/submissions/me, Point Add Rectangle Sum

template <class T, class C = int>
struct RangeTree {
  private:
    using P = pair<C, C>;
    int n;
    C MN = numeric_limits<C>::min();
    vector<P> ps;
    vector<vector<P>> yxs;
    
    static constexpr int LG = 20;
    vector<int> idx, cur;

    vector<T> fws;
    vector<int> start;

    void _add(int v, int i, const T val) {
        int offset = start[v - 1];
        int len = start[v] - offset;
        i++;
        while (i <= len) {
            fws[i - 1 + offset] += val;
            i += i & -i;
        }
    }

    T __sum(int v, int r) {
        T res = 0;
        int offset = start[v - 1];
        while (r > 0) {
            res += fws[r - 1 + offset];
            r -= r & -r;
        }
        return res;
    }

    T _sum(int v, C yl, C yr) {
        int il = lower_bound(yxs[v].begin(), yxs[v].end(), P{yl, MN}) - yxs[v].begin();
        int ir = lower_bound(yxs[v].begin(), yxs[v].end(), P{yr, MN}) - yxs[v].begin();
        return __sum(v, ir) - __sum(v, il);
    }

  public:
    RangeTree() {}

    void add_point(C x, C y) {
        ps.emplace_back(x, y);
    }

    void build() {
        sort(ps.begin(), ps.end());
        ps.erase(unique(ps.begin(), ps.end()), ps.end());
        n = ps.size();
        yxs.resize(n * 2);
        idx.resize(n * LG, 0);
        cur.resize(n, 1);
        for (int i = 0; i < n; i++) {
            yxs[i + n].emplace_back(ps[i].second, ps[i].first);
        }
        for (int i = n - 1; i > 0; i--) {
            auto& l = yxs[i * 2];
            auto& r = yxs[i * 2 + 1];
            int ls = l.size(), rs = r.size();
            int il = 0, ir = 0;
            int sz = 0;
            auto push = [&](const int x, const int y) -> void {
                yxs[i].emplace_back(y, x);
                int id = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
                int& j = cur[id];
                idx[id * LG + j] = sz++;
                j++;
            };
            while (il < ls || ir < rs) {
                if (il == ls) {
                    auto [y, x] = r[ir++];
                    push(x, y);
                } else if (ir == rs) {
                    auto [y, x] = l[il++];
                    push(x, y);
                } else {
                    if (l[il] <= r[ir]) {
                        auto [y, x] = l[il++];
                        push(x, y);
                    } else {
                        auto [y, x] = r[ir++];
                        push(x, y);
                    }
                }
            }
        }
        start.resize(n * 2, 1);
        for (int i = n - 1; i > 0; i--) {
            start[i] = start[i * 2] + start[i * 2 + 1];
        }
        for (int i = 1; i < n * 2; i++) {
            start[i] += start[i - 1];
        }
        fws.resize(start.back(), 0);
    }

    void add(C x, C y, T val) {
        int id = lower_bound(ps.begin(), ps.end(), P{x, y}) - ps.begin();
        assert(id < n && ps[id].first == x && ps[id].second == y);
        int j = id * LG;
        for (int i = id + n; i; i >>= 1) {
            _add(i, idx[j++], val);
        }
    }

    T sum(C xl, C xr, C yl, C yr) {
        assert(xl <= xr);
        assert(yl <= yr);
        int l = lower_bound(ps.begin(), ps.end(), P{xl, MN}) - ps.begin();
        int r = lower_bound(ps.begin(), ps.end(), P{xr, MN}) - ps.begin();
        l += n, r += n;
        T res = 0;
        while (l < r) {
            if (l & 1) {
                res += _sum(l++, yl, yr);
            }
            if (r & 1) {
                res += _sum(--r, yl, yr);
            }
            l >>= 1, r >>= 1;
        }
        return res;
    }
    
    T get(C x, C y) {
        return sum(x, x + 1, y, y + 1);
    }
};
