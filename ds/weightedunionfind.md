# Weighted Union Find

## 概要
重み（ポテンシャル）付き Union Find

## 使い方
### merge
```cpp
int merge(int x, int y, T z)
```
`y` の重さ = `x` の重さ + `w` となるように `x` と `y` をマージする。マージ後の根を返す。

### diff
```cpp
T diff(int x, int y)
```
(`y` の重さ - `x` の重さ) を返す。

## 仕組み
![WeightedUnionFind](https://github.com/user-attachments/assets/2190eb37-7f99-470b-a165-f66338a81da1)
