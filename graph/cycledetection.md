# Cycle Detection
コード: [graph/cycledetection.cpp](https://github.com/tatsumr/kyopro/blob/main/graph/cycledetection.cpp)

## 概要
グラフのサイクルを、深さ優先探索を用いて検出する。

## 使い方
### コンストラクタ
```cpp
CycleDetection(StaticGraph g, bool directed)
```
[Static Graph](https://github.com/tatsumr/kyopro/blob/main/graph/staticgraph.md) `g` 、有向グラフかどうかを表す bool 型変数 `directed` で初期化する。

**Static Graph `g` に add する際は `g.add(from, to, cost, idx);` と引数が 4 つ必要である。 `idx` がおかしいとサイクルを正しく検出できない。**

### find
```cpp
vector<Edge<T>> find()
```
`g` に含まれるサイクルを1つ見つけ、その辺のリストを返す。サイクルが存在しない場合は空列を返す。
#### 計算量
頂点数を $N$ 、辺の本数を $M$ として $O(N+M)$ 時間
