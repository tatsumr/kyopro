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
- 原点 $(0,~0)$ は存在しない前提で組まれている。存在する場合の挙動は未調査
- 偏角が等しい点の並び順は予測不可能。
#### 仕組み
- 参考: [ABC442-E の解説](https://atcoder.jp/contests/abc442/editorial/15136)
- ベクトル $\overrightarrow{a},~\overrightarrow{b}$ の外積 $\overrightarrow{a} \times \overrightarrow{b}$ の正負は、 $\overrightarrow{a}$ から $\overrightarrow{b}$ へ $180 \degree$ 以内で回るときの向き(時計回り or 反時計回り or 同一直線上)を表している
- よって基本的には $\overrightarrow{a} \times \overrightarrow{b} \gt 0$ のときは $a$ → $b$ の順に並べるとよい
- ただ、例えば $\overrightarrow{b}$ の偏角が $350 \degree$ 、 $\overrightarrow{a}$ の偏角が $10 \degree$ のときのように $0 \degree$ をまたぐとうまくいかない
- そこで、点を上下の半平面で分けてから比較する
