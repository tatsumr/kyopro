# Fenwick Tree

## 概要
Fenwick Tree（Binary Indexed Tree）

## 使い方
### sum
```cpp
T sum(int l, int r)
```
`a[l] + a[l+1] + ... a[r-1]` を返す。

### lower_bound
```cpp
int lower_bound(T w)
```
`sum(0, i)` が `w` 以上となる最小の `i` を返す。`sum(0, n)` が `w` 未満の場合は `n+1` を返す。
