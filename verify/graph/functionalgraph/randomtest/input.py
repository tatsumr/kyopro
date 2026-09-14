from gen_lib import *

N = Int(1, 10)

A = []
for i in range(N):
    A.append(Int(1, N))

print(N)
print(*A)
