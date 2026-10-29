# Fast Set
コード: [ds/fastset.cpp](https://github.com/tatsumr/kyopro/blob/main/ds/fastset.cpp)
解説: [ds/fastset_algorithm.cpp](https://github.com/tatsumr/kyopro/blob/main/ds/fastset_algorithm.md)

## 概要
64分木で非負整数の集合を管理するデータ構造。`std::set`より高速に動作する。

重複を許す集合の管理や、 $k$ 番目に小さい要素の取得はできない。

## 使い方
### コンストラクタ
```cpp
FastSet(int n)
```
0 以上 `n` 未満の集合を管理する `FastSet` を構築する。
#### 計算量
$w=64$ として $O(n/w)$

### count
```cpp
bool count(int x)
```
集合内に `x` が存在するかどうかを判定する。
#### 制約
$0 \le x \lt n$
#### 計算量
$O(1)$

### insert, erase
```cpp
void insert(int x)
void erase(int x)
```
集合から `x` を挿入 / 削除する。挿入したい要素が既に存在していたり、削除したい要素が既に存在しないときは何も起こらない。
#### 制約
$0 \le x \lt n$
#### 計算量
$w=64$ として $O(\log n / \log w)$

### next, prev
```cpp
int next(int x)
int prev(int x)
```
`x` 以上で最小の要素 / `x` 以下で最大の要素を返す。そのような要素がなければ $-1$ を返す。
#### 計算量
$w=64$ として $O(\log n / \log w)$

### min, max
```cpp
int min()
int max()
```
集合内で最小 / 最大の要素を返す。集合が空のときは $-1$ を返す。
#### 計算量
$w=64$ として $O(\log n / \log w)$

### size, empty
```cpp
int size()
bool empty()
```
`size()` は集合の要素の個数を返す。 `empty()` は集合が空かどうかを判定する。
#### 計算量
$O(1)$
