// https://atcoder.jp/contests/past202104-open/tasks/past202104_m
#include <bits/stdc++.h>
using namespace std;

// Interval Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    using lint = long long;
    int N;
    cin >> N;
    IntervalSet<int, int, -1> st;
    lint ans = 0;
    unordered_map<int, lint> mp;
    auto choose = [](lint x) {
        return x * (x - 1LL) / 2LL;
    };
    auto add = [&](int l, int r, int x) {
        lint cnt = r - l;
        ans -= choose(mp[x]);
        mp[x] += cnt;
        ans += choose(mp[x]);
    };
    auto del = [&](int l, int r, int x) {
        lint cnt = r - l;
        ans -= choose(mp[x]);
        mp[x] -= cnt;
        ans += choose(mp[x]);
    };
    for (int i = 0; i < N; i++) {
        lint A;
        cin >> A;
        st.insert(i, i + 1, A, add, del);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        st.insert(l, r, x, add, del);
        cout << ans << "\n";
    }
}
