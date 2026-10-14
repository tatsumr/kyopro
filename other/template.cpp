// library: https://github.com/tatsumr/kyopro
#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for(int i = (a); i < (b); ++i)
#define rep(i, n) For(i, 0, n)
#define rFor(i, a, b) for(int i = (a); i >= (b); --i)
#define ALL(v) (v).begin(), (v).end()
#define rALL(v) (v).rbegin(), (v).rend()
#define SZ(v) ((int)(v).size())

using lint = long long;
using ld = long double;

const int INF = 1001001001;
const lint LINF = 4004004003094073385LL;
// 真上から反時計回り
const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, -1, 0, 1};
const int di8[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dj8[] = {0, -1, -1, -1, 0, 1, 1, 1};

struct SetupIo {
    SetupIo() {
        ios::sync_with_stdio(false); cin.tie(nullptr);
        cout << fixed << setprecision(15);
        cerr << fixed << setprecision(15);
    }
} setupio;

namespace tatsumr {

template <class T>
bool chmin(T &a, const T &b) {
    return a > b ? a = b, 1 : 0;
}
template <class T>
bool chmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0; 
}
template <class T>
T div_floor(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a >= 0 ? a / b : (a + 1) / b - 1);
}
template <class T>
T div_ceil(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a > 0 ? (a - 1) / b + 1 : a / b);
}
template <class T>
T mypow(T a, T b) {
    T res = 1;
    while (b) {
        if (b & 1) { res *= a; }
        a *= a; b >>= 1;
    }
    return res;
}
template <class T>
T modpow(T a, T b, T mod) {
    T res = 1;
    while (b) {
        if (b & 1) { res = (res * a) % mod; }
        a = (a * a) % mod; b >>= 1;
    }
    return res;
}

} // namespace tatsumr

using namespace tatsumr;

int main() {
    
}
