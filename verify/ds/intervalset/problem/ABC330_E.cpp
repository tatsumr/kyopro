// https://atcoder.jp/contests/abc330/tasks/abc330_e
#include <bits/stdc++.h>
using namespace std;

// Interval Set

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    unordered_map<int, int> mp;
    IntervalSet<int, int, -1> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
        s.insert(a[i]);
    }
    while (q--) {
        int i, x;
        cin >> i >> x;
        i--;
        mp[a[i]]--;
        if (mp[a[i]] == 0) {
            s.erase(a[i]);
        }
        a[i] = x;
        mp[a[i]]++;
        s.insert(a[i]);
        cout << s.mex() << endl;
    }
}
