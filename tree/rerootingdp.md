# Rerooting DP
コード: [tree/rerootingdp.cpp](https://github.com/tatsumr/kyopro/blob/main/tree/rerootingdp.cpp)

## 概要
全方位木DPの抽象化ライブラリ。

## 使い方
### コンストラクタ
```cpp
RerootingDP<T, E, merge, add_edge, add_node, id> rd(StaticGraph<T> g)
```
DPテーブルを構築する。
- DPテーブルの値の型 `T`
- グラフの辺のコストの型 `E`
- 子の集約値どうしを統合する関数 `T merge(T a, T b)`
- 辺のコストなどを追加する関数 `T add_edge(Edge<E> e, T x)`
- 子の部分木の集約値たちを統合した後、親頂点の情報を追加する関数 `T add_node(int v, T x)`
- `merge` の単位元 `T id()`
- [Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 

根を固定して、 $f(v) :=$ 頂点 $v$ の部分木に関するDPの値 とすると、 $f(v)$ は `add_edge` → `merge` → `add_node` の順に関数が適用されて求まるイメージである。
- $v$ の子を $c_1,c_2,...,c_k$ とする。
- $f(c_i)$ に、辺 $e_i(v,~c_i)$ の情報を追加する。
  - $x_i = \verb|add_edge|(e_i, f(c_i))$
- 各子の情報を統合する。
  - $y = \verb|merge|(x_1,x_2,...,x_k)$
- 統合した値に頂点 $v$ の情報を追加する。
  - $f(v) = \verb|add_node|(v, y)$

#### 計算量
木の頂点数を $N$ として $O(N)$ (`merge`, `add_edge`, `add_node`, `id` の計算量を $O(1)$ と仮定)
 
### get
```cpp
T get(int v)
```
頂点 `v` を根としたときのDPの値を返す。
#### 計算量
`v` の次数を $deg(v)$ として $O(deg(v))$ (`merge`, `add_edge`, `add_node`, `id` の計算量を $O(1)$ と仮定)

### メンバ変数 dp
```cpp
vector<vector<T>> dp
```
$dp[v][i]:=$ 頂点 $v$ から $i$ 番目に出ている辺の先にいる頂点の部分木に関するDPの値。辺の情報は含まれていない。

## 使用例
どんな関数を乗せるかは、一旦根を1つ決めて、 $f(v):=v$ の部分木に関するDPの値 という普通の木DPを考えると分かりやすい。

### 木の直径
```cpp
using T = long long;
using E = long long;
T merge(T a, T b) { return max(a, b); }
T add_edge(Edge<E> e, T x) { return x + e.cost; }
T add_node(int v, T x) { return x; }
T id() { return 0; }

int main() {
    RerootingDP<T, E, merge, add_edge, add_node, id> rd(g);
    T diameter = 0;
    for (int i = 0; i < g.size(); i++) {
        diameter = max(diameter, rd.get(i));
    }
}
```
木の直径(最長パスの長さ)を全方位木DPで求めるとこのようになる。

### [EDPC-V. Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)
```cpp
lint N, M;

using T = long long;
using E = long long;
T merge(T a, T b) { return (a * b) % M;}
T add_edge(Edge<E> e, T x) { return (x + 1) % M; }
T add_node(int v, T x) { return x; }
T id() { return 1; }

int main() {
    RerootingDP<T, E, merge, add_edge, add_node, id> rd(g);
    for (int i = 0; i < N; i++) {
        cout << rd.get(i) << "\n";
    }
}
```
$f(v):= v$ の部分木について、 $v$ が黒色のときの通り数 とすると、部分木どうしのマージは掛け算すればよい。ただし、 $v$ の部分木の頂点が全部白色の場合も考慮する必要があるので、 `add_edge` の部分で +1 しておく。

### [ABC222-F. Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f)
```cpp
const int MX = 200010;
long long D[MX];

using T = long long;
using E = long long;
T merge(T a, T b) { return max(a, b);}
T add_edge(Edge<E> e, lint x) { return x + e.cost; }
T add_node(int v, T x) { return max(x, D[v]); }
T id() { return 0; }

int main() {
    RerootingDP<T, E, merge, add_edge, add_node, id> rd(g);
    for (int v = 0; v < N; v++) {
        T ans = id();
        for (int i = 0; i < g[v].size(); i++) {
            ans = merge(add_edge(g[v][i], rd.dp[v][i]), ans);
        }
        cout << ans << "\n";
    }
}
```
$f(v):= v$ の部分木について、 $v$ を始点としたときの旅費の最大値(ただし $v$ が終点の場合も含む) とすると、各始点に対する答えは main 関数内で上のような処理をすることで求められる。 `get(v)` を呼ぶと `add_node(v)` が適用されて $D[v]$ が非常に大きい場合に $v$ が始点かつ終点の場合が答えになってしまう点に注意。

### [ABC160-F. Distributing Integes](https://atcoder.jp/contests/abc160/tasks/abc160_f)
### [Library Checker-Tree Path Composite Sum](https://judge.yosupo.jp/problem/tree_path_composite_sum)
