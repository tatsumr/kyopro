# Treap Set の実装
[Treap Set](https://github.com/tatsumr/kyopro/blob/main/ds/treapset.cpp) の実装説明・高速化に関する知見をまとめた。

## rotate
`rotate(Node *t)` は平衡二分探索木ではおなじみの「木の回転」を、ノード `t` を中心に行う関数である。
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
