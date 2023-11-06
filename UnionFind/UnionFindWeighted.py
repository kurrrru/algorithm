class UnionFind:
    def __init__(self, n: int) -> None:
        self.parent: list[int] = [-1] * n 
        self.rank: list[int] = [1] * n
        self.diff_weight: list[int|float] = [0] * n
    
    def find(self, x: int) -> int:
        if self.parent[x] == -1: return x
        root = self.find(self.parent[x])
        self.diff_weight[x] += self.diff_weight[self.parent[x]]
        self.parent[x] = root
        return self.parent[x]
    
    def unite(self, x: int, y: int, w: int|float) -> bool:
        """
        xとyが異なる集合に属している場合、それらを併合してTrueを返す。
        xとyが元々同じ集合に属している場合、Falseを返す。
        wはxを基準にしたyを表す。（yを基準にしたxとしてもよいが、どちらにするかは統一されている必要がある。）
        """
        w+=self.weight(x)
        w-=self.weight(y)
        x = self.find(x)
        y = self.find(y)
        if x == y: return False
        if self.rank[x] < self.rank[y]: 
            x, y = y, x
            w = -w
        if self.rank[x] == self.rank[y]: self.rank[x] += 1
        self.parent[y] = x
        self.diff_weight[y] = w
        return True
        
    def issame(self, x: int, y: int) -> bool: 
        return self.find(x) == self.find(y)
    
    def weight(self, x: int) -> int|float:
        self.find(x)
        return self.diff_weight[x]        
    
    def diff(self, x: int, y: int) -> int|float:
        if self.issame(x,y):
            return self.diff_weight[y]-self.diff_weight[x]
    
