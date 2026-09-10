## 概要
- Undo 可能 Union Find
- 経路圧縮をしない代わりに, 最新のマージ操作を取り消すことができる（その分, 計算量は通常の Union Find より悪化する）

## 使い方
- `merge`, `same`, `leader`, `size` : $O(\log N)$ （ $N$ は頂点数）
- `void undo()` : $O(1)$
- `vector<vector<int>> groups()` : $O(N \log N)$

## 仕組み
- `merge` 呼び出しによって変更が起こる部分の, 変更前の状態を stack に保存し, `undo` が呼ばれたら stack からそれを取り出して変更前の状態に戻す.
- 具体的には, `merge(a, b)` で変更が起こるのは `par[aの根]` と `par[bの根]`.
- よって `merge(a, b)` が呼ばれたら整数の組(`a`, `par[aの根]`) と (`b`, `par[bの根]`) を stack に入れる. その後 `par[aの根]` と `par[bの根]` を更新.
- `undo()` が呼ばれたら stack の上 2 つを取り出して, マージする前の状態を再現.
