# Tree
コード: [tree/tree.cpp](https://github.com/tatsumr/kyopro/blob/main/tree/tree.cpp)

## 概要
根付き木に関する様々な情報（LCAや頂点間の距離など）を知りたい時に使える。内部では BFS とダブリングをしている。

## 使い方
以下、木の頂点数を $N$ とする。

### コンストラクタ
```cpp
Tree(StaticGraph<T> g, int root = 0)
```
[Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 、根の頂点番号 `root` で構築する。
#### 制約
$0 \le root \lt N$
#### 計算量
$O(N \log N)$

### lca
```cpp
int lca(int u, int v)
```
`u` と `v` の LCA（最小共通祖先）を返す。
#### 制約
$0 \le u,~v \lt N$
#### 計算量
$O(\log N)$

### la
```cpp
int la(int v, int k)
```
`v` の `k` 個上の祖先の頂点番号を返す（Level Ancestor）。（ `k=0` なら `v` 自身、 `k=1` なら `v` の親）

`k` 個上の祖先が `root` より上の場合は、 `root` を返す。
#### 制約
- $0 \le v \lt N$
- $k \ge 0$
#### 計算量
$O(\log N)$
- ただし `k` 個上の祖先が `root` より上の場合は早期終了するので $O(1)$

### jump
```cpp
int jump(int u, int v, int i)
```
`u` - `v` パスを $x_0, x_1, ..., x_k$ としたときの $x_i$ を返す。`i` が $k$ より大きい時は `-1` を返す。0-indexed であることに注意。
- "jump" は [Library Checker](https://judge.yosupo.jp/problem/jump_on_tree) で Jump on Tree と名付けられていることに由来する。
#### 制約
- $0 \le u,~v \lt N$
- $i \ge 0$
#### 計算量
$O(\log N)$

### dist, par, dep
```cpp
int dist(int u, int v)
int par(int v)
int dep(int v)
```
- `dist(u, v)` は `u` と `v` の距離を返す。
- `par(v)` は `v` の親の頂点番号を返す。
- `dep(v)` は `v` の深さを返す。根の深さは $0$ である。
#### 制約
$0 \le u,~v \lt N$
#### 計算量
- `dist`: $O(\log N)$
- `par`, `dep`: $O(1)$
