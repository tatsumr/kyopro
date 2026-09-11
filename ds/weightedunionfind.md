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
![WeightedUnionFind](https://github.com/user-attachments/assets/0c506867-3050-4ec5-b93b-41e158a77922)
