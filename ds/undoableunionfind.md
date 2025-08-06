## 概要
- Undo 可能 Union Find
- 経路圧縮をしない代わりに, 最新のマージ操作をなかったことにできる

## 使い方
- `merge`, `same`, `leader`, `size` : $O(\log N)$
- `void undo()` : $O(1)$
