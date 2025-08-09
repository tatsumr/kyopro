## 概要
- グラフ. CSR 形式にしているので, vector<vector< Edge >> より高速.
  [参考（11枚目）](https://drive.google.com/file/d/1JwPJ8OErgCqO_MjAYijNgS-fJ7AFVa8Q/view)
- 一度構築したら, もう辺は追加できない（ゆえに StaticGraph）.

## 使い方
- `StaticGraph<T> g(int n)` : 辺のコストの型が `T`, 頂点数が `n` のグラフを作る.
  - ただ宣言しただけで, `build` しないと使えない.
- ```
  (1) void add(int u, int v)
  (2) void add(int u, int v, T w)
  (3) void add(int u, int v, T w, int i)
  ```
  - (1) 頂点 `u` から頂点 `v` に辺を張る.
  - (2) 頂点 `u` から頂点 `v` に重さ `w` の辺を張る.
  - (3) 頂点 `u` から頂点 `v` に重さ `w`, 辺番号 `i` の辺を張る.
  - `build` した後にこれを呼ぶと assert に引っかかる.
  - 頂点番号が 0 以上 `n` 未満じゃないと assert に引っかかる.
- `void build()` : グラフを構築する.
  - これを呼んだ後に `add` を呼ぶと assert に引っかかる.
- `g[v], g[v][i]` : vector<vector< Edge >> と同じように使える.
  - `build` していない状態で呼ぶと assert に引っかかる.
