namespace Area_of_Union_of_Rectangles {

struct AUR_S { 
    long long len;
    int cnt; 
};

AUR_S AUR_op(AUR_S a, AUR_S b) {
    if (a.cnt != b.cnt) {
        return a.cnt < b.cnt ? a : b;
    } else {
        return {a.len + b.len, a.cnt};
    }
}

AUR_S AUR_e() {
    return {0, 2000000000};
}

AUR_S AUR_mpg(int f, AUR_S x) {
    x.cnt += f;
    return x;
}

int AUR_cmp(int f, int g) {
    return f + g;
}

int AUR_id() {
    return 0;
}

struct AUR {
    using lint = long long;
    using rectangle = tuple<lint, lint, lint, lint>;
    
    private:
    vector<rectangle> recs;
    vector<lint> xs, ys, dx, dy;
    vector<vector<tuple<int, int, int>>> event;
    
    public:
    AUR() {}
    AUR(vector<rectangle> &recs_) : recs(recs_) {
        build();
    }
    
    void add(lint l, lint r, lint d, lint u) {
        assert(l < r);
        assert(d < u);
        recs.emplace_back(l, r, d, u);
    }
    
    void build() {
        for (auto [l, r, d, u] : recs) {
            xs.emplace_back(l);
            xs.emplace_back(r);
            ys.emplace_back(d);
            ys.emplace_back(u);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        dx.resize((int)xs.size() - 1);
        for (int i = 0; i < (int)xs.size() - 1; i++) {
            dx[i] = xs[i + 1] - xs[i];
        }
        dy.resize((int)ys.size() - 1);
        for (int i = 0; i < (int)ys.size() - 1; i++) {
            dy[i] = ys[i + 1] - ys[i];
        }
        event.resize((int)xs.size());
        for (auto [l, r, d, u] : recs) {
            int in = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            int out = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
            int left = lower_bound(ys.begin(), ys.end(), d) - ys.begin();
            int right = lower_bound(ys.begin(), ys.end(), u) - ys.begin();
            event[in].emplace_back(left, right, 1);
            event[out].emplace_back(left, right, -1);
        }
    }
    
    lint get() {
        atcoder::lazy_segtree<AUR_S, AUR_op, AUR_e, int, AUR_mpg, AUR_cmp, AUR_id> seg((int)dy.size());
        for (int i = 0; i < (int)dy.size(); i++) {
            seg.set(i, {dy[i], 0});
        }
        lint sum = accumulate(dy.begin(), dy.end(), 0LL);
        lint res = 0;
        for (int i = 0; i < (int)dx.size(); i++) {
            for (auto [left, right, num] : event[i]) {
                seg.apply(left, right, num);
            }
            auto fold = seg.all_prod();
            lint leny = sum - (fold.cnt == 0 ? fold.len : 0);
            res += dx[i] * leny;
        }
        return res;
    }
};

} // namespace Area_of_Union_of_Rectangles

using namespace Area_of_Union_of_Rectangles;
