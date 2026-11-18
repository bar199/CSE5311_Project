// Sydney Swayzer

#include "graph.hpp"

Graph::Graph(int vertices)
{
    V = vertices;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int weight)
{
    adj[u].push_back({v, weight});
    edges.push_back({u, v, weight});
}

Graph generateGraph(
    int V,
    int E,
    int weightMin,
    int weightMax,
    std::mt19937& rng
) {
    Graph g(V);

    std::uniform_int_distribution<int> distVertex(0, V - 1);
    std::uniform_int_distribution<int> distWeight(weightMin, weightMax);

    std::unordered_set<unsigned long long> usedEdges;

    while (static_cast<int>(g.edges.size()) < E)
    {
        int u = distVertex(rng);
        int v = distVertex(rng);

        if (u != v)
        {
            unsigned long long key = static_cast<unsigned long long>(u) * V + v;

            if (!usedEdges.count(key))
            {
                usedEdges.insert(key);
                int weight = distWeight(rng);
                g.addEdge(u, v, weight);
            }
        }
    }

    return g;
}