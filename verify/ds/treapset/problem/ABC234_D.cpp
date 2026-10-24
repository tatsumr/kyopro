// https://atcoder.jp/contests/abc234/tasks/abc234_d
// library: https://github.com/tatsumr/kyopro
#include <bits/stdc++.h>
using namespace std;

// Treap Set


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }
    TreapSet<int> st(-1, N);
    for (int i = 0; i < K - 1; ++i) {
        st.insert(P[i]);
    }
    for (int i = K - 1; i < N; ++i) {
        st.insert(P[i]);
        cout << st[st.size() - K] << "\n";
    }
}
