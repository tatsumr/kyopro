#include <bits/stdc++.h>
using namespace std;
#define ALL(v) (v).begin(), (v).end()

// Treap Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    set<int> st;
    const int none = -1;

    auto dbg = [&]() {
        cout << st.size() << "\n";
        for (const int x : st) { cout << x << " "; }
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
            vector<int> A;
            for (const int x : st) A.emplace_back(x);
            auto out = [&](int i) {
                if (0 <= i && i < A.size()) cout << i << " " << A[i] << "\n";
                else cout << none << " " << A.size() << "\n";
            };
            int u = upper_bound(ALL(A), x) - A.begin();
            int l = lower_bound(ALL(A), x) - A.begin();
            out(u);
            out(l);
            out(l - 1);
            out(u - 1);
        }
    }
}
