# Static Graph

## 概要
- グラフ。CSR 形式にしているので、`vector<vector<Edge>>`より高速。
  [参考（11枚目）](https://drive.google.com/file/d/1JwPJ8OErgCqO_MjAYijNgS-fJ7AFVa8Q/view)
- 一度構築したら、もう辺は追加できない（ゆえに "Static"Graph）。

## 使い方
### コンストラクタ
```cpp
StaticGraph<T> g(int n)
```
辺のコストの型が `T`、頂点数が `n` のグラフを作る。ただ宣言しただけで、`build`を呼ばないと使えない。

### add
```cpp
(1) void add(int u, int v)
(2) void add(int u, int v, T w)
(3) void add(int u, int v, T w, int i)
```
頂点 `u` から頂点 `v` に重さ `w`、辺番号 `i` の辺を張る。
#### 制約
- $0 \leq u, v < n$
- `build`を呼んだ後にこれを呼んではいけない。

### build
```cpp
void build()
```
グラフを構築する。
#### 制約
- これを呼んだ後に `add` を呼んではいけない。

### オペレーター[]
```cpp
g[v], g[v][i]
```
`vector<vector<Edge>>`と同じように使える。
#### 制約
- $0 \leq v < n$
- `build` していない状態で呼んではいけない。
- 頂点 0 から辺が 2 本しか出てないのに `g[0][10]` を呼んだ場合の挙動...未調査（多分 `std::vector` の配列外参照と同じ）
