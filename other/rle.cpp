template <class T>
vector<pair<T, int>> RLE(vector<T> &v) {
    vector<pair<T, int>> res;
    for (auto x : v) {
        if (res.size() == 0 || res.back().first != x) {
            res.emplace_back(x, 1);
        } else {
            res.back().second++;
        }
    }
    return res;
}

vector<pair<char, int>> RLE(string &s) {
    vector<char> v;
    for (char &c : s) {
        v.emplace_back(c);
    }
    return RLE(v);
}
