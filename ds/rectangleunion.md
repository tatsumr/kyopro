## 概要

## 注意
- atcoder::lazy_segtree が必要.
- 2 通りの初期化（宣言）の仕方
  - 長方形を `add` -> `build` -> `get`
  - 長方形の入った配列 `vector<tuple<lint, lint, lint, lint>>` で宣言 -> `get`
- 長方形は閉区間. すなわち `add(l, r, d, u)` は $l \leq x \leq r, d \leq y \leq u$ をみたす長方形を追加.

## 仕組み
