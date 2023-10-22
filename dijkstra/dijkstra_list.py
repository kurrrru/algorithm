"""
グラフを隣接リスト(adjacency list)として保持します。
INFの値は、状況に応じて適切な値に変更します。
float("inf")などにするより、整数値にした方が速いようです。
"""
import heapq
INF = 10**18

class Dijkstra:
    def __init__(self,num_node):
        self.num_node = num_node
        self.edge = [[] for _ in range(num_node)]
    def add_edge(self,start,end,cost):
        self.edge[start].append([end,cost])
    def dijkstra_heap(self,start):
        "startからの最短距離を求める。"
        self.start = start
        self.d = [INF] * self.num_node
        c = [start] # 0*N + start
        used=[False] * self.num_node
        while c:
            w, u = divmod(heapq.heappop(c), self.num_node)
            if used[u]: continue
            self.d[u] = w
            used[u] = True
            for v,cost in self.edge[u]:
                if used[v]: continue
                if self.d[v] > self.d[u] + cost:
                    self.d[v] = self.d[u] + cost
                    heapq.heappush(c, self.d[v] * self.num_node + v)
        return self.d
    def dijkstra(self, start, heap = True):
        """
        heap = Trueにすると、O((E+V)logV)
        heap = Falseにすると、O(V^2)
        """
        if heap: return self.dijkstra_heap(start)
        self.start = start
        self.d = [INF] * self.num_node
        self.d[start] = 0
        used = [False] * self.num_node
        for _ in range(self.num_node):
            min_d = INF
            min_d_index = -1
            for j in range(self.num_node):
                if used[j]: continue
                if self.d[j] < min_d:
                    min_d = self.d[j]
                    min_d_index = j
            if min_d_index == -1: break
            used[min_d_index] = True
            for j, cost in self.edge[min_d_index]:
                if used[j]: continue
                if self.d[min_d_index] + cost < self.d[j]:
                    self.d[j] = self.d[min_d_index] + cost
        return self.d