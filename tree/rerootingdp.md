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
- 辺のコストなどを追加する関数 `T add_edge(Edge<E> e, T a)`
- 子の部分木の集約値たちを統合した後、親頂点の情報を追加する関数 `T add_node(int v, T a)`
- `merge` の単位元 `T id()`
- [Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 

$f(v) := 頂点vの部分木に関するDPの値$ とすると、 $f(v)$ は `add_edge` → `merge` → `add_node` の順に関数が適用されて求まるイメージである。
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
$dp_{v,~i}:= 頂点vからi番目に出ている辺の先にいる頂点の部分木に関するDPの値$ 。辺の情報は含まれていない。

## 使用例
### [EDPC-V. Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)
### [ABC222-F. Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f)
### [ABC160-F. Distributing Integes](https://atcoder.jp/contests/abc160/tasks/abc160_f)
### [AB361-E. Tree and Hamilton Path 2](https://atcoder.jp/contests/abc361/tasks/abc361_e)
### [Library Checker. Tree Path Composite Sum](https://judge.yosupo.jp/problem/tree_path_composite_sum)
