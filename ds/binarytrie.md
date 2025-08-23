## 概要
- 非負整数の集合を Trie 木で管理するデータ構造
- 平たく言うと k 番目の値を取得できる `std::set`
- すべての要素をある数と xor したやつに変える, という操作もできる

## 注意
- 存在しない要素を `erase` すると壊れる
- `lower`, `upper` はインデックスを返す
  - `int i = std::lower_bound(v.begin(), v.end(), x) - v.begin();` みたいな感じ
