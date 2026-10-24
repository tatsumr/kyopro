# Treap Set
## 概要
平衡二分探索木（Treap）で順序付き集合を管理する。 $k$ 番目に小さい要素の取得もできる。

似たようなことができるデータ構造に対する差別化としては、
- [64分木](https://github.com/tatsumr/kyopro/blob/main/ds/fastset.cpp) と違い、 $k$ 番目に小さい要素の取得ができる。また、非負整数以外の集合も扱える。
- [Binary Trie](https://github.com/tatsumr/kyopro/blob/main/ds/binarytrie.cpp) と違い、非負整数以外の集合も扱える。
- [Offline Set](https://github.com/tatsumr/kyopro/blob/main/ds/offlineset.cpp) と違い、挿入する要素を事前に知る必要がない。

一方でこちらの方がおそらく速度が遅い（ $O( \log N)$ 時間で処理できるが、定数倍が重いと思われる）ので注意。

## 使い方
### コンストラクタ
```cpp
TreapSet<T, bool multi = false>(T none, int capacity = 0)
```
集合の要素の型 `T`、重複を許すかどうかを表す `multi`、無効値 `none` 、集合のサイズの上限 `capacity` で初期化。
- `capacity` を宣言することで内部ではノード配列の `reserve` が呼ばれるため、配列の再確保のコストが抑えられるというメリットがある。
- `capacity = 0` でコンストラクトしたり、途中で集合が `capacity` を超えるサイズになったりしてもエラーは生じない。

### insert
### erase
```cpp
void erase(T x)
```
要素 `x` を削除する。重複を許す集合では、`x` が1つだけ削除される。集合に `x` が存在しない状態で `erase(x)` を呼んでもエラーは生じない。

### count
```cpp
bool count(T x)
```
値 `x` が含まれるかどうか判定。現状、重複を許す集合でも個数ではなく true or false を返す仕様になっている。

### gt, ge, lt, le
```cpp
pair<T, int> gt(T x)
pair<T, int> ge(T x)
pair<T, int> lt(T x)
pair<T, int> le(T x)
```
`x` より大きい / 以上 / より小さい / 以下の要素の中で最小 / 最大のものの {値, インデックス} を返す。インデックスは 0-indexed。そのような要素がなければ `{none, n}` を返す。ただし `n` はその時点での要素数。

重複を許す集合で、条件をみたす要素が複数ある場合は、境界に最も近いものが選ばれる。

例えば集合が $\lbrace 0, 0, 0, 2, 2, 2 \rbrace$ のときは以下のような挙動を示す。
- `gt(0) = {2, 3}` (0 0 0 | 2 2 2)
- `ge(0) = {0, 0}` (| 0 0 0 2 2 2)
- `lt(2) = {0, 2}` (0 0 0 | 2 2 2)
- `le(2) = {2, 5}` (0 0 0 2 2 2 |)
### operator[]
### size
### empty
