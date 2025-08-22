## 概要
- マージ時に頂点の値の集約値も求めてくれる UF
- 連結成分の最大値とか和とか知りたいときに使える
- 演算は可換じゃないといけない

## 使い方
- `UnionFindSemigroup<S, op, inv> uf(d)`
  - 値の型 `S`
  - 二項演算 `op`（可換）
  - 逆元があるか？が `inv`
  - 各頂点の値の初期配列 `d`
- `void set(int a, S x, F inv_op)`
  - 頂点 `a` の値を `x` に変更
  - 集約値 `sum` から `val` を取り消す演算 `S inv_op(S sum, S val)` を渡す
  - 宣言時の `inv` が false だと assert に引っかかる
