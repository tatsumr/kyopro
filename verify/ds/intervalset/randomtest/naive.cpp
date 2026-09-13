#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for(int i = (a); i < (b); i++)
#define rep(i, n) For(i, 0, n)
#define rFor(i, a, b) for(int i = (a); i >= (b); i--)

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int MX = 210;
    const int e = -1;
    vector<int> A(MX, e);

    auto debug = [&]() {
        int l = 0;
        while (true) {
            while (A[l] == e) l++;
            if (l == MX) break;
            int r = l + 1, x = A[l];
            while (r < MX && A[r] == x) {
                r++;
            }
            cout << "[" << l << ", " << r << "):" << x << " ";
            l = r;
        }
        cout << "\n";
    };

    int Q;
    cin >> Q;
    while (Q--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        if (t == 1) {
            cin >> x;
            For(i, l, r) {
                A[i] = x;
            }
        } else {
            For(i, l, r) {
                A[i] = e;
            }
        }
        int ans = 0;
        rep(i, MX) {
            if (A[i] != e) ans++;
        }
        cout << ans << "\n";
        debug();
    }
}
