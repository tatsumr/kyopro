# Union Find Semigroup

## 概要
Union Find の亜種。頂点に重みがあるときに、連結成分の集約値（和や最大値など）を求めることができる。可換な半群を乗せることができる。

## 使い方
### コンストラクタ
```cpp
UnionFindSemigroup<S, op, inv> uf(d)
```
値の型 `S`、二項演算 `op`（可換）、逆元があるか？が `inv`、各頂点の重みの初期配列 `d` で初期化。
- `inv` は下で述べる `set` でエラーを検出するために用意している。

### merge, same, leader, size, groups
```cpp
int merge(int a, int b)
bool same(int a, int b)
int leader(int a)
int size(int a)
vector<vector<int>> gourps()
```
通常の Union Find と同じ。

### prod, get
```cpp
S prod(int a)
S get(int a)
```
- `prod(a)` は頂点 `a` が属する連結成分の頂点たちの重みの集約値を返す。
- `get(a)` は頂点 `a` の重みを返す。

### set
```cpp
(1)void set(int a, S x, F inv_op)
(2)void set(int a, S x)
```
(1)頂点 `a` の重みを `x` に変更する。集約値 `sum` から `val` を取り消す演算 `S inv_op(S sum, S val)` を渡す。

(2)演算が和のときの `set` は予め用意されているので、`uf.set(a, x);` とすればよい。ちなみに、内部では以下のような `inv_op` が定義されている。
```cpp
auto inv_op = [&](S rx, S x) {
    return rx - x;
};
```
#### 注意
- 宣言時の `inv` が `false` だと assert 関数に引っかかる。
- 現状の実装ではコンストラクタの引数である配列を参照渡しにしているので、引数にしたもとの配列の値が書き換わる。
