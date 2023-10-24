class UnionFind:
    def __init__(self, n):
        self.parent = [-1] * n
        self.rank = [1] * n
    
    def find(self, x):
        if self.parent[x] == -1: return x
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def unite(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y: return False
        if self.rank[x] > self.rank[y]: x, y = y, x
        if self.rank[x] == self.rank[y]: self.rank[y] += 1
        self.parent[x] = y
        return True
    
    def issame(self, x, y): 
        return self.find(x) == self.find(y)

