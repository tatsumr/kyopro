// https://atcoder.jp/contests/abc380/tasks/abc380_e
#include <bits/stdc++.h>
using namespace std;

// Interval Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    IntervalSet<int, int, -1> s;
    vector<int> cnt(n, 0);
    auto add = [&](int l, int r, int x) { 
        cnt[x] += r - l; 
    };
    auto del = [&](int l, int r, int x) { 
        cnt[x] -= r - l; 
    };
    for (int i = 0; i < n; i++) {
        s.insert(i, i + 1, i, add, del);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, c;
            cin >> x >> c;
            x--;
            c--;
            auto it = s.get(x);
            s.erase(it->l, it->r, add, del); // なくてもいいが、verify のため
            s.insert(it->l, it->r, c, add, del);
        } else {
            int c;
            cin >> c;
            c--;
            cout << cnt[c] << endl;
        }
    }
}
