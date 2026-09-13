# Functional Graph

## 概要
[functional graph](https://atcoder.jp/contests/abc357/editorial/10185) に関する様々な操作ができる。

## 使い方
### コンストラクタ
```cpp
FunctionalGraph(StaticGraph<T> g)
```
[Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.cpp) `g` で初期化。

### cc
```cpp
int cc()
```
連結成分（connected component）の個数を返す。

### root, to_cycle, len_cycle, cycle
```cpp
int root(int v)
int to_cycle(int v)
int len_cycle(int v)
vector<Edge<T>> cycle(int v)
```
頂点 `v` から有向辺を辿っていくと、必ず閉路上のある頂点に到達する（`v` が閉路上にある可能性もあるが）。このとき、
- `root` はその頂点（初めて到達した閉路上の頂点）を返す。`v` が閉路上にあるときは `v` を返す。
  - 別の言い方をすると、functional graph の各連結成分は木の集まりで、木の根たちが閉路をなしているといえる。`root` は頂点 `v` の根を返す。
- `to_cycle` は閉路に到達するまでに通った辺の本数を返す。
- `len_cycle` はその閉路の長さを返す。つまり `v` が属する連結成分に存在する閉路の長さを返す。
- `cycle` はその閉路をなす辺のリストを返す。辺の順番が望み通りになっているとは限らない。

### all_cycles
```cpp
vector<vector<Edge<T>>> all_cycles()
```
全ての連結成分に存在する閉路の辺のリストを返す。

### next
```cpp
int next(int v, long long k)
```
頂点 `v` から辺を `k` 本渡って到達する頂点を返す。

## 仕組み
「入次数が 0 の頂点と、その頂点から出ている辺を消す」ことを繰り返すと、各連結成分で閉路だけが残る。閉路上の適当な頂点から辺を探索すれば、閉路の長さや閉路をなす辺のリストを求めることができる。

次に、逆向きに辺を張ったグラフを用意して閉路上の頂点から辺を辿っていけば、`root` や `to_cycle` にあたる処理もできる。

`next` はダブリングで求める。
$dp[i][j] := 頂点 i から 2^j 個先の頂点$
とすればよい。
