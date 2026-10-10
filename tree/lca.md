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

### 参考資料
- [AALのオイラーツアーテクニックの記事](https://info.atcoder.jp/entry/algorithm_lectures/euler_tour_technique)
- [AALのスパーステーブルの記事](https://info.atcoder.jp/entry/algorithm_lectures/sparse_table)

### 実装メモ
ライブラリ作成時に自分が詰まった点を備忘録としてメモしておく。
- 頂点列は行きがけ順じゃダメ？
  - `1-0-2` という木（根は0）だと行きがけ順は `{0, 1, 2}`。 1 と 2 の LCA が知りたいとき...？
- 頂点列の長さはどうなる？
  - $N$ 回の訪問 + それぞれの親へ戻る訪問（ $N-1$ 回）で、計 $2N-1$
- `while (1 << (K + 1) <= M) K++;` は何をしている？
  - $2^K<=M$ を満たす最大の $K$ を求めている。
- `int sz = M - (1 << k) + 1; table[k].resize(sz);` は何をしている？
  - $table[k][i] := [i, i+2^k)$ における集約値なので、 $0 \leq i \leq M-2^k$ が成り立つ。
  - よって `table[k]` のサイズは $(M-2^k)-0+1$ でよい。
- Sparse Table には何を乗せている？
  - 頂点番号を乗せている。ただし比較の際はそれぞれの頂点の深さを見ている。
- `31 - __builtin_clz(R - L)` は何をしている？
  - `__builtin_clz(x)` は `x` が最上位ビット（つまり $2^{31}$ の位）から数えて 0 が何個連続するかを返す関数。 $x=0$ なら $32$ 、 $x=6$ なら $29$ が返ってくる。
  - つまり $2^i (32-clz \leq i \lt 32)$ の位は 0 なので初めて $1$ が登場するのは $2^{31-clz}$ の位。
