#include<bits/stdc++.h>
using namespace std;

struct UnionFind {
    private:
    int *parent, *rank;
    public:
    UnionFind(int n) {
        parent = (int*)malloc(n*sizeof(int));
        rank = (int*)malloc(n*sizeof(int));
        fill_n(parent, n, -1);
        fill_n(rank, n, 1);
    }
    int find(int x) {
        if (parent[x] == -1) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] > rank[y]) swap(x, y);
        if (rank[x] == rank[y]) rank[y] += 1;
        parent[x] = y;
        return true;
    }
    bool issame(int x, int y) {
        return find(x) == find(y);
    }
    ~UnionFind() {
        free(parent);
        free(rank);
    }
};