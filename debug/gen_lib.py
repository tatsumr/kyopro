import random
import string
import heapq

class UF:
    def __init__(self, n):
        self.par = [-1 for _ in range(n)]
        self.cc = n
    
    def merge(self, a, b):
        x, y = self.leader(a), self.leader(b)
        if x == y: return x
        if -self.par[x] < -self.par[y]: x, y = y, x
        self.par[x] += self.par[y]
        self.par[y] = x
        self.cc -= 1
        return x
    
    def same(self, a, b): return self.leader(a) == self.leader(b)
    
    def leader(self, a):
        if self.par[a] < 0: return a
        self.par[a] = self.leader(self.par[a])
        return self.par[a]
    
    def size(self, a): return -self.par[self.leader(a)]
    
    def count(self): return self.cc

#  a <= x <= b
def Int(a, b):
    return random.randint(a, b)

# l <= x <= r
def Array(n, l, r):
    return [Int(l, r) for _ in range(n)]

# [start, start+n)
def Perm(n, start=0):
    a = list(range(start, start + n))
    random.shuffle(a)
    return a

def String(n, s=string.ascii_lowercase):
    return ''.join(random.choice(s) for _ in range(n))

# 重みなし
# 0 <= u < v < N
def Tree(n):
    if n == 1:
        return []
    elif n == 2:
        return [(0, 1)]
    prufer = Array(n - 2, 0, n - 1)
    deg = [1 for _ in range(n)]
    for p in prufer:
        deg[p] += 1
    st = [v for v in range(n) if deg[v] == 1]
    heapq.heapify(st)
    es = []
    for x in prufer:
        y = heapq.heappop(st)
        es.append((min(x, y), max(x, y)))
        deg[x] -= 1
        if deg[x] == 1:
            heapq.heappush(st, x)
    u = heapq.heappop(st)
    v = heapq.heappop(st)
    es.append((min(u, v), max(u, v)))
    return es

# 多重辺なし、自己ループなし、重みなし、連結
def Graph(n, m):
    assert(n - 1 <= m <= n * (n - 1) // 2)
    st = set()
    es = Tree(n)
    for u, v in es: st.add((u, v))
    while len(es) < m:
        u, v = Int(0, n - 1), Int(0, n - 1)
        if u > v: u, v = v, u
        if (u == v) or ((u, v) in st): continue
        es.append((u, v))
        st.add((u, v))
    random.shuffle(es)
    return es
