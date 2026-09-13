# Interval Set

## 概要
区間と値を set で管理するデータ構造。コードの中身についての説明は [intervalset_implemention.md](https://github.com/tatsumr/kyopro/blob/main/ds/intervalset_implemetion.md) に書いた。

## 使い方
### コンストラクタ
```cpp
IntervalSet<S, T, e>
```
区間の型 `S`、値の型 `T`、値の初期値 `e` で初期化。

### covered
```cpp
bool covered(S l, S r)
bool covered(S x)
```
区間 `[l, r)` 、値 `x` （=区間 `[x, x+1)` ）が完全に set に含まれているか判定。

### get
```cpp
auto get(S l, S r)
auto get(S x)
```
これが使われる状況として想定しているのは、区間 `[l, r)` や値 `x` が含まれる区間のイテレータを得たいとき。そのような区間がない場合は `[l, r)` や `x` を超えない区間の中で最大（最右）のもののイテレータを返す。

### insert
```cpp
void insert(S l, S r, T x, ADD add, DEL del)
```
半開区間 `[l, r)` の値を `x` にする。区間を新たに追加する度に `add`、区間を消去する度に `del` が呼ばれる。
- 例えば $[2, 5)=1$ のときに `insert(3, 8, 2, add, del)` を呼ぶと $[2, 3)=1, [3, 8)=2$ となる。処理の中で `del(2, 5, 1)`、`add(2, 3, 1)`、`add(3, 8, 2)`が呼ばれる。
- 区間更新の遅延セグ木のようなイメージ。
#### 計算量
多分、償却 $O(\log n)$（ $n$ は区間の個数）

### erase
```cpp
void erase(S l, S r, ADD add, DEL del)
```
半開区間 `[l, r)` を削除する。区間を新たに追加する度に `add`、区間を消去する度に `del` が呼ばれる。
- 例えば $[2, 5)=1, [8, 10)=3$ のときに `erase(4, 9, add, del)` を呼ぶと $[2, 4)=1, [9, 10)=3$ となる。処理の中で `del(2, 5, 1)`、`add(2, 4, 1)`、`del(8, 10, 3)`、`add(9, 10, 3)` が呼ばれる。

### size
```cpp
int size()
```
set に入っている区間の個数を返す（set には実装の都合で番兵が 2 つあるが `size()` には含まれない）。

### mex
```cpp
S mex(S x = 0)
```
set に入っていない `x` 以上の整数の最小値を返す。
