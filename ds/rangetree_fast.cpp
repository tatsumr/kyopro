// 演算が和のとき専用
// 添字を予め管理することで add の二分探索を省略、Fenwick Tree や fws を一本の配列にする、などをしている
// 点の数が多そうなら LG=20 を変更しよう
// めっちゃ小さい数が登場するなら MN=-1001001001 を変更しよう
// 実験の歴史:
//   https://atcoder.jp/contests/awc0082/submissions/me
//   Point Add Rectangle Sum (Library Checker)

template <class T, class C = int>
struct RangeTree {
  private:
    struct Point {
        C x, y;
        int id;
        
        Point() {}
        Point(C _x, C _y, int _id = -1) : x(_x), y(_y), id(_id) {}

        bool operator<(const Point& rhs) const {
            if (x != rhs.x) return x < rhs.x;
            return y < rhs.y;
        }
        bool operator==(const Point& rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        bool operator<=(const Point& rhs) const {
            if (x != rhs.x) return x < rhs.x;
            return y <= rhs.y;
        }
    };
    int n;
    vector<Point> ps, yxs;
    
    static constexpr int LG = 20;
    static constexpr int MN = -1001001001;
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

    T __sum(int v, int r, int offset) {
        T res = 0;
        while (r > 0) {
            res += fws[r - 1 + offset];
            r -= r & -r;
        }
        return res;
    }

    T _sum(int v, C yl, C yr) {
        int st = start[v - 1], ed = start[v];
        int il = lower_bound(yxs.begin() + st, yxs.begin() + ed, Point(yl, MN)) - yxs.begin();
        int ir = lower_bound(yxs.begin() + st, yxs.begin() + ed, Point(yr, MN)) - yxs.begin();
        return __sum(v, ir - st, st) - __sum(v, il - st, st);
    }

  public:
    RangeTree() {}

    void add_point(C x, C y) {
        ps.emplace_back(Point(x, y));
    }

    void build() {
        sort(ps.begin(), ps.end());
        ps.erase(unique(ps.begin(), ps.end()), ps.end());
        n = ps.size();
        for (int i = 0; i < n; i++) {
            ps[i].id = i;
        }

        start.resize(n * 2, 1);
        start[0] = 0;
        for (int i = n - 1; i > 0; i--) {
            start[i] = start[i * 2] + start[i * 2 + 1];
        }
        for (int i = 2; i < n * 2; i++) {
            start[i] += start[i - 1];
        }
        int len = start.back();

        yxs.resize(len);
        for (int i = 0; i < n; i++) {
            int offset = start[i + n - 1];
            Point& p = ps[i];
            yxs[offset] = Point(p.y, p.x, p.id);
        }

        idx.resize(n * LG, 0);
        cur.resize(n, 1);
        for (int i = n - 1; i > 0; i--) {
            int il = start[i * 2 - 1], ir = start[i * 2];
            int ls = ir, rs = start[i * 2 + 1];
            int sz = 0;

            int now = start[i - 1];

            auto push = [&](const Point& p) -> void {
                yxs[now] = p;
                now++;
                int id = p.id;
                int& j = cur[id];
                idx[id * LG + j] = sz++;
                j++;
            };
            while (il < ls || ir < rs) {
                if (il == ls) {
                    auto& p = yxs[ir++];
                    push(p);
                } else if (ir == rs) {
                    auto& p = yxs[il++];
                    push(p);
                } else {
                    if (yxs[il] <= yxs[ir]) {
                        auto& p = yxs[il++];
                        push(p);
                    } else {
                        auto& p = yxs[ir++];
                        push(p);
                    }
                }
            }
        }
        fws.resize(len, 0);
    }

    void add(C x, C y, T val) {
        int id = lower_bound(ps.begin(), ps.end(), Point(x, y)) - ps.begin();
        assert(id < n && ps[id].x == x && ps[id].y == y);
        int j = id * LG;
        for (int i = id + n; i; i >>= 1) {
            _add(i, idx[j++], val);
        }
    }

    T sum(C xl, C xr, C yl, C yr) {
        assert(xl <= xr);
        assert(yl <= yr);
        int l = lower_bound(ps.begin(), ps.end(), Point(xl, MN)) - ps.begin();
        int r = lower_bound(ps.begin(), ps.end(), Point(xr, MN)) - ps.begin();
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
