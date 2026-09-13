#include <bits/stdc++.h>
using namespace std;

// Interval Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int e = -1;
    IntervalSet<int, int, e> st;
    auto debug = [&]() {
        auto it = next(st.get(-INT_MAX));
        while (it->l != INT_MAX) {
            cout << "[" << it->l << ", " << it->r << "):" << it->val << " ";
            it++;
        }
        cout << "\n";
    };
    int ans = 0;
    auto add = [&](int l, int r, int x) { ans += r - l; };
    auto del = [&](int l, int r, int x) { ans -= r - l; };
    int Q;
    cin >> Q;
    while (Q--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        if (t == 1) {
            cin >> x;
            st.insert(l, r, x, add, del);
        } else {
            st.erase(l, r, add, del);
        }
        cout << ans << "\n";
        debug();
    }
}
