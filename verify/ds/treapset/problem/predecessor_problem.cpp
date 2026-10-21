// https://judge.yosupo.jp/problem/predecessor_problem
#include <bits/stdc++.h>
using namespace std;

// Treap Set

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    string t;
    cin >> n >> q >> t;
    TreapSet<int> s(-1);
    for (int i = 0; i < n; ++i) {
        if (t[i] == '1') {
            s.insert(i);
        }
    }
    while (q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) {
            s.insert(k);
        } else if (c == 1) {
            s.erase(k);
        } else if (c == 2) {
            cout << s.count(k) << "\n";
        } else if (c == 3) {
            cout << s.ge(k).first << "\n";
        } else {
            cout << s.le(k).first << "\n";
        }
    }
}
