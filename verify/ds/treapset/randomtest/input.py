from gen_lib import *
from random import shuffle
import itertools

# とりあえず多重でない set の verify

Q = Int(1, 20)
print(Q)

A = []

for _ in range(Q):
    # insert : erase : 二分探索 = 5:3:2 にしている
    # erase では 50% の確率で x を意図的に集合内の要素にする
    
    prob = Int(1, 10)
    tp: int
    x = Int(1, 30)
    
    if prob <= 5:
        tp = 1
        if x not in A:
            A.append(x)
    
    elif prob <= 8:
        tp = 2
        if len(A) >= 1 and Int(0, 1) == 0:
            i = Int(0, len(A) - 1)
            x = A[i]
        if x in A:
            i = A.index(x)
            A.pop(i)
    
    else:
        tp = 3
    
    print(tp, x)
            
