# Treap Set の実装
[Treap Set](https://github.com/tatsumr/kyopro/blob/main/ds/treapset.cpp) の実装を説明する。またポインタによる実装と配列による実装の比較結果をまとめる。

## rotate
`rotate(Node *t)` は二分探索木ではおなじみの「木の回転」を、ノード `t` を中心に行う関数である。
![treapset_rotate](https://github.com/user-attachments/assets/23505509-7057-4b67-8632-14d430fda8aa)
図のように `t` が親の左の子なら右向きに回転、右の子なら左向きに回転するのだが、実装ではこれらを1つの関数にまとめてある。

操作後の木の、赤い辺が変更が起こった辺である。このうち
- `x` の子を `B` にする
- `B` の親を `x` にする
- `t` の子を `x` にする

処理は、左右で場合分けして別々に実装している。一方で、
- `x` の親を `t` にする
- `t` の子を `y` にする
- `y` の親を `t` にする

処理は、左右でまとめている。

## kth
ある要素（ノード）のインデックスは、予め各ノードに自分を根とする部分木のサイズを持たせておき、探索の際に「今見ているノードの左部分木のサイズ+1」を足していくことで求めることができる。
[こちらの記事](https://qiita.com/hamamu/items/570e7c36bf73913cbeb8#%E9%85%8D%E5%88%97%E3%81%A8%E3%81%97%E3%81%A6%E4%BD%BF%E3%81%86%E6%96%B9%E6%B3%95implicit-treap)の解説が分かりやすい。

## 配列による実装
本ライブラリはポインタを用いて実装しているが、配列を用いて実装するという方法もある。

本ライブラリと同じアルゴリズムを配列を用いて実装して（AIに実装させた）[Library Checker](https://judge.yosupo.jp/)の同じ問題に提出した結果、速度はあまり変わらない（少しだけ速くなる）がメモリ使用量が大きく減ることが分かった。

[Ordered Set](https://judge.yosupo.jp/problem/ordered_set) [ポインタ（32.27Mib）](https://judge.yosupo.jp/submission/412089) [配列（16.91Mib）](https://judge.yosupo.jp/submission/412684)
