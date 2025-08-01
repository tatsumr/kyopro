// 不完全
// verify: https://atcoder.jp/contests/dwacon2017-prelims/tasks/dwango2017qual_d
// todo:
//      pop の verify
//      最小値バージョン
template <class S, S (*op)(S, S), S (*e)(), S (*inv_op)(S, S)>
struct TopK {
    private:
    int k;
    priority_queue<S, vector<S>, greater<S>> large;
    priority_queue<S> small;
    S sum;

    public:
    TopK() {}
    TopK(int k_) : k(k_), sum(e()) {}

    void push(S x) {
        if (large.size() < k) {
            large.push(x);
            sum = op(sum, x);
        } else {
            if (!large.empty() && large.top() < x) {
                small.push(large.top());
                sum = inv_op(sum, large.top());
                large.pop();
                large.push(x);
                sum = op(sum, x);
            } else {
                small.push(x);
            }
        }
    }

    void pop() {
        assert(!large.empty());
        sum = inv_op(sum, large.top());
        large.pop();
        if (!small.empty()) {
            sum = op(sum, small.top());
            large.push(small.top());
            small.pop();
        }
    }

    S prod() const {
        return sum;
    }

    int size() const {
        return large.size() + small.size();
    }
};
