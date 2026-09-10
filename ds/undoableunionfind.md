# Undo-able Union Find

## 概要
- Undo 可能 Union Find
- 経路圧縮をしない代わりに、最新のマージ操作を取り消すことができる（その分計算量は通常の Union Find より悪化する）。

## 使い方
### merge, same, leader, size, groups
```cpp
int merge(int a, int b)
bool same(int a, int b)
int leader(int a)
int size(int a)
vector<vector<int>> groups()
```
通常の Union Find と同じ。
#### 計算量
`groups` のみ $O(N \log N)$ 、それ以外 $O(\log N)$

### undo
```cpp
void undo()
```
最新の `merge` 操作を取り消す。取り消すべき `merge` 操作がなかった場合は何も起こらない（エラーにはならない）。
#### 計算量
$O(1)$

## 仕組み
- `merge` によって変更が起こる部分の、変更前の状態を stack に保存し、`undo` が呼ばれたら stack からそれを取り出して変更前の状態に戻す。
- 具体的には、`merge(a, b)` で変更が起こるのは `par[aの根]` と `par[bの根]`。
- よって `merge(a, b)` が呼ばれたら整数の組(`a`, `par[aの根]`) と (`b`, `par[bの根]`) を stack に入れる。その後 `par[aの根]` と `par[bの根]` を更新。
- `undo()` が呼ばれたら stack の上 2 つを取り出して、マージする前の状態を再現。
