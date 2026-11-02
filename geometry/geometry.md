# 幾何

## 使い方
### Point
```cpp
Point<T>(T x, T y)
```
点 $(x,~y)$ を作る。

### cross
```cpp
T cross(Point<T> a, Point<T> b)
```
`a` と `b` の外積 $a_x b_y - a_y b_x$ を返す。

### argument_sort
```cpp
void argument_sort(vector<Point<T>>)
```
点列 `ps` を偏角ソートする。 $x$ 軸の正の方向からの偏角が小さい順に点が並ぶようにする。
#### 注意点
- 原点 $(0,~0)$ は存在しない前提で組まれている。ある場合の挙動は未調査
- 偏角が等しい点の並び順は予測不可能。
#### 仕組み
[こちら](https://atcoder.jp/contests/abc442/editorial/15136)を参考にした。ベクトル $\overrightarrow{a}$ 外積 $a
