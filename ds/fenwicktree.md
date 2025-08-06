## 概要
Fenwick Tree（Binary Indexed Tree）

## 使い方
- `T sum(l, r)` : $\Sigma a_i (l \leq i \lt r)$ を返す.
- `int lower_bound(w)` : `sum(0, i)` が $w$ 以上となる最小の $i$ を返す. `sum(0, n)` が $w$ 未満の場合は $n+1$ を返す.
