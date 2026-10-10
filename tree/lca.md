# LCA

## 概要
根付き木の最小共通祖先（Lowest Common Ancestor）を Euler Tour + Sparse Table でクエリあたり $O(1)$ で求める。

## 使い方
### コンストラクタ
```cpp
LCA(vector<vector<int>> g, int root = 0)
```
木の隣接リスト `g` 、根 `root` で初期化。`root` は 0-indexed。
#### 計算量
$O(NlogN)$

### query
```cpp
int lca(int u, int v)
```
頂点 `u` と頂点 `v` の LCA の頂点番号を返す。
#### 計算量
$O(1)$

