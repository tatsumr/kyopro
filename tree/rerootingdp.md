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
- 部分木の集約値どうしを集約する関数 `T merge(T a, T b)`
- 辺のコストなどを追加する関数 `T add_edge(Edge<E> e, T a)`
- 子の部分木の集約値たちを集約した後、親頂点の情報を追加する関数 `T add_node(int v, T a)`
- `merge` の単位元 `T id()`
- [Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 

$dp_v := 頂点vの部分木に関するDPの値$ とすると、 $dp_v$ は `add_edge` → `merge` → `add_node` の順に関数が適用されて求まるとイメージである。

## 使用例
### [EDPC-V](https://atcoder.jp/contests/dp/tasks/dp_v)
