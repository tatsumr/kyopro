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

$dp_v := 頂点~v~の部分木に関するDPの値$ とすると、 $dp_v$ は `add_edge` → `merge` → `add_node` の順に関数が適用されて求まるイメージである。
- $v$ の子を $c_1,c_2,...,c_k$ とする。
- $dp_c_i$ に、辺 $e_i(v,~c_i)$ の情報を追加する。
  - $x_i = add_edge(e_i, dp_c_i)$
- 各子の情報を統合する。
  - $y = merge(x_1,x_2,...,x_k)$
- 統合した値に頂点 $v$ の情報を追加する。
  - $dp_v = add_node(v, y)$

## 使用例
### [EDPC-V. Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)
