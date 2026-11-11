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
- 部分木の集約値どうしを集約する関数 `merge`
- 辺のコストなどを追加する関数 `add_edge`
- 子の部分木の集約値たちを集約した後、親頂点の情報を追加する関数 `add_node`
- `merge` の単位元 `id`
- [Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 

## 使用例
### [EDPC-V](https://atcoder.jp/contests/dp/tasks/dp_v)
