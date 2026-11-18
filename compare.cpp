// Sydney Swayzer

/* add the necessary includes */
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "graph.hpp"
#include "algorithms.hpp"

using namespace std;

const int REPETITIONS = 5;

void displayAndSave(
    std::ofstream& file,
    const std::string& gType, 
    int V, 
    int E,
    double timeBFS,
    double timeBF,
    double timeD 
) {
    // Display
    cout << gType << " Graph:" << std::endl;

    if (gType == "Unweighted")
    {
        cout << "BFS:          " << timeBFS << " ms" << std::endl;
    }
    cout << "Bellman-Ford: " << timeBF << " ms" << std::endl;
    cout << "Dijkstra:     " << timeD << " ms" << std::endl;

    // Save
    if (gType == "Unweighted")
    {
        file << gType << "," << V << "," << E << ",BFS," << timeBFS << "\n";
    }
    file << gType << "," << V << "," << E << ",Bellman-Ford," << timeBF << "\n";
    file << gType << "," << V << "," << E << ",Dijkstra," << timeD << "\n";
}

int runUnweighted(int V, int E, mt19937& rng, ofstream& file)
{
    Graph graph = generateGraph(V, E, 1, 1, rng);

    auto outBFS = BFS(graph, 0);
    auto outBF = BellmanFord(graph, 0);
    auto outD = Dijkstra(graph, 0);

    if (!verifyOuts(outBFS, outBF) || !verifyOuts(outBFS, outD))
    {
        cerr << "Unweighted outputs do not match!" << std::endl;
        return 1;
    }

    double timeBFS = benchmark(graph, BFS, REPETITIONS);
    double timeBF = benchmark(graph, BellmanFord, REPETITIONS);
    double timeD = benchmark(graph, Dijkstra, REPETITIONS);

    displayAndSave(file, "Unweighted", V, E, timeBFS, timeBF, timeD);
    return 0;
}

int runWeighted(int V, int E, mt19937& rng, ofstream& file)
{
    Graph graph = generateGraph(V, E, 1, 20, rng);

    auto outBF = BellmanFord(graph, 0);
    auto outD = Dijkstra(graph, 0);

    if (!verifyOuts(outBF, outD))
    {
        cerr << "Weighted results do not match!" << std::endl;
        return 1;
    }

    double timeBF = benchmark(graph, BellmanFord, REPETITIONS);
    double timeD = benchmark(graph, Dijkstra, REPETITIONS);

    displayAndSave(file, "Weighted", V, E, 0.0, timeBF, timeD);
    return 0;
}

int main()
{
    mt19937 rng(42);
    std::filesystem::create_directories("out");
    ofstream file("out/results.csv");

    if (!file.is_open()) {
        cerr << "Unable to create results.csv" << std::endl;
        return 1;
    }

    file << "Scenario,Vertices,Edges,Algorithm,AverageTime(ms)\n";
    vector<int> sizes = {100, 250, 500, 1000};
    cout << fixed << setprecision(6);

    for (int V : sizes)
    {
        int maxEdges = V * (V - 1);

        vector<pair<string, int>> densities = {
            {"Sparse", min(4 * V, maxEdges)},
            {"Medium", min(12 * V, maxEdges)},
            {"Dense",  static_cast<int>(0.5 * maxEdges)}
        };

        for (auto [name, E] : densities)
        {
            cout << std::endl << "==============================" << std::endl;
            cout << "Vertices: " << V
                 << " | Edges: " << E
                 << " | Density: " << name << std::endl;
            cout << "==============================" << std::endl;

            if (runUnweighted(V, E, rng, file) || runWeighted(V, E, rng, file))
            {
                file.close();
                return 1;
            }
        }
    }

    file.close();

    cout << std::endl << "Benchmarking completed" << std::endl;
    cout << "Saved to results.csv" << std::endl;

    return 0;
}