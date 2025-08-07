## 概要
- グラフ. CSR 形式にしているので, vector<vector< Edge >> より高速.
  [参考（11枚目）](https://drive.google.com/file/d/1JwPJ8OErgCqO_MjAYijNgS-fJ7AFVa8Q/view)
- 一度構築したら, もう辺は追加できない（ゆえに StaticGraph）.

## 使い方
- `StaticGraph<T> g(N)` : 辺のコストの型が `T`, 頂点数が `N` のグラフを作る.
  - ただ宣言しただけで, `build` しないと使えない.
- `void build()` : グラフを構築する.
  - これを呼んだ後に `add` を呼ぶと assert に引っかかる.
- `g[v], g[v][i]` : vector<vector< Edge >> と同じように使える.
  - `build` していない状態で呼ぶと assert に引っかかる.
