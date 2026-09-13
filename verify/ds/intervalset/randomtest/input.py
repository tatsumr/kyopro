from gen_lib import *

Q = Int(1, 20)
print(Q)
for _ in range(Q):
    t = Int(1, 2)
    l = Int(0, 5)
    r = Int(l + 1, 10)
    x = Int(0, 1)
    if t == 1:
        print(t, l, r, x)
    else:
        print(t, l, r)
