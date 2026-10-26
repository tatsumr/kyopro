# Fast Set
## 概要
非負整数の集合を管理するデータ構造。`std::set`より高速に動作する。

## 使い方
### コストラクタ
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

## insert, erase
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
