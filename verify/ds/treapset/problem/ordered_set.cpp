// https://judge.yosupo.jp/problem/ordered_set
#include <bits/stdc++.h>
using namespace std;

// Treap Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    TreapSet<int> s(-1);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        s.insert(a);
    }
    while (q--) {
        int c, x;
        cin >> c >> x;
        if (c == 0) {
            s.insert(x);
        } else if (c == 1) {
            s.erase(x);
        } else if (c == 2) {
            cout << (x <= s.size() ? s[x - 1] : -1) << "\n";
        } else if (c == 3) {
            cout << s.gt(x).second << "\n";
        } else if (c == 4) {
            cout << s.le(x).first << "\n";
        } else {
            cout << s.ge(x).first << "\n";
        }
    }
}
