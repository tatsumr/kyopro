#include <bits/stdc++.h>
using namespace std;

// Treap Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    TreapSet<int> st(-1);

    auto dbg = [&]() {
        cout << st.size() << "\n";
        for (int i = 0; i < st.size(); ++i) { cout << st[i] << " "; }
        cout << "\n";
    };

    int Q;
    cin >> Q;
    while (Q--) {
        int tp, x;
        cin >> tp >> x;
        if (tp == 1) {
            st.insert(x);
            dbg();
        } else if (tp == 2) {
            st.erase(x);
            dbg();
        } else if (tp == 3) {
            int a, b;
            tie(a, b) = st.gt(x); cout << a << " " << b << "\n";
            tie(a, b) = st.ge(x); cout << a << " " << b << "\n";
            tie(a, b) = st.lt(x); cout << a << " " << b << "\n";
            tie(a, b) = st.le(x); cout << a << " " << b << "\n";
        }
    }
}
