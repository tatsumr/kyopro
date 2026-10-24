// https://atcoder.jp/contests/arc033/tasks/arc033_3
// library: https://github.com/tatsumr/kyopro
#include <bits/stdc++.h>
using namespace std;

// Treap Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Q;
    cin >> Q;
    TreapSet<int> st(-1, Q);
    while (Q--) {
        int T, X;
        cin >> T >> X;
        if (T == 1) {
            st.insert(X);
        } else {
            int ans = st[X - 1];
            cout << ans << "\n";
            st.erase(ans);
        }
    }
}
