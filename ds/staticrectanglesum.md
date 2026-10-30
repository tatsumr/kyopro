# Static Rectangle Sum
コード: [ds/staticrecranglesum.cpp](https://github.com/tatsumr/kyopro/blob/main/ds/staticerctanglesum.cpp)

## 概要
こんな問題が解ける:

xy平面上に $N$ 個の点がある。以下のクエリに答えよ:

- $l$, $r$, $d$, $u$ が与えられる。 $[l, r) \times [d, u)$ の矩形領域上に点はいくつあるか。

## 計算量
`add_point`: $O(1)$
`build`: $O(N \log N + NH)$
`query`: $O(\log N + H)$ ($H$ は座標の最大値のビット長)

## 解法
前準備として以下を行う:
- 点を x 座標の昇順にソートする。
- ソート後の各座標の列をそれぞれ $X$, $Y$ とする。
- $Y$ を Wavelet Matrix に乗せる。

クエリは以下の手順で解く:
- $X$ において、「 $l$ 以上の値が初めて登場するのは何番目か」と「 $r$ 以上の値が初めて登場するのは何番目か」を二分探索で求める。
- $Y$ において、上で求めたインデックスの範囲 (半開区間) 内で $d$ 以上 $u$ 未満の要素の個数を Wavelet Matrix を用いて求める。

## クエリの途中で点の追加がある場合
領域木や二次元 Fenwick Tree を使おう

## 使用例
### [ABC453-E](https://atcoder.jp/contests/abc453/tasks/abc453_e) の部分問題 [提出](https://atcoder.jp/contests/abc453/submissions/74936804)
$N$ 個の区間 $[L_1, R_1), [L_2, R_2), ..., [L_N, R_N)$ がある。整数 $x$ と $y$ が与えられるので、「 $x$ と $y$ をともに含む区間の個数」「 $x$ のみを含む区間の個数」「 $y$ のみを含む区間の個数」を求めよ。

（もとの問題風に言うと、選手 $i$ は $[L_i, R_i)$ 内にある人数のチームに入ることができる。チームAが $x$ 人、チームBが $y$ 人のとき、AとBの両方に / Aのみ / Bのみ に入れる選手はそれぞれ何人いるか。）

- 以下、 $x < y$ とする。
- 例えばともに含む区間の個数は「 $L_i \le x$ かつ $y \lt R$ をみたす $i$ の個数」といえる。
- そこで、xy平面上に $N$ 個の点 $(L_i, R_i)$ をプロットする。
- そうすると、ともに含む区間の個数は $[-\infty, x+1) \times [y, \infty)$ の矩形領域上の点の個数となる。
