// Sydney Swayzer

/* add the necessary includes */
#include <random>
#include <unordered_set>
#include <vector>

/* add an include guard */
#ifndef _GRAPH_
#define _GRAPH_

struct Edge {
    int u, v, weight;
};

struct Graph {
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<Edge> edges;

    Graph(int vertices);

    void addEdge(int u, int v, int weight);
};

Graph generateGraph(
    int V,
    int E,
    int weightMin,
    int weightMax,
    std::mt19937& rng
);

#endif