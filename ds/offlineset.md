## 概要
- k 番目の値を取り出せる set, multiset
- ただし insert する要素が事前に分かっている必要がある（その分, 平衡二分探索木より速い）
- 座標圧縮 + Fenwick Tree

## 使い方
- `OfflineSet<T, multi>(a, none)`
  - 型 `T`
  - 重複を許すかどうかが `multi` （デフォルトは false, つまり std::set みたいな感じ）
  - insert する要素が入った配列が `a`
  - 無効値が `none`（値を検索する関数で, 値がなかった場合にこれを返す）
- `int count(T x)` : x の個数. true or false の存在判定ではない
- `pair<T, int> ge(T x) / gt(T x) / le(T x) / lt(T x)`
  - `x` 以上 / より大きい / 以下 / より小さい 要素の中で 最小 / 最小 / 最大 / 最大 のものの {値, インデックス} を返す
  - そのような要素がないときは {none, n} を返す（n はその時点での要素数）
