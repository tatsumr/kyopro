# Sparse Table
## 概要
更新のない列に対する区間クエリ（min や gcd など）を高速に処理するデータ構造。冪等なモノイドを乗せることができる。

実装に関するメモは、 [tree/lca.md](https://github.com/tatsumr/kyopro/blob/main/tree/lca.md) に書かれている。

## 使い方
### コンストラクタ
```cpp
SparseTable<S, op, e>(vector<S> A)
```
型 `S` 、二項演算 `S op(S a, S b)` 、単位元 `e()`、列 `A` で構築する。
#### 計算量
`A` の長さを $N$ として、 $O(N \log N)$

### prod
```cpp
S prod(int l, int r)
```
半開区間 $A_l,~A_{l+1},~A_{r-1}$ の区間クエリに答える。 $l=r$ のときは `e()` を返す。
#### 制約
$0 \le l \le r \le N$
#### 計算量
$O(1)$
