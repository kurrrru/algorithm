#include<bits/stdc++.h>
using namespace std;

template <typename Key>
struct Dijkstra {
    private:
    int num_node, start;
    Key INF;
    Key** edge;
    Key* dist;
    Key* dijkstra_heap() {
        priority_queue<long long, vector<long long>, greater<long long>> heap;
        heap.push(start);
        bool* used = (bool*)malloc(num_node * sizeof(bool));
        fill_n(used, num_node, false);
        long long to_and_cost;
        int cost, u;
        while (!heap.empty()) {
            to_and_cost = heap.top();
            heap.pop();
            cost = to_and_cost / num_node;
            u = to_and_cost % num_node;
            if (used[u]) continue;
            dist[u] = cost;
            used[u] = true;
            for (int v=0; v<num_node; ++v) {
                if (used[v]) continue;
                if (dist[v] > dist[u] + edge[u][v]) {
                    dist[v] = dist[u] + edge[u][v];
                    heap.push(dist[v] * num_node + v);
                }
            }
        }
        free(used);
        return dist;
    }
    public:
    Dijkstra(int _num_node, Key _INF = 1<<30) {
        num_node = _num_node;
        INF = _INF;
        edge = (Key**)malloc(num_node * sizeof(Key*));
        dist = (Key*)malloc(num_node * sizeof(Key));
        for (int i=0; i<num_node; ++i) {
            edge[i] = (Key*)malloc(num_node * sizeof(Key));
            fill_n(edge[i], num_node, INF);
        }
        fill_n(dist, num_node, INF);
    }
    void add_edge(int from, int to, Key cost) {
        edge[from][to] = cost;
    }
    Key* dijkstra(int from, bool using_heap = true) {
        start = from;
        if (using_heap) return dijkstra_heap();
        dist[start] = 0;
        bool* used = (bool*)malloc(num_node * sizeof(bool));
        fill_n(used, num_node, false);
        int min_d_index;
        Key min_d;

        for (int i=0; i<num_node; ++i) {
            min_d = INF;
            min_d_index = -1;
            for (int j=0; j<num_node; ++j) {
                if (used[j]) continue;
                if (dist[j] < min_d) {
                    min_d = dist[j];
                    min_d_index = j;
                }
            }
            if (min_d_index == -1) break;    
            used[min_d_index] = true;
            for (int j=0; j<num_node; ++j) {
                if (used[j]) continue;
                Key cost = edge[min_d_index][j];
                if (dist[min_d_index] + cost < dist[j]) {
                    dist[j] = dist[min_d_index] + cost;
                }
            }
        }
        free(used);
        return dist;
    }
    ~Dijkstra() {
        for (int i=0; i<num_node; ++i) {
            free(edge[i]);
        }
        free(edge);
        free(dist);
    }
};