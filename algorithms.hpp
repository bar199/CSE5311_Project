// Sydney Swayzer

/* add the necessary includes */
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "graph.hpp"

/* add an include guard */
#ifndef _ALGORITHMS_
#define _ALGORITHMS_

const int INF = 1e9;

// Algorithms
std::vector<int> BFS(const Graph& g, int src);
std::vector<int> BellmanFord(const Graph& g, int src);
std::vector<int> Dijkstra(const Graph& g, int src);

template <typename Func>
double benchmark(const Graph& g, Func algorithm, int reps = 5)
{
    double totalTime = 0;

    volatile long long checksum = 0;

    for (int i = 0; i < reps; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<int> result = algorithm(g, 0);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;
        totalTime += elapsed.count();

        if (!result.empty())
        {
            checksum += result.back();
        }
    }

    return totalTime / reps;
}

bool verifyOuts(const std::vector<int>& a, const std::vector<int>& b);

#endif