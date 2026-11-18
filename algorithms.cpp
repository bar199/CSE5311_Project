// Sydney Swayzer

#include "algorithms.hpp"

std::vector<int> BFS(const Graph& g, int src)
{
    std::vector<int> dist(g.V, INF);
    std::queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, weight] : g.adj[u])
        {
            if (dist[v] == INF)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}

std::vector<int> BellmanFord(const Graph& g, int src)
{
    std::vector<int> dist(g.V, INF);
    dist[src] = 0;

    for (int i = 0; i < g.V - 1; i++)
    {
        bool updated = false;
        for (const Edge& e : g.edges)
        {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.weight;
                updated = true;
            }
        }

        if (!updated) {
            break;
        }
    }

    for (const Edge& e : g.edges)
    {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v])
        {
            std::cerr << "Negative-weight cycle detected!" << std::endl;
            return {};
        }
    }

    return dist;
}

std::vector<int> Dijkstra(const Graph& g, int src)
{
    std::vector<int> dist(g.V, INF);

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d <= dist[u])
        {
            for (auto [v, weight] : g.adj[u])
            {
                int newDist = dist[u] + weight;
                if (newDist < dist[v])
                {
                    dist[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
    }

    return dist;
}

bool verifyOuts(const std::vector<int>& a, const std::vector<int>& b)
{
    return a == b;
}