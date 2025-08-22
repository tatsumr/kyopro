## 概要
- k 番目の値を取得できる std::set. ただし 0 以上の整数しか扱えない.
- すべての要素をある数と xor したやつに変える, という操作もできる

## 注意
- 存在しない要素を `erase` すると壊れる
- `lower`, `upper` はインデックスを返す
  - `int i = std::lower_bound(v.begin(), v.end(), x) - v.begin();` みたいな感じ
