"""
グラフを隣接行列(adjacency matrix)として保持します。
INFの値は、状況に応じて適切な値に変更します。
float("inf")などにするより、整数値にした方が速いようです。
"""

import heapq
INF = 10**18

class Dijkstra:
    def __init__(self,num_node):
        self.num_node = num_node
        self.edge = [[INF]*num_node for _ in range(num_node)]
    def add_edge(self,start,end,cost):
        self.edge[start][end]=cost
    def delete_edge(self,start,end):
        self.edge[start][end]=INF
    def dijkstra_heap(self,start):
        self.start = start
        self.d = [INF] * self.num_node
        c = [start] # 0*N + start
        used=[False] * self.num_node
        while c:
            w, u = divmod(heapq.heappop(c), self.num_node)
            if used[u]: continue
            self.d[u] = w
            used[u] = True
            for v in range(self.num_node):
                if used[v]: continue
                if self.d[v] > self.d[u] + self.edge[u][v]:
                    self.d[v] = self.d[u] + self.edge[u][v]
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
