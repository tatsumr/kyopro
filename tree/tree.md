# Tree

## 概要
根付き木に関する様々な情報（LCAや頂点間の距離など）を知りたい時に使える。

## 使い方
### コンストラクタ
```cpp
Tree(StaticGraph<T> g, int root = 0)
```
[Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.cpp) `g` 、根の頂点番号 `root` で構築。

### lca
```cpp
int lca(int u, int v)
```
`u` と `v` の LCA（最小共通祖先）を返す。

### la
```cpp
int la(int u, int k)
```
`u` の `k` 個上の祖先の頂点番号を返す（Level Ancestor）。（ `k=0` なら `u` 自身、 `k=1` なら `u` の親）

### jump
```cpp
int jump(int u, int v, int i)
```
`u` - `v` パスを $x_0, x_1, ..., x_k$ としたときの $x_i$ を返す。`i` が $k$ より大きい時は `-1` を返す。0-indexed であることに注意。
- "jump" は [Library Checker](https://judge.yosupo.jp/problem/jump_on_tree) で Jump on Tree と名付けられていることに由来する。
