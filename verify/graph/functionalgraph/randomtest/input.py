from gen_lib import *

N = Int(1, 10)
K = Int(1, 20) # next

A = []
for i in range(N):
    A.append(Int(1, N))

print(N, K)
print(*A)
