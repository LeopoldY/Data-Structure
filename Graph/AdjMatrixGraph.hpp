//
// Created by yangc on 24-12-2.
//

#ifndef DATA_STRUCTURE_ADJMATRIXGRAPH_HPP
#define DATA_STRUCTURE_ADJMATRIXGRAPH_HPP
// Created on iPad.

#include <iostream>
#include <vector>
#include <queue>
#define MAXV 100
using namespace std;

typedef struct {
    int numVex, numArc;       // 顶点数和边数
    char VexList[MAXV];       // 顶点列表
    int edge[MAXV][MAXV];     // 邻接矩阵
} MGraph;

bool uniquely(MGraph G) {
    vector<int> inDegree(G.numVex, 0);
    queue<int> zeroQueue;
    int visitedCount = 0;

    // 初始化入度数组
    for (int i = 0; i < G.numVex; i++) {
        for (int j = 0; j < G.numVex; j++) {
            if (G.edge[i][j]) inDegree[j]++;
        }
    }

    // 找到所有初始入度为0的顶点
    for (int i = 0; i < G.numVex; i++) {
        if (inDegree[i] == 0) zeroQueue.push(i);
    }

    // 拓扑排序
    while (!zeroQueue.empty()) {
        if (zeroQueue.size() > 1) return false; // 多个入度为0的顶点，说明排序不唯一

        int cur = zeroQueue.front();
        zeroQueue.pop();
        visitedCount++;

        // 更新相邻顶点的入度
        for (int i = 0; i < G.numVex; i++) {
            if (G.edge[cur][i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) zeroQueue.push(i);
            }
        }
    }

    // 如果没有访问完所有顶点，说明图中有环
    return visitedCount == G.numVex;
}
#endif //DATA_STRUCTURE_ADJMATRIXGRAPH_HPP
