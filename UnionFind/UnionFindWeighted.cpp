#include<bits/stdc++.h>
using namespace std;

template <typename Key>
struct UnionFind {
    private:
    int *parent, *rank;
    Key *diff_weight;
    public:
    UnionFind(int n) {
        parent = (int*)malloc(n*sizeof(int));
        rank = (int*)malloc(n*sizeof(int));
        diff_weight = (Key*)malloc(n*sizeof(Key));
        fill_n(parent, n, -1);
        fill_n(rank, n, 1);
        fill_n(diff_weight, n, 0);
    }
    int find(int x) {
        if (parent[x] == -1) return x;
        int root = find(parent[x]);
        diff_weight[x] += diff_weight[parent[x]];
        parent[x] = root;
        return parent[x];
    }
    bool unite(int x, int y, Key w) {
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) {
            swap(x, y);
            w = -w;
        }
        if (rank[x] == rank[y]) rank[x] += 1;
        parent[y] = x;
        diff_weight[y] = w;
        return true;
    }
    bool issame(int x, int y) {
        return find(x) == find(y);
    }
    Key weight(int x) {
        find(x);
        return diff_weight[x];
    }
    Key diff(int x, int y) {
        "assume that x and y are in the same set"
        return diff_weight[y] - diff_weight[x];
    }

    ~UnionFind() {
        free(parent);
        free(rank);
        free(diff_weight);
    }
};