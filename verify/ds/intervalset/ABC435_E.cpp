// https://atcoder.jp/contests/abc435/tasks/abc435_e
#include <bits/stdc++.h>
using namespace std;

// Interval Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    IntervalSet<int, int, -1> st;
    int ans = N;
    auto add = [&](int l, int r, int x) {
        ans -= (r - l);
    };
    auto del = [&](int l, int r, int x) {
        ans += (r - l);
    };
    while (Q--) {
        int L, R;
        cin >> L >> R;
        L--;
        st.insert(L, R, 0, add, del);
        cout << ans << "\n";
    }
}
