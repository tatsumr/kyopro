# Treap Set
## 概要
平衡二分探索木（Treap）で順序付き集合を管理する。k 番目に小さい要素の取得もできる。

似たようなことができるデータ構造に対する差別化としては、
- [Binary Trie](https://github.com/tatsumr/kyopro/blob/main/ds/binarytrie.cpp) と違い、非負整数以外の集合も扱える。
- [64分木](https://github.com/tatsumr/kyopro/blob/main/ds/fastset.cpp) と違い、k 番目に小さい要素の取得ができる。

## 使い方
### コンストラクタ
```cpp
TreapSet<T, bool multi = false>(none)
```
集合の要素の型 `T`、重複を許すかどうかを表す `multi`、無効値 `none` で初期化。

### insert
### erase
### count
### gt, ge, lt, le
### operator[]
### size
### empty
