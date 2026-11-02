template <class T>
struct Point {
    T x, y;
    
    Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}
};

template <class T>
T cross(const Point<T> &a, const Point<T> &b) {
    return a.x * b.y - a.y * b.x;
}

template <class T>
void argument_sort(vector<Point<T>> &ps) {
    auto cmp = [&](const Point<T> &a, const Point<T> &b) -> bool {
        int ah = (a.y < 0 || (a.y == 0 && a.x < 0));
        int bh = (b.y < 0 || (b.y == 0 && b.x < 0));
        if (ah != bh) return ah < bh;
        return cross(a, b) > 0;
    };
    sort(ps.begin(), ps.end(), cmp);
}
