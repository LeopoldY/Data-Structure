//
// Created by yangc on 24-12-2.
//

# pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>

using namespace std;

typedef struct ArcNode { // 边表节点
    int idx; // 顶点下标
    int weight; // 权重
    ArcNode *next;
    ArcNode(int i, int w = 0, ArcNode *n = nullptr) : idx(i), weight(w), next(n) {}
} *ArcNodePtr;

typedef struct VNode{ // 顶点表节点
    int data;
    ArcNodePtr firstArc;
    VNode(int d = 0, ArcNodePtr f = nullptr) : data(d), firstArc(f) {}
} *VNodePtr;

struct DijkstraLists {
    vector<int> dist;
    vector<int> path;
};

class AdjListGraph { // 邻接表图
private:
    std::vector<VNodePtr> adjList; // 邻接表
    int numVex; // 顶点数
    int numArc; // 边数
public:
    AdjListGraph(int n) : numVex(n), numArc(0) {
        adjList.resize(n);
    }

    ~AdjListGraph() {
        for (int i = 0; i < numVex; i++) {
            ArcNode *p = adjList[i]->firstArc;
            while (p) {
                ArcNode *q = p;
                p = p->next;
                delete q;
            }
        }
    }

    void addEdge(int u, int v, int w = 0) {
        ArcNode *node = new ArcNode(v, w, adjList[u]->firstArc);
        adjList[u]->firstArc = node;
        numArc++;
    }

    bool dfs(int u, int parent, std::vector<int> &visited) {
        visited[u] = 1;
        ArcNode *p = adjList[u]->firstArc;
        while (p) {
            if (!visited[p->idx]) {
                if (dfs(p->idx, u, visited)) return true;
            } else if (p->idx != parent) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // 判断是否为树
    bool isTree() {
        std::vector<int> visited(numVex, 0);
        if (dfs(0, -1, visited)) {
            for (int i = 0; i < numVex; i++) {
                if (!visited[i]) return false;
            }
            return true;
        }
        return false;
    }

    // 判断是否为连通图
    bool isConnected() {
        std::vector<int> visited(numVex, 0);
        dfs(0, -1, visited);
        for (int i = 0; i < numVex; i++) {
            if (!visited[i]) return false;
        }
        return true;
    }

    // 最小生成树的Prim算法实现
    std::vector<std::tuple<int, int, int>> primMST() {
        std::vector<int> inMST(numVex, 0); // 标记顶点是否已加入MST
        std::vector<int> key(numVex, INT_MAX); // 每个顶点的权值
        std::vector<int> parent(numVex, -1); // MST中的父节点
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq; // 小顶堆

        key[0] = 0; // 从顶点0开始
        pq.push({0, 0}); // (权值, 顶点)

        while (!pq.empty()) {
            int u = pq.top().second; // 取出权值最小的顶点
            pq.pop();

            if (inMST[u]) continue; // 如果顶点已在MST中，跳过
            inMST[u] = 1;

            // 遍历与u相邻的所有边
            ArcNode *p = adjList[u]->firstArc;
            while (p) {
                int v = p->idx;
                int weight = p->weight;

                // 如果v不在MST中且权值小于当前记录的权值
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({weight, v});
                }
                p = p->next;
            }
        }

        // 收集MST边集
        std::vector<std::tuple<int, int, int>> mstEdges;
        for (int i = 1; i < numVex; i++) {
            if (parent[i] != -1) {
                mstEdges.emplace_back(parent[i], i, key[i]);
            }
        }
        return mstEdges;
    }

    // Dijkstra算法实现
    DijkstraLists dijkstra(int src) {
        std::vector<int> dist(numVex, INT_MAX); // 记录源点到各点的最短距离
        std::vector<int> path(numVex, -1); // 记录最短路径
        std::vector<int> final(numVex, 0); // 记录是否已经找到最短路径

        // 初始化
        dist[src] = 0;
        final[src] = 1;
        ArcNode *p = adjList[src]->firstArc;
        while (p) {
            dist[p->idx] = p->weight;
            path[p->idx] = src;
            p = p->next;
        }

        for (int i = 1; i < numVex; i++) {
            int min = INT_MAX;
            int u = src;
            for (int j = 0; j < numVex; j++) {
                if (!final[j] && dist[j] < min) {
                    min = dist[j];
                    u = j;
                }
            }
            final[u] = 1;
            p = adjList[u]->firstArc;
            while (p) {
                int v = p->idx;
                if (!final[v] && dist[u] + p->weight < dist[v]) {
                    dist[v] = dist[u] + p->weight;
                    path[v] = u;
                }
                p = p->next;
            }
        }

        return {dist, path};
    }

    // Dijkstra算法求解最短路径（限制最多经过 k 个中转站）
    int findCheapestPrice(int src, int dst, int k) {
        DijkstraLists dijkstraLists = dijkstra(src);
        std::vector<int> dist = dijkstraLists.dist;
        std::vector<int> path = dijkstraLists.path;

        // 判断中转是否超过 k
        int cnt = 0;
        int cur = dst;
        while (cur != src) {
            cur = path[cur];
            cnt++;
        }
        if (cnt > k) return -1;

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }

    // Floyd算法实现求解最短路径（限制最多经过 k 个中转站）
    int findCheapestPriceFloyd(int src, int dst, int k) {
        std::vector<std::vector<int>> dist(numVex, std::vector<int>(numVex, INT_MAX));
        for (int i = 0; i < numVex; i++) {
            dist[i][i] = 0;
            ArcNode *p = adjList[i]->firstArc;
            while (p) {
                dist[i][p->idx] = p->weight;
                p = p->next;
            }
        }

        for (int k = 0; k < numVex; k++) {
            for (int i = 0; i < numVex; i++) {
                for (int j = 0; j < numVex; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        return dist[src][dst] == INT_MAX ? -1 : dist[src][dst];
    }

    void printGraph() {
        for (int i = 0; i < numVex; i++) {
            std::cout << "Vertex " << i << ":";
            ArcNode *p = adjList[i]->firstArc;
            while (p) {
                std::cout << " -> " << p->idx << "(" << p->weight << ")";
                p = p->next;
            }
            std::cout << std::endl;
        }
    }
};
